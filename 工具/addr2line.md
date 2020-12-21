通过地址显示函数名和行号，**编译时需要-g参数**。自测有效。  
**在程序出现 core dump 时，很有用**，此时 gdb bt 命令无法显示堆栈，只有地址信息。

```powershell
addr2line 0x417ab3 -e /mvtech/CSMS/bin/csms -f -C -s
```

例如有如下报错信息：  
```powershell
./csms[0x417ab3]  
./csms[0x512727]  
./csms[0x426ca2]  
./csms[0x42656d]  
./csms[0x57783a]  
./csms[0x577b01]  
/lib64/libc.so.6(__libc_start_main+0xf5)[0x7fd9c8b35b35]  
./csms[0x416c19]
```

使用上述 addr2line 命令的显示结果： 
```powershell
RequestLogger::~RequestLogger()  
request_logger.cpp:206
```
