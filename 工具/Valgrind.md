* 安装  
yum install valgrind

* 准备工作  
编译 debug 版程序 xxx_d 

* 内存泄漏检查  
valgrind --leak-check=full --show-leak-kinds=all ./xxx_d  
valgrind 有几种工具，默认启用内存泄漏工具
