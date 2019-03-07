尽量避免使用和平台相关的代码，这样的程序才能快速、方便的进行移植。

# 常识
* 路径分割符 <br/>
“\”在 linux 上不支持，需要都改为“/”
* 文件名 <br/>
Windows 下文件名大小写不敏感，而在 linux 下文件名大小写敏感
* gcc编译代码更为严格 <br/>
* 字符集

# 基本类型
程序里不能使用Windows特有的数据类型，例如，FAR PASCAL、HWND、HMENU、HFONT等，因为这些类型在Linux下无法找到替代它们的类型。

# 宏定义
一些宏定义Windows下有而Linux下没有，需要自己添加到头文件中。

# 关于API
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

* 时间操作
