* 简介  

* 原理

* 为什么可以做到高性能 
0. PMD   
DPDK的UIO驱动屏蔽了硬件发出中断，然后在用户态采用主动轮询的方式，这种模式被称为PMD（Poll Mode Driver）。
原来的方式数据：网卡 -> 驱动 -> 协议栈 -> Socket接口 -> 业务。  
DPDK的方式：基于UIO(Userspace I/O)旁路数据，数据从网卡 -> DPDK轮询模式-> DPDK基础库 -> 业务。  
用户态的好处是易用开发和维护，灵活性好。并且Crash也不影响内核运行，鲁棒性强。  
UIO旁路了内核，主动轮询去掉硬中断，DPDK从而可以在用户态做收发包处理。带来Zero Copy、无系统调用的好处，同步处理减少上下文切换带来的Cache Miss。  

1. 采用HugePage减少TLB Miss  
PDK采用HugePage，在x86-64下支持2MB、1GB的页大小，几何级的降低了页表项的大小，从而减少TLB-Miss。并提供了内存池（Mempool）、MBuf、无锁环（Ring）、Bitmap等基础库。根据我们的实践，在数据平面（Data Plane）频繁的内存分配释放，必须使用内存池，不能直接使用rte_malloc，DPDK的内存分配实现非常简陋，不如ptmalloc。  

2. SNA（Shared-nothing Architecture）  
软件架构去中心化，尽量避免全局共享，带来全局竞争，失去横向扩展的能力。NUMA体系下不跨Node远程使用内存。  

3. SIMD（Single Instruction Multiple Data）

4. 不使用慢速API  
比如说 gettimeofday，但不能直接使用 rte_get_tsc_cycles 接口  

5. 编译执行优化

  分支预测

  CPU Cache预取  

  内存对齐  

  常量优化

  使用CPU指令

