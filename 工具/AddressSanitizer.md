## 简介  
Address Sanitizer（ASan）是一个快速的内存错误检测工具。它非常快，只拖慢程序两倍左右（比起Valgrind快多了）。它包括一个编译器instrumentation模块和一个提供malloc()/free()替代项的运行时库。  
从gcc 4.8开始，AddressSanitizer成为gcc的一部分。当然，要获得更好的体验，最好使用4.9及以上版本，因为gcc 4.8的AddressSanitizer还不完善，最大的缺点是没有符号信息。

```shell
# 有些依赖库默认没有安装，需要手动安装
yum install libasan
# 编译时加入指定库选项：
gcc -fsanitize=address -fno-omit-frame-pointer -O1 -g xxx.c
```
