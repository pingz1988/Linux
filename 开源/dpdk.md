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
以上编译命令可以直接使用 dpdk-setup.py\/dpdk-setup.sh 完成。

# 设置环境  

* 必须导出的变量  
```shell
export RTE_SDK=/root/dpdk-stable-18.11.2  // 安装目录
export RTE_TARGET=x86_64-native-linux-gcc  // T参数
```

* 设置大页 
```
./dpdk-setup.sh  # 根据提示选择设置大页项，输入数量
```

* 加载驱动对应的模块 
```shell
modprobe igb_uio    // 加载 uio 模块 
insmod ./igb_uio.ko  // 进入DPDK编译目录（./x86_64-native-linux-gcc/kmod），加载编译出的 ko 文件
```

* 绑定/解绑网卡  
  + 查看用法  
    dpdk-devbind.py --h
  + 查看网卡绑定状态  
    dpdk-devbind.py -s  
  + 绑定网卡  
    dpdk-devbind.py -b igd_uio 05:00.0 05:00.1
  + 解绑网卡  
    dpdk-devbind.py -u

#  运行 sample 程序  

* 编译 
```shell
cd examples/helloworld  
make 
``` 

* 运行程序  

* 查看结果/状态/性能  


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

# 其它  

```shell
# numa 统计
numastat -m  
numactl -H  

# Build DPDK target.  
cd dpdk_folder  
make install T=x86_64-native-linux-gcc -j  

# Get the hugepage size.  
awk '/Hugepagesize/ {print $2}' /proc/meminfo  

# Get the total huge page numbers.  
awk '/HugePages_Total/ {print $2} ' /proc/meminfo  

# Unmount the hugepages.  
umount `awk '/hugetlbfs/ {print $2}' /proc/mounts`  

# 设置Numa节点nodo0的大页数量为10，每个大页大小由系统指定（参见上面“Get the hugepage size”命令）; node1类似相同操作。  
echo 10 /sys/devices/system/node/node0/hugepages/hugepages-1048576kB/nr_hugepages

# Create the hugepage mount folder.  
mkdir -p /mnt/huge  

# Mount to the specific folder.  
mount -t hugetlbfs nodev /mnt/huge  

# 查看cpu信息，包括布局、cache等  
lscpu   

# 使用CAT功能，需要libpqos.so，编译 intel-cmt-cat-master/pqos 时需设置 libpqos.so 目录  
export LD_LIBRARY_PATH=/home/pingz/intel-cmt-cat-master/lib
```
