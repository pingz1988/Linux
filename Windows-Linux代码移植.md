# 常识
* 路径分割符 <br/>
“\”在 linux 上不支持，需要都改为“/”
* 文件名 <br/>
Windows 下文件名大小写不敏感，而在 linux 下文件名大小写敏感
* gcc编译代码更为严格 <br/>
* 字符集

# 基本类型


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
