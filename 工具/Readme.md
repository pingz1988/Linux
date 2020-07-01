## 内存检测工具
* AddressSanitizer
GCC 4.8及以上版本自带功能，4.8版本支持有限，功能不完善，不能看到符号（函数、行号等），4.9及以上版本很方便。
有些库默认没安装。需要手动安装下：
yum install libasan

* Valgrind
