GCC 4.8及以上版本自带该工具，可以内存进行检测，比valgrind好用，4.8版本支持有限，功能不完善，不能看到符号（函数、行号等），4.9及以上版本很方便。  '
有些库默认没安装，需要手动安装下：
```shell
yum install libasan
# 编译时加入指定库选项：
gcc -fsanitize=address -fno-omit-frame-pointer -O1 -g xxx.c
```
