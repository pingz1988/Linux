* ubuntu下最好安装开发环境，安装过程中可能由于网络原因安装失败：  
sudo apt-get install  build-essential  
也可以单个包进行安装，如：  
sudo apt-get install libc6-dev   

* 缺少io.h文件：  
  使用locate命令查找io.h，如果有这个文件，拷贝到/usr/include/sys目录下，编译时-I包含这个目录 

* linux 32/64位动态库如何编译  
-m32/-m64 ？
32位系统编译32位.so，64位编译64位.so ？

* 查看.so有哪些函数（.a使用nm -g **.a）  
nm -D **.so  
筛选／查找： nm **.so | grep XX

* 查看.so是32还是64位？
objdump -a *.so

* 调用.so：
使用dlopen等函数调用.so时，在链接成目标时需要-ldl参数  

* 找不到pthread相关符号时，需要链接-lpthread

* 多个.a合成一个.a，即用多个.a编译成一个.a：
ar x libtest1.a		//导出.a中的符号到.o  
ar x libtest2.a  
ar rc liball.a *.o  //多个.o合成.a  

* 查看.so依赖库：
ldd x.so  
如果有找不到的依赖库拷贝至/usr/lib目录

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
| backtrace（或bt）|	查看各级函数调用及参数 |
| finish	| 连续运行到当前函数返回为止，然后停下来等待命令 |
| frame（或f） 帧编号	| 选择栈帧 |
| info（或i） locals	| 查看当前栈帧局部变量的值 | 
| list（或l）	| 列出源代码，接着上次的位置往下列，每次列10行 |
| list 行号	| 列出从第几行开始的源代码 |
| list 函数名 | 列出某个函数的源代码 |
| next（或n） |	执行下一行语句 |
| print（或p） |	打印表达式的值，通过表达式可以修改变量的值或者调用函数 |
| quit（或q） |退出gdb调试环境 |
| set var	| 修改变量的值 |
| start	| 开始执行程序，停在main函数第一行语句前面等待命令 |
| step（或s） | 执行下一行语句，如果有函数调用则进入到函数中 |
