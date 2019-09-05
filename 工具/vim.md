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
* 指定行间替换
:100,200s/vbird/VBIRD/g

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

* 删除光标所在到第一行的所有数据  
d1G  

* 删除光标所在到最后一行的所有数据
dG  

* 删除字符  
x, X  在一行字当中，x 为向后删除一个字符 (相当于 [del] 按键)， X 为向前删除一个字符(相当于 [backspace] 亦即是退格键)   
nx n 为数字，连续向后删除 n 个字符。举例来说，我要连续删除 10 个字符

* 删除游标所在处，到该行的最后一个字符  
d$  

* 删除游标所在处，到该行的最前面一个字符
d0

* 撤销  
u

* 重复执行
[Ctrl]+r

* 比较文件  
vim -d file1 file2
