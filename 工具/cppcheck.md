## linux

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
cppcheck . --enable=all 2>err.txt  # 递归检查当前目录下所有文件，并将错误信息输出到txt文件
cppcheck . --enable=all --xml 2>err.xml   # 输出为xml
cppcheck --enable=all --xml-version=2 CHECK_PATH 2>OUT.xml  # 检查CHECK_PATH，并将错误信息输出到xml文件
# htmlreport/cppcheck-htmlreport 脚本需指定全路径，此脚本位于cppcheck源码目录中
xxx/htmlreport/cppcheck-htmlreport --file=err.xml --report-dir=cppcheck  # 将err.xml转换成html，存放到F:/cppcheck
```

## windows

**注意：带图形界面运行时，默认启用 -j 选项，即启用多线程检查，会跳过未使用函数的检查**

在 cmd 中运行以下命令，输出的结果 txt/xml 文件正常；

```powershell
# cppcheck 可在非安装目录运行
cppcheck . --enable=all 2>F:/err.txt  # 递归检查当前目录下所有文件，并将错误信息输出到txt文件
cppcheck . --enable=all --xml 2>F:/err.xml   # 输出为xml
cppcheck --enable=all --xml-version=2 CHECK_PATH 2>OUT.xml  # 检查CHECK_PATH，并将错误信息输出到xml文件
cppcheck . -DEU_SVN_NUM --enable=all --xml 2>F:/cppcheck/err.xml  # 启用宏 EU_SVN_NUM
# htmlreport/cppcheck-htmlreport 脚本需指定全路径，生成html格式报告
d:/htmlreport/cppcheck-htmlreport --file=F:/cppcheck/err.xml --report-dir=F:/cppcheck  # 将err.xml转换成html，存放到F:/cppcheck. 注意，--file指定的文件要使用上述命令生成，此命令只做 xml -> html 转换
```

**但在 powershell 中运行上述命令时，输出的结果 txt/xml 文件会有多余的命令行信息，所以最好不用 powershell 运行 cppcheck**

