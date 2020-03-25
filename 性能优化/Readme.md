# 目录  
- [优化原则](#优化原则)  
- [工具](#工具)  
- [关键点](#关键点)  
- [实操](#实操)
- [应用](#应用)

# 优化原则  
1. 不过早优化，当性能成为关键时再优化；不过度优化，适可而止    
2. 先优化架构、框架、流程、系统配置、设置编译器优化相关参数这些宏观上的东西        
3. 找出性能瓶颈，对热点代码进行优化  
4. 可考虑空间换时间

# 工具 
* perf   
https://github.com/pingz1988/Linux/blob/master/%E5%B7%A5%E5%85%B7/perf.md

Intel平台工具：
* VTune     
https://software.intel.com/en-us/vtune-amplifier-help-amplxe-cl-command-syntax  
* Intel Thread Checker  
* Intel Thread Profiler  

# 常用法则  
## 空间换时间  
* 修改数据结构：增加额外信息，便于数据访问  
* 利用中间结果计算后续结果  
* cache  
## 循环法则  
* 将代码移出循环体 
* 合并条件：内循环条件尽可能少，可用哨兵  
* 循环展开（运行时间可提高50%左右）  
* 循环合并（一次循环尽量多的做事） 
## 逻辑法则  
* 预先计算逻辑函数：在比较小的有限域上，用查表取代逻辑函数  
## 过程法则  
* 打破函数层次：使用inline/宏替代简单函数，减少函数调用开支    
* 消除递归函数：重写为迭代方式  
* 提高并行性：尽可能让代码并行执行（有些并行方式涉及CPU指令），参考DPDK优化      
## 表达式法则  
* 初始化：尽可能多地初始化变量  
* 用等价代数表达式替换开销较大的运算：三角函数/求模/乘除等都可替代  

# 关键点  
* 数据结构及算法
* 内存管理(包括对齐、cache、内存分配等）  

## 设计层面  
* 业务流程、架构优化
* 优先多核，然后多线程
* 数据本地化、无锁化  

## 编译层面  
开启必要的编译器优化参数，让编译器自动做优化  

# 代码层面
## 变量 
* 尽可能用无符号变量
* 尽量少用全局变量，可先赋值给局部变量再使用  
* 尽量使用const、static（本地化）变量 
* 少用数组，换成指针。用restrict修饰的指针，表明指针所指向的内存只能由该指针来修改，而不能由其它变量或指针来修改，避免指针别名问题，这样做可以让编译器优化代码。 memcpy(void * restrict dest, void * restrict src, size_t n)使用了restrict关键字，不让内存重叠操作。
* 结构体要对齐，一般以cached line 64字节对齐  
* 线程中的本地全局变量让它对齐_declspec(align(64)) int thread_local_val，以避免伪共享（false sharing）引发的cache line调度

## 函数及逻辑
* 函数不需要返回值时，用void减少函数栈操作  
* 尽量减少函数间的调用层数，以减小函数栈调用开销（比如递归）
* 尽量消除条件分支判断  
* if、switch 分支中，按出现可能性由高到低排放  
* 多语句宏、想用goto语句时，用do...while(0)  
* 尽量用static、inline函数（内联函数中要注意提高分支预测率、减少函数调用），函数参数也尽量用const
* 尽量用位运算  

## 循环  
* 循环融合  
```c
#pragma omp parallel for
    for (i = 0; i < 8; i++)
        for (j = 0; j < 9; j++)
            a[i][j] = b[j] * c[i];

#pragma omp parallel for
    for (ij = 0; ij < 72; ij++)
    {
        int i = ij / 9;
        int j = ij % 9;
        a[i][j] = b[j] * c[i];
    }
```  
* 循环交换  
交换内外层循环，使外层循环次数少，内层循环次数多.  
把内层循环可以做的操作放到外层循环。  
* 循环展开  
```c
for (i = 1; i < n+1; i++)
{
    res = res + i;
}

// 利用寄存器优化  
for (i = 1; i < n; i+=2)
{
    res1 = res1 + i;
    res2 = res2 + (i+1);
}
```
* 其它  
循环条件<、>优于<=、>=  
++i优于i++

## 分支预测
* 排列代码使得分支预测符合静态分支预测结果：静态分支预测**if(condition)中的前向条件为不采取**，可以把逻辑改成**if(!condition)**；静态分支预测while(condition)/for(condition)中的后向条件为采取
* 尽量减少甚至消除分支（运用上述的循环展开、排列代码方式），尤其在主逻辑中
* if条件出现的概率可预测时，**使用likely、unlikely**，否则不用  

## 编译相关  
* 变量对齐  
\_\_attribute\_\_(aligned(N)) 属性指定变量以N字节对齐；\_\_attribute\_\_(packed)属性指定变量以最小字节数对齐，位域变量以位对齐，其它变量则以一字节对齐
* -O3优化  
* 没有开启-O编译优化，任何函数是不会被内联的，使用–Winline，让gcc对标志成inline但不能被展开的函数给出警告信息，例如，使用了可变函数、递归  
* 尽量作函数声明，此时可手动添加各种属性\_\_attribute\_\_以使编译器作优化  
* **没有使用函数返回值将会在编译时产生警告**：\_\_attribute__((warn_unused_result))
* 函数尽量使用const、static（本地化）、inline(用\_\_attribute\_\_((always_inline))强制内联)及其组合来修饰函数  
* 函数返回值**仅仅依赖于输入参数**时（不涉及staic变量、全局变量、指针等），用\_\_attribute__((const))修饰函数，编译器会使得相同的输入只会计算一次。比如求一个数的平方。 pure与const属性用处类似，没有const那么严格，比如 int hash (char \*) \_\_attribute\_\_ ((pure))   
* 编译器对函数参数进行非空检查（只能检查明确的NULL传参，不能检查p=NULL，传入p的情况）：\_\_attribute__((nonnull))，也可指定检查第几个参数（参数序号从1开始）\_\_attribute__((nonnull(2)))
* 函数使用hot属性\_\_attribute__((hot))会将热点函数集中放在txt section某处，以改善本地化；函数使用cold属性也会把函数集中放在txt section某处，这些函数不大可能执行，在分支预测时有用，比如perror函数。
* \_\_attribute__(section_name) 修饰函数或变量，将其放入以section_name命名的段中，以提高代码和数据的本地化（**还需理解及验证**）  

## 并行化
Amdahl定律：增加处理器数、计算负载分布到更多处理器上；串行计算程序的加速，取决于程序代码可并行化的比例。  
编译器对满足条件的代码进行并行化处理，以优化执行。  
* 循环可并行的3个条件    
  1、进入循环之前，循环次数是确定的（while循环就不符合这个条件）  
  2、循环中，不能跳入或跳出循环  
  3、各次循环之间的数据是独立没有依赖的（计算结果与执行顺序无关）  
  可以手动告诉编译器对循环并行化，在循环前加一行\#pragma parallel   
  ```c
  void add (int k, float *a, float *b)
  {
    #pragma parallel
      for (int i = 1; i < 10000; i++)
        a[i] = a[i+k] + b[i];
  }
  ```
  gcc命令行参数-par_report3打印哪些循环可以并行化、哪些循环不能并行化的详细信息  
* 指针或数组别名  
  指针或数组别名是编译器判断代码是否可安全并行的阻碍。restrict关键字修饰指针或数组变量，告诉编译器变量所指的内存只能由这个变量来修改，有利于编译器并行化处理    
  
* 多线程并行化步骤  
  1、合理划分任务：划分粒度过粗会造成线程的任务负载不均衡，粒度过细带来线程资源等开销.  
  2、线程通信；线程间数据的划分、线程同步操作。  
  3、算法优化  
 
* 线程等待方式  
  1、忙等spin-wait，在资源持有时间短（1/100s）、很快能获取到资源的情况下使用，此时效率较高  
  2、阻塞，放弃CPU直到资源可用，在长时间获取不到资源时使用  
 
* 并行方式  
  1、OpenMP指令（编译器不支持时会忽略指令，GCC支持），适用于数据分解，旨在数据并行处理，只需加指令即可，由串行改成并行代码改动小，但它不够灵活，不能动态创建销毁线程、不支持线程优先级等属性的设置。   
  OpenMP官方文档：https://www.openmp.org/specifications/  
  为线程的任务负载均衡，OpenMP有4种任务调度方法：a) 静态 b) 动态 c) 引导 d)运行时，默认为静态调度方法  
  2、Thread API，适用于功能分解，旨在功能间的并行，由串行改成并行代码改动大，但控制线程很灵活  

## 伪共享（false sharing）
* 可能原因  
线程间的全局变量、动态分配的共享数据  
* 检测  
VTune工具采样2nd Level Cache Load Misses Retired事件，支持超线程时采样Memory Order Machine Clear事件，当发现大量出现采样事件时，说明可能出现了伪共享  
* 解决办法  
使用指令__declspec (align(n))，让变量对齐（SSE指令集中，n=16）
```c
__declspec (align(16)) int thread1_global_variable;
__declspec (align(16)) int thread2_global_variable;

struct ThreadParams
{
  // For the following 4 variables: 4*4 = 16 bytes
  unsigned long thread_id;
  unsigned long v; // Frequent read/write access variable
  unsigned long start;
  unsigned long end;
  // expand to 128 bytes to avoid false-sharing
  // (4 unsigned long variables + 28 padding)*4 = 128
  int padding[28];
};
__declspec (align(16)) struct ThreadParams Array[10];

void threadFunc(void *parameter)
{
  ThreadParams *p = (ThreadParams*) parameter;
  // local copy for read/write access variable.先拷到本地，再使用
  unsigned long local_v = p->v;
  for(local_v = p->start; local_v < p->end; local_v++)
  {
    // Functional computation
  }
  p->v = local_v; // Update shared data structure only once
}
```
上述避免伪共享的技术需要保守使用，除非性能得到较大提升，它们会影响CPU自身的cache调度

## 数据结构与算法  
针对具体实际应用，适用的数据结构的设计以及算法实现思路都对程序性能有重大影响。  
有序数组元素的插入比链表插入还快？？链表需要存数据外，还要存指针，每个元素存储空间比数组多；数组访问数据有良好的预见性，链表需要在内存空间来回跳跃。    
