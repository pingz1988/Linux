* 安装  
yum install valgrind

* 内存泄漏检查  
valgrind --leak-check=full --show-leak-kinds=all ./xxxExe
