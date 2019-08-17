# 插件

主要用如下几个插件：<br/>
* pathogen<br/>
让每一个插件占有一个独立的目录，解决了文件分散的问题<br/>
* ctags<br/>
方便代码阅读的工具，vim中已默认安装<br/>
* taglist<br/>
基于ctags，以分割窗口形式显示当前的代码结构概览，增加代码浏览的便利程度<br/>
* winmanager<br/>
文件管理器<br/>
* cvim<br/>

# 常用命令  

* 替换全部字符串  
:%s/old_str/new_str/gg

* 替换路径  
:%s#/home/szs/stb/stsdk/A36/rpmbuild/BUILD#/home/yinjiabin/qt#g

* 复制粘贴当前行  
yy
p

* 复制粘贴块  
v
yy
p

* 删除当前行  
dd

* 撤销  
u

* 比较文件
vim -d file1 file2
