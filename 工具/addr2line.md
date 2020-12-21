```shell
# 通过地址显示函数名和行号，编译时需要-g参数。自测有效。
# 在程序出现 core dump 时，很有用，此时 gdb bt 命令无法显示堆栈，只有地址信息。
addr2line 0x417ab3 -e xxxExe -f -C -s
```
