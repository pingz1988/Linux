尽量避免使用和平台相关的代码，这样的程序才能快速、方便的进行移植。如果必须要用OS相关API，可以先考虑跨平台的第三方库。

# 基础
* 路径分割符 <br/>
“\”在 linux 上不支持，需要都改为“/”
* 文件名 <br/>
Windows 下文件名大小写不敏感，而在 linux 下文件名大小写敏感
* windows \r\n换行，linux \n换行
* gcc编译代码更为严格 <br/>

# 字符串编码
* 由于vc中的默认源代码编码为GBK，使用GCC编译时，需要指定源代码编码名称，否则以GCC默认的UTF8解码会出现乱码或者报错，可通过参数-finput-charset=GBK或者手动另存文件格式解决。
* C运行库中的mbstowcs和wcstombs是locale相关的，linux下默认的是UTF8，所以这里也要设置，否则运行时会出现转码错误。可在程序开始时设置环境变量LC_ALL=zh_CN.GBK，或者在运行中调用setlocale。
* 需要注意wchart_t在Windows和Linux下字符长度不一样。

# 数据类型
程序里不能使用Windows特有的数据类型，例如，FAR PASCAL、HWND、HMENU、HFONT等，因为这些类型在Linux下无法找到替代它们的类型。

# 宏定义
一些宏定义Windows下有而Linux下没有，需要自己添加到头文件中。

# 异常处理
SEH 结构化异常处理是windows中的机制，linux中没有。

# 模板
  1、两个连续>>之间必须要空格，否则报错  
  2、

# API
Windows下基于MFC、基于消息、基于注册表的API等在Linux下都是没有的。<br/>
* 字符串 <br/>

| Win32 | Linux |
| ------ | ------ |
| WideCharToMultiByte | wcstombs |
| MultiByteToWideChar | mbstowcs |
| \_stricmp | strcasecmp |
| strtok_s | strtok_r |
| sprintf_s | snprintf |
| vsprintf_s | vsnprintf |
| strcpy_s | strncpy |
| strcat_s | strncat |
| \_tcsnpy_s | wcsnpy |
| vsprintf_s | vsnprintf |
| \_tcslen | wcslen |
| \_wtoi | 无 |
| strcpy_s | strcpy |
| strncpy_s | strncpy |
| wcscpy_s | wcscpy |
| wcsncpy_s | wcsncpy |
| \_tcsncpy_s | wcsncpy |
| \_strlwr_s | 无 |
| \_strupr_s | 无 |
| \_wcslwr_s | 无 |
| \_wcsupr_s | 无 | 

* 文件操作

| Win32 | Linux |
| ------ | ------ |
| \_access | access |
| \_mkdir | mkdir |
| SHCreateDirectoryEx | mkdir |
| CreateFile | fopen |
| DeleteFile | remove |
| FlushFileBuffers | fflush |
| CloseHandle | fclose |
| \_trename | rename |
| GetCurrentDirectory | getcwd |
| SetCurrentDirectory | chdir |
| GetModuleFileName | 自实现 |
| PathFileExists | access |
| FindFirstFile | 用readdir实现 |
| PathFindFileName | basename |
| PathFindExtension | 自实现 |
| \_stat | stat |
| \_ftelli64 | ftello |
| \_fseeki64 | fseeko |

* 内存操作

| Win32 | Linux |
| ------ | ------ |
| memcpy_s | memcpy |

* 时间操作

| Win32 | Linux |
| ------ | ------ |
| GetLocalTime | localtime |
| QueryPerformanceFrequency | 无 |

* 格式化

| Win32 | Linux |
| ------ | ------ |
| sscanf_s | sscanf |
| \_snscanf_s | sscanf |
| vsprintf_s | vsnprintf |
| vswprintf_s | vsnprintf |
| "%I64d" | "%lld" |
| "%I64u" | "%I64lu" |

注意可变参数的传递：  
1、 向函数传递可变参数时，不能只传参数'format...'，还需要传入参数列表'va_list'，否则结果不可预期。  
2、 格式化宽字符、字符串时，需要添加'l'前缀，使用%lc、%ls  
<br/> 

* 控制台操作 <br/>
linux不支持控制台

* 其它

| Win32 | Linux |
| ------ | ------ |
| \_wsystem | 无 |
| GetLaseError | 无 |
