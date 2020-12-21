## 内存检测工具
* AddressSanitizer
GCC 4.8及以上版本自带功能，4.8版本支持有限，功能不完善，不能看到符号（函数、行号等），4.9及以上版本很方便。
有些库默认没安装。需要手动安装下：  
yum install libasan  
编译时加入指定库选项：  
gcc -fsanitize=address -fno-omit-frame-pointer -O1 -g mem.c

* Valgrind


## 进程间通信状态
ipcs    # 消息队列、共享内存、信号量
ipcs -m # 共享内存

## 进程使用内存情况
pmap -p 37682 | grep total

## CPU使用
mpstat -P 1,2,3
