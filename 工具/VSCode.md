## 快捷键

| 快捷键 | 描述 |
| ------ | ------ |
| Ctrl + P | 直接输入字符串，搜索文件名；输入@查找符号（变量/函数）；输入?，查看帮助信息 |
| Ctrl + Shift + P | 打开命令面板，搜索命令；如输入“c/c++”，可选“择编辑配置json”，开启某个宏 |
| Ctrl + G | 在当前文件中，跳转到行号 |
| Ctrl + T | 在整个工作区中，搜索符号(变量及函数) |
| Ctrl + Shift + O | 在当前文件中，搜索符号(变量及函数) |
| Ctrl + K + F | 格式化选中内容 |
| Ctrl + K + 0 | （数字0）折叠所有 |
| Ctrl + K + J | 展开所有 |
| Shift + Alt + F | 格式化整个文档 |
| Ctrl + Y | 恢复 |
| Ctrl + W | 关闭当前窗口（文件）|
| Ctrl + F4 | 关闭当前文件 |
| Alt + ← | 向前导航编辑位置 |
| Alt + → | 向后导航编辑位置 |
| Alt + ↑ | 将当前行上移一行 |
| Alt + ↓ | 将当前行下移一行 |
| Shift + Alt + ↑ | 向上复制一行 |
| Shift + Alt + ↓ | 向下复制一行 |
| Ctrl + L | 选中当前行 |
| Shift + Alt + → | 展开选中内容 |
| Shift + Alt + ← | 缩小选中内容 |
| Ctrl + Shift + K | 删除当前行 |
| Ctrl + Enter | 在当前行下插入新行 |
| Ctrl + Shift + Enter | 在当前行上插入新行 |
| Ctrl + ] | 向左缩进 |
| Ctrl + \[ | 向右缩进 |
| Shift + Alt + F | 添加/取消注释 |
| Ctrl + / | 向左缩进 |
| Ctrl + Shift + \[ | 以递归的方式折叠代码 |
| Ctrl + Shift + ] | 向左缩进 |
| Ctrl + \[ | 以递归的方式展开代码 |
| Ctrl + K + J | 以递归的方式展开代码 |
| Ctrl + \[ | 展开代码 |
| Ctrl + Shift + Y | 打开调试控制台 |
| Ctrl + B | 显示/隐藏侧边栏 |
| Shitft + F12 | 查找所有引用 |
| Ctrl + Shitft + V | 预览markdown文件 |

## 常用插件
* 中文  
* C/C++
* C/C++ Advanced Lint
* 代码提示 c/c++ snippets
* 括号颜色  Bracket Pair Colorizer
* 注释 Better comments
* Git代码管理 GitLens
* SVN代码管理 TortoiseSVN
* 书签 Bookmarks
* Remote SSH  
远程调试插件，左侧菜单栏-远程资源管理器-新建连接-选择配置文件-输入登录用户名、密码，连接成功后，可进行远程操作。保存登录密码，在windows主机上输入cmd命令（win10自带ssh client, win7需要手动安解压安装包到 C:\Program Files\OpenSSH,并把这个目录加到系统环境变量path）：  
```shell
ssh-keygen -t rsa -b 4096
SET REMOTEHOST=root@192.168.1.245
scp C:\Users\Administrator\.ssh\id_rsa.pub %REMOTEHOST%:~/tmp.pub
ssh %REMOTEHOST% "mkdir -p ~/.ssh && chmod 700 ~/.ssh && cat ~/tmp.pub >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys && rm -f ~/tmp.pub"
```
* power mode
在“设置”中直接搜索如下配置项进行设置
```json
{
    //powser mode   
  "powermode.enabled": true,
  //样式
  "powermode.presets": "fireworks",
  // 时间间隔
  "powermode.comboTimeout":8,
  // 抖动
  "powermode.enableShake": false,
  "powermode.backgroundMode": "mask",
}
```

- 文件（代码）同步 sftp

在vscode中实现远程同步（本地->远程，远程->本地）文件或目录，安装 sftp 插件后，在 sftp.json 中配置如下（uploadOnSave为true表示保存即上传）：

```json
{

  "name": "编译服务器",

  "host": "10.10.64.214",

  "protocol": "sftp",

  "port": 22,

  "username": "root",

  "password": "topteng1985",

  "remotePath": "/home/zhangping/svn/cmcu_eu_re_ver/code",

  "uploadOnSave": true, 

  "ignore": [

​    "**/.vscode/**",

​    "**/.git/**",

​    "**/.DS_Store"

  ],

  "watcher": {

​    "files": "*",

​    "autoUpload": false,

​    "autoDelete": false

  }

}
```

注意：

第一次配置后上传文件到远程目录，会报“No such file” 的错误，需要修改文件`C:\Users\Administrator\.vscode\extensions\liximomo.sftp-1.12.9\node_modules\ssh2-streams\lib\sftp.js`，搜索`options.emitClose = false;` 在搜到的两处语句之后，增加一行 `options.autoDestroy = false;` 重启 vscode 即可正常上传。
