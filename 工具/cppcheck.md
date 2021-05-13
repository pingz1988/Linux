linux

```shell
# 安装
yum install cppcheck
# 编译 cppcheck 源码
make MATCHCOMPILER=yes FILESDIR=/usr/share/cppcheck HAVE_RULES=yes CXXFLAGS="-O2 -DNDEBUG -Wall -Wno-sign-compare -Wno-unused-function"
make install FILESDIR=/usr/share/cppcheck
# 在 cppcheck 的安装目录下使用
cppcheck --enable=all [files or paths]
cppcheck -j4 --enable=all -i/home/zhangping/svn/dns/trunk/dpdk /home/zhangping/svn/dns # -j选项表示线程数，多线程检查时，会跳过未使用函数的检查；-i选项表示排除指定文件或目录，即不检查指定文件或目录
cppcheck -DX file.c # 启用宏定义X，并对文件进行检查
cppcheck -UX file.c # 取消宏定义X，并对文件进行检查
cppcheck file.c 2> err.txt # 输出错误信息
```

windows

**带图形界面运行时，默认启用 -j 选项，即启用多线程检查，会跳过未使用函数的检查**；

在 cmd 中运行以下命令，输出的结果 txt/xml 文件正常；

```powershell
cppcheck --enable=all --xml-version=2 CHECK_PATH 2>OUT.xml
```

**但在 powershell 中运行上述命令时，输出的结果 txt/xml 文件会有多余的命令行信息**。

