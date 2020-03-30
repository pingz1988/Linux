# 目录  
- [基础](#基础)  
- [可执行程序](#可执行程序)  
- [静态库及动态库](#静态库及动态库)  
- [Makefile](#Makefile)
- [GDB调试](#GDB调试)

# 基础
* man 帮助  
查看 ls 命令第一部分：  
man 1 ls  

* 查看系统环境变量  
env  
env | grep XXX  

* 打印错误信息  
perror(argv[0]) ： ./a.out: No such file or directory

* linux下两种 c++ main函数   
```c++
int main(void)
int main(int argc, char *argv[])
```

* ubuntu下最好安装开发环境，安装过程中可能由于网络原因安装失败：  
sudo apt-get install  build-essential  
也可以单个包进行安装，如：  
sudo apt-get install libc6-dev   

* 缺少io.h文件：  
  使用locate命令查找io.h，如果有这个文件，拷贝到/usr/include/sys目录下，编译时-I包含这个目录 
  
# 可执行程序
* 查看可执行程序有哪些函数  
objdump -T xxx_exe  
* 后台方式运行可执行程序  
nohup command > outFile 2>&1 

# 静态库及动态库
* linux 32/64位动态库如何编译  
-m32/-m64 ？
32位系统编译32位.so，64位编译64位.so ？

* 查看.so有哪些函数（.a使用nm -g **.a）  
nm -D **.so  
筛选／查找： nm **.so | grep XX

* 查看.so是32还是64位？
objdump -a *.so

* 调用.so的两种方法：  
  1、使用dlopen等函数调用.so时，在链接成目标时加上-ldl参数  
  2、包含.h，直接调用so函数，链接LIBS时候加上so路径

* 找不到pthread相关符号时，需要链接-lpthread

* 多个.a合成一个.a，即用多个.a编译成一个.a：
ar x libtest1.a		//导出.a中的符号到.o  
ar x libtest2.a  
ar rc liball.a *.o  //多个.o合成.a  

* 查看.so依赖库：
ldd x.so  
如果有找不到的依赖库拷贝至/usr/lib目录  

* 编译  
static_library:   
    gcc -c *.c   
    ar  -cr xxx.a *.o  
 
shared_library:  
    gcc -shared -fpic -o xxx.so *.c  

# Makefile
* 简单的编译命令   
gcc xxx.c  : 生成 a.out   
gcc -o xxx xxx.c  : 生成 xxx 

* 多线程编译  
make -j 

* make直接传递makefile中变量的值，则makefile中同名的变量会被统一替换为指定的值  
make DIR=/Home  

* 多makefile中共用变量   
1、make DIR=/Home  
2、export DIR=/Home  // 注意，export命令最好不要放在子目标中  

* 打印变量值  
$(info xxxVar=$(xxxVar))  

* 获取当前makefile路径  
DIR := $(shell dirname $(mkfile_path))  // 绝对路径  
DIR := $(shell dirname $(pwd))  // 相对路径，跟调用者路径相关，最好使用上面的绝对路径     

* makefile 调试参数
1. make -n  // 把规则和连带规则下的命令打印出来  
2. make -p  // 如果目标不存在，其会打印相关的出错信息  
3. make -p -f /dev/null  // 可以打印出内置变量和内置规则
4. make -h  // 可查看其它make参数  
<br>

| 符号 | 说明 |
| ------ | ------ |
| = | 变量的值将会是整个makefile中最后被指定的值 |
| := | 覆盖之前的值 |
| ?= | 如果没有被赋值过就赋予等号后面的值 |

* 注意：
  + 1、makefile编译时，不要编译任何.h/.hpp头文件，本身它们是不参与编译的，如果把它们编译生成的.o文件链接成目标文件就会报错（x.o文件不能被识别）。如果其它.c文件用到这些头文件，在编译.c文件时，用-I包含头文件即可
  + 2、每个.c文件编译成一个.o文件，不能多个.c生成一个.o文件
  + 3、生成调试信息，编译时需要使用-g参数
  + 4、编译选项-O0，意思是不进行编译优化。gdb在默认情况下会使用-O2优化编译，调试时打印变量会出现<optimized out>。
  + 5、C++调用C程序，注意extern "C"的使用，否则编译提示找不到符号

* make编译输出到文件：<br />
  + 1、想要把make输出的全部信息，输出到某个文件中，最常见的办法就是：<br />
make xxx > build_output.txt <br />
此时默认情况是没有改变2=stderr的输出方式，还是屏幕，所以，如果有错误信息，还是可以在屏幕上看到的。<br />
  + 2、只需要把make输出中的错误（及警告）信息输出到文件中ing，可以用：<br />
make xxx 2> build_output.txt <br />
相应地，由于1=stdout没有变，还是屏幕，所以，那些命令执行时候输出的正常信息，还是会输出到屏幕上，你还是可以在屏幕上看到的。<br />
  * 3、只需要把make输出中的正常（非错误，非警告）的信息输出到文件中，可以用：<br />
make xxx 1> build_output.txt <br />
相应地，由于2=stderr没有变，还是屏幕，所以，那些命令执行时候输出的错误信息，还是会输出到屏幕上，你还是可以在屏幕上看到的。<br />
  * 4、想要把正常输出信息和错误信息输出到分别的文件中，可以用：<br />
make xxx 1> build_output_normal.txt 2>build_output_error.txt <br />
即联合使用了1和2，正常信息和错误信息，都输出到对应文件中了。<br />
  * 5、 所有的信息都输出到同一个文件中：<br />
make xxx > build_output_all.txt 2>&1<br />
其中的2>&1表示错误信息输出到&1中，而&1，指的是前面的那个文件：build_output_all.txt 。<br />
注意：上面所有的1,2等数字，后面紧跟着大于号'>' ，中间不能有空格。<br />

# GDB调试
| 命令 | 描述 |
| ------ | ------ |
| gdb attach pid | 附加进程调试 |
| r v1 v2 | 设置调试参数为v1、v2 |
| set args v1 v2 | 设置调试参数为v1、v2 |
| show args | 显示调试参数 |
| bt |	查看各级函数调用及参数 |
| f n	| 选择栈帧n |
| up n/down n	| 向上或向下选择选择栈帧，默认n=1 |
| u(until) | 执行完当前的循环 |
| fin(finish) | 执行到当前函数返回为止，然后停下来等待命令 |
| l	| 列出源代码，接着上次的位置往下列，每次列10行 |
| l -/+ | 向前/后列出源码 |
| l N | 列出从第N行开始的源代码 |
| l 1,10 | 列出指定行范围的源码 |
| l func | 列出函数func的源代码 |
| l file:N | 定位到指定文件的指定行或者函数 |
| n |	执行下一行语句 |
| p |	打印表达式的值，通过表达式可以修改变量的值或者调用函数 |
| q |退出gdb调试环境 |
| set var	| 修改变量的值 |
| start	| 开始执行程序，停在main函数第一行语句前面等待命令 |
| s | 执行下一行语句，如果有函数调用则进入到函数中 |
| wa(watch) var | 观察一个变量，当一个变量值发生变化时会断下来。软件实现的观察点会导致程序运行很慢。 |
| wa a thread 2 | 只有线程2改变a的值才会停下来 |
| rw(rwatch) a | 每次读取 a 的值都会让程序停下来 |
| aw(awatch) a | 当发生读取 a 或改变变量 a 值的行为时，程序就会暂停住 |
| disp(display) var | 程序每次断住时，就显示某个变量或表达式的值 |
| info display | 查看哪些变量被设置了display |
| delete display num | num为info disp变量前的编号,不带num时清除所有 |
| current | 跳转到下个断点，或则跳转到观察点 |
| b n | 在第n行设置断点 |
| b n if i == 100 | 在第n行设置条件断点 |
| b func | 在函数func处设置断点 |
| b fileName:N | 在文件第N行设置断点 |
| b Foo::foo | 对命名空间Foo中的foo函数设置断点 |
| tb(tbreak) N | 让断点只生效一次，断点参数跟break命令一样 |
| i(info) source | 显示源文件信息（全路径、行数、编程语言、预编译宏） |
| i b | 显示当前所有的断点，断点号，断点位置 |
| i locals	| 查看当前栈帧局部变量的值 |
| i args	| 打印出当前函数的参数名及其值 |
| i functions thre* | 列出以thre开头的函数名 |
| d | 删除所有断点 |
| d n | 删除第n个断点 |
| clear | 清除所有断点 |
| clear n | 清除第n行的断点 |
| c | 继续执行到下一断点 |
| where | 查看当前运行到哪（也可用bt命令） |
| p var | 显示变量var的值 |
| p /x(/d /t /c) var | 以16进制（10进制 2进制 字符格式）显示变量var |
| p \*a@10 | 显示数组a的10个元素 |
| p array[index]@num | 打印数组中从index处开始（index从0开始）的num个元素 |
| p 'file1.c'::var | 打印file1中的静态变量var |
| whatis var | 显示一个变量var的类型 |
| ptype var | 以更详细的方式显示变量var的类型 |
| i variables ^var$ | 查看变量var的定义 |
| gcc -g3 | 使gdb可以调试宏。gcc -g编译的程序不显示宏信息 |
| info macro | 查看这个宏在哪些文件里被引用，以及宏定义 |
| macro | 查看宏展开 |
| set print array on | 显示数组元素时，每个元素占一行 |
| set print elements 0 | 不限制数组的最大显示长度 |
| set print null-stop on | 显示字符串时，遇到结束符则停止显示 |
| set print pretty on | 按格式打印结构体 |
| set print array-indexes on | 打印数组时，显示索引下标 |
| set print union | 打印struct时按格式打印内部的union |
| set follow-fork-mode child | gdb默认只会追踪父进程的运行，子进程会独立运行，要想调试子进程，进入fork()=0逻辑，使用此命令 |
| set detach-on-fork off | 同时调试父子进程，在调试一个进程时，另外一个进程处于挂起状态 |
| x | help x 可以查看x命令用法 |
| x/16xb a | 以16进制格式打印数组a的前16个byte的值。x/ (n,f,u为可选参数)，n: 需要显示的内存单元个数，也就是从当前地址向后显示几个内存单元的内容，一个内存单元的大小由后面的u定义；f：显示格式，可以是x/u/d/o/c等；u：每个单元的大小，按字节数来计算，默认是4 bytes，可以是b:1 byte h:2 bytes     w:4 bytes g:8 bytes |
| command | 自动化调试 |
| save br .gdb_bp | gdb会把本次会话的断点存在.gdb_bp中，启动gdb的时，加上-x .gdb_bp，让gdb把.gdb_bp当做命令文件逐条重新执行 |
| pstree -p 40900 | 查看主线程40900及其子线程间的关系 |
| pstack | 查看线程栈结构 |
| i(info) threads | 查看当前进程中的线程，前面带“\*”为当前线程 |
| thread ID | 切换调试的线程为指定ID的线程 |
| b file.c:100 thread all | 在file.c文件第100行处为所有经过这里的线程设置断点 |
| b frik.c:13 thread 28 if bartab > lim | 为线程28设置条件断点 |
| set scheduler-locking on | 锁定其他线程，只调试当前线程，让其它线程暂停执行 |
| p $\_exitcode | 程序退出码 |
| i signals | 查看如何处理信号 |
| set logging on | 把执行gdb的过程记录下来，默认生成gdb.txt，也可以用“ set logging file file ”改成别的名字 |

# 其它工具  
* cgdb是gdb的增强版，可以显示源码窗口
* 内存泄漏工具：valgrind
