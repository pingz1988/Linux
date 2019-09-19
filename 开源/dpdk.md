# 编译准备  
* 安装依赖库  
yum makecache  
yum install -y gcc gcc-c++  kernel-devel kernel-headers kernel.x86_64 net-tools  
yum install -y numactl-devel.x86_64 numactl-libs.x86_64  
yum install -y pciutils  
yum install kernel-devel-$(uname -r)  

* 安装命令  
tar xf dpdk-18.11.2.tar.xz  
cd dpdk-18.11.2
make install T=x86_64-native-linuxapp-gcc  

* 缺少numa.h  
yum install numactl-devel*x86_64  

* make: *** /lib/modules/3.10.0-693.el7.x86_64/build: 没有那个文件或目录。 停止。  
yum install gcc kernel-devel  
cd /lib/modules/3.10.0-693.el7.x86_64  
rm ./build  
ln -s /usr/src/kernels/3.10.0-693.el7.x86_64/ ./build （/usr/src/kernels/3.10.0-693.el7.x86_64/ 为当前机器安装开发库后已存在的目录）   

* 缺少pcap.h  
yum -y install flex bison   
从 http://www.tcpdump.org/ 下载最新版本 libpcap  
./configure
make && make install
