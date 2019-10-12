# 编译  
* 安装依赖库 
```shell
yum makecache  
yum install -y gcc gcc-c++  kernel-devel kernel-headers kernel.x86_64 net-tools  
yum install -y numactl-devel.x86_64 numactl-libs.x86_64  
yum install -y pciutils  
yum install kernel-devel-$(uname -r)  
```

* 命令 
```shell
tar xf dpdk-18.11.2.tar.xz  
cd dpdk-stable-18.11.2  
make config T=x86_64-native-linuxapp-gcc  
sed -ri 's,(PMD_PCAP=).\*,\1y,' build/.config  
make  
```
以上编译命令可以直接使用 dpdk-setup.py 完成。

* 模块 
```shell
modprobe uio_pci_generic    // 加载 uio 模块 
```

* 必须导出的变量  
```shell
export RTE_SDK=/root/dpdk-stable-18.11.2  // 安装目录
export RTE_TARGET=x86_64-native-linuxapp-gcc  // T参数
```

# 设置环境  
* 大页  
* 绑定  

#  运行 sample 程序  
* 编译 
```shell
cd examples/helloworld  
make 
```

* 绑定网口到 DPDK 
```shell
cd usertools  
./dpdk-devbind.py --status   // 查看网口绑定状态   
./dpdk-devbind.py --bind=uio_pci_generic ens33   // 绑定网口
```

# 问题
* 缺少numa.h  
yum install numactl-devel*x86_64  

* make: *** /lib/modules/3.10.0-693.el7.x86_64/build: 没有那个文件或目录。 停止。
```shell
yum install gcc kernel-devel  
cd /lib/modules/3.10.0-693.el7.x86_64  
rm ./build  
ln -s /usr/src/kernels/3.10.0-693.el7.x86_64/ ./build （/usr/src/kernels/3.10.0-693.el7.x86_64/ 为当前机器安装开发库后已存在的目录）   
```

* 缺少pcap.h  
yum -y install flex bison   
从 http://www.tcpdump.org/ 下载最新版本 libpcap  
./configure  
make && make install

# 使用  
* 使用前检查项  
```shell
# numa 统计
numastat -m  

# Build DPDK target.  
cd dpdk_folder  
make install T=x86_64-native-linux-gcc -j  

# Get the hugepage size.  
awk '/Hugepagesize/ {print $2}' /proc/meminfo  

# Get the total huge page numbers.  
awk '/HugePages_Total/ {print $2} ' /proc/meminfo  

# Unmount the hugepages.  
umount `awk '/hugetlbfs/ {print $2}' /proc/mounts`  

# Create the hugepage mount folder.  
mkdir -p /mnt/huge  

# Mount to the specific folder.  
mount -t hugetlbfs nodev /mnt/huge  

# 查看cpu布局  
lscpu   
```
