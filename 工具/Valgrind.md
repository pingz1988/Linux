* 安装  
yum install valgrind

* 准备工作  
编译 debug 版程序 xxx_d 

* 内存泄漏检查命令  
valgrind --leak-check=full --show-leak-kinds=all ./xxx_d  

* 说明  
valgrind 有几种工具，默认启用内存泄漏工具 Memcheck。  
- Memcheck 工具主要检查下面的程序错误：  
  - 1.使用未初始化的内存 (Use of uninitialised memory)
  - 2.使用已经释放了的内存 (Reading/writing memory after it has been free’d)
  - 3.使用超过 malloc分配的内存空间(Reading/writing off the end of malloc’d blocks)
  - 4.对堆栈的非法访问 (Reading/writing inappropriate areas on the stack)
  - 5.申请的空间是否有释放 (Memory leaks – where pointers to malloc’d blocks are lost forever)
  - 6.malloc/free/new/delete申请和释放内存的匹配(Mismatched use of malloc/new/new [] vs free/delete/delete [])
  - 7.src和dst的重叠(Overlapping src and dst pointers in memcpy() and related functions)
