[toc] 

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
rmmod igb_uio
modprobe uio    // 加载 uio 模块 
insmod ./igb_uio.ko  // 进入DPDK编译目录（./x86_64-native-linux-gcc/kmod），加载编译出的 ko 文件
```

* 绑定/解绑网卡  
  + 查看用法  
    dpdk-devbind.py --h
  + 查看网卡绑定状态  
    dpdk-devbind.py -s  
  + 绑定网卡  
    dpdk-devbind.py --bind=igb_uio 05:00.0 05:00.1  
    绑定几个口，eu.ini配置文件中也要配置几个口，否则报错   
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


# 常见问题
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

# 其它命令  

```shell
# numa 及大页信息
numastat -m  
# numa CPU信息
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
# DPDK程序优化  
## 设计  
* 选型  
dpdk支持两种模式，可对比测试各自性能  
* 架构  
设计上尽量避免全局共享、锁。锁对性能有重大影响，可考虑2个替代方案：per-lcore变量、RCU（Read-Copy-Update）算法。  
可借助 rte_ring（rte_ring_create函数、rte_ring_lookup函数、rte_mempool_lookup函数） 实现进程、线程间通信。  

## 编译  
* 内存对齐  
结构体成员需从大到小排序和以及强制对齐 \_\_attribute__((\_\_aligned__(64))) 
* 变量修饰  
1. const  
2. static  
3. 常量优化  
\_\_builtin_constant_p() 来判断值是否常量  
* 函数修饰  
1. 强制内联：inline \_\_attribute__((always_inline)) 
2. static  
3. 函数返回值**仅仅依赖于输入参数**时（不涉及staic变量、全局变量、指针等），用\_\_attribute__((const))修饰函数，编译器会使得相同的输入只会计算一次。比如求一个数的平方。    
4. 编译器对函数参数进行非空检查：\_\_attribute__((nonnull)，也可指定检查第几个参数（参数序号从1开始）\_\_attribute__((nonnull(2)))  
* 分支预测  
#define likely(x) \_\_builtin_expect(!!(x), 1)  
#define unlikely(x) \_\_builtin_expect(!!(x), 0)  

## 编码     
* 需要时，每个核单独使用变量  
用 RTE_PER_LCORE 宏修饰，每个核内的变量独立于其它核，核内变量值不会景程其它核内变量    
* 尽量少用if、switch分支，要使用时，将条件按出现概率从大到小摆放。  
* 多语句宏、想用goto语句时，用do...while(0)  
* Cache预取  
1. rte_prefetch0() // 预取数据想要重复使用  
2. rte_prefetch_non_temporal()  // 预存的数据只想用一次或很“短期”的使用，具体参考dpdk api文档    

* 使用dpdk重新实现的库函数  
  比如 memcpy/malloc/慢速API（如网络序-主机序转换函数） 等其它API使用DPDK实现版本，dpdk作了性能优化，尽量使用rte_malloc/rte_free/rte_memcpy/rte_strcpy这些函数。类似地，还有rte_ring/rte_mempool/rte_hash 等。 

# 实用库

rte_cfgfile.h  // ini 文件解析

rte_string_fns. h  // 字符串分割

rte_log.h  // log

bitmap  // bigmap

timer // 定时器，性能如何？

atomic  // 原子操作

rwlock  // 读写锁，在读多写少的情况下，容易产生写者饥饿

pflock  // 读写交替，解决 rwlock 中的写者饥饿问题

spinlock  // 自旋锁

mcslock  // 可扩展/可伸缩的自旋锁，在CPU/线程局部变量上旋转，避免了昂贵的缓存开销

ticketlock // 公平锁，好比排队，叫到自己的号了才能获致锁（先来先服务）
