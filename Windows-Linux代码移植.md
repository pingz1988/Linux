尽量避免使用和平台相关的代码，这样的程序才能快速、方便的进行移植。如果必须要用OS相关API，可以先考虑跨平台的第三方库。

# 开发环境
| 类别 | Win32 | Linux | 跨平台 |
| ------ | ------ | ------ | ------ |
| IDE | VS | 无官方版 | QT/CB |
| 编译方式 | VS/Makefile | Makefile | cmake/gyp |
| 代码编辑 | IDE/SourceInsingt | 无主流 | Vim/Emacs/Sublime Text/Eclipse |
| 编译器 | cl/devenv/nmake | gcc/make | gcc/clang |
| 调试 | VS/WinDbg | GDB | - |
| 打包 | Windows Installer/第三方工具 | dpkg/checkinstall | - |

# 基础
* 路径分割符“\”在 linux 上不支持，需要都改为“/”
* Windows 下文件名大小写不敏感，而在 linux 下文件名区分大小写
* windows \r\n换行，linux \n换行
* 不要假定可执行文件一定有.exe的扩展名
* long类型的变量在32位和64位Windows上都是4个字节，而在64位Linux系统上占8字节
* Linux下gcc/g++不认带BOM标记的源文件
* gcc编译代码更为严格 <br/>
  
# 函数参数
  调用函数时的形参类型和函数声明中参数列表的类型不匹配linux会报错，有无const或者是否是引用参数，都需要严格对应。

# 字符串
* 由于vc中的默认源代码编码为GBK，使用GCC编译时，需要指定源代码编码名称，否则以GCC默认的UTF8解码会出现乱码或者报错，可通过参数-finput-charset=GBK或者手动另存文件格式解决。
* C运行库中的mbstowcs和wcstombs是locale相关的，linux下默认的是UTF8，所以这里也要设置，否则运行时会出现转码错误。可在程序开始时设置环境变量LC_ALL=zh_CN.GBK，或者在运行中调用setlocale。
* 需要注意wchart_t在Windows和Linux下字符长度不一样，wchar_t不能以空字符来初始化。

# 数据类型
  程序里不能使用Windows特有的数据类型，例如，FAR PASCAL、HWND、HMENU、HFONT等，因为这些类型在Linux下无法找到替代它们的类型。

# 异常处理
  SEH 结构化异常处理是windows中的机制，linux中没有。  
  LINUX下是不支持抛出异常的，如果继承自标准库的异常类写自己的异常类的时候，在Linux下，子类的析构函数中就需要表明不抛出异常，所以析构函数后面加上throw()就可以了。

# 语法
  1、两个连续>>之间必须要空格，否则报错  
  2、gcc不支持写法 for(int i=0;,,)，变量i的声明要放到for外面
  3、要使用C++11中的特性，如auto关键字，gcc需要开启c++11编译项.  
  4、linux没有关键字”__in“、”__out“.  
  5、一些宏定义Windows下有而Linux下没有，需要自己添加到头文件中。  
  6、#prgram once预编译指令在linux下并不起作用.  
  7、在父类中用typedef定义的类型，在子类并不能直接使用
  
# 数据处理
  使用通用数据描述（XML、JSON、Google ProtocolBuf），持久化存储，字符编码/多语言/国际化（ICU），图片解码，音频/视频解码，资源管理，log等

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
| GetPrivateProfileString | 自实现 |

windows中对ini文件进行操作的所有函数在linux下都没有对应函数.
wfstream.open() 第一个参数只能传入char\*或string.

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
3、 size_t在printf中的表示，Linux是%zu，Windows是%lu
<br/> 

* 其它

| Win32 | Linux |
| ------ | ------ |
| \_wsystem | 无 |
| GetLaseError | 无 |

# 测试工具
  各平台都有专门的代码测试、格式化工具
