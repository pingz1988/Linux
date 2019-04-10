C/C++跨平台IDE，安装、调试都很方便，不需要手写makefile，设置编译项即可生成目标文件 <br/>

* Unicode-UTF8编码问题 <br/>
windows下编辑为Unicode格式的文件，放在Linux下CodeBlocks中编译，会大量警告信息报出“null character(s) igored (enabled default)”，还伴随其它“stray \377”、“stray #”错误.

* 解决GDB不能打印STL容器元素的方法  
1、下载gdb文件 https://sourceware.org/gdb/wiki/STLSupport 里的 stl_views_1.0.3.gdb
2、将下载的gdb文件放到某个目录后，启动gdb调试后，用命令加载stl_views_1.0.3.gdb：source xxx/stl_views_1.0.3.gdb
3、用help命令查看用法，pvector
