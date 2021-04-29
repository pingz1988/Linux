源码编译

1. 下载安装 cmake（版本为v3以上），wget https://cmake.org/files/v3.5/cmake-3.5.2.tar.gz，tar zxvf cmake-3.5.2.tar.gz && cd cmake-3.5.2 && ./bootstrap --prefix=/usr && make && make install && cmake -v
2. 删除软链接 /urs/bin/python，升级Python为python3
3. 下载 wireshark 源码，解压
4. 进入解压目录，mkdir build && cd build && cmake ..
5. 如果提示缺少所需库，手动安装，全安装后，执行 cmake..  无报错，进入下一步
6. make && make install
7. cd run
8. ./wireshark 
9. 附加进程调试，gdb -p  `pidof wireshark  `