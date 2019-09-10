* 安装  
yum install valgrind

* 准备工作  
编译debug版程序  

* 内存泄漏检查  
valgrind --leak-check=full --show-leak-kinds=all ./xxxExe
