perf 性能剖析工具

# 安装

# 用法  

* 帮助信息  
perf -h  

* 常用命令  
perf -e     // 采样事件  
perf -p [pid]  // 指定进程
perf list  // 查看当前系统支持的性能事件  
perf test  // 对系统进行健全性测试  
perf stat [参数] // 性能统计  
perf top  // 实时查看当前系统进程函数占用率情况  
perf lock  // 分析锁性能  
perf mem  // 分析内存slab性能  
pref record  // 记录信息到perf.data  
perf report生  // 成报告  
perf diff  // 对两个记录进行diff  
perf evlist列出记录的性能事件  
perf annotate显示perf.data函数代码  
perf archive将相关符号打包，方便在其它机器进行分析  
perf script将perf.data输出可读性文本  
perf timechart record记录事件  
perf timechart生成output.svg文档  

* overhead  
perf测试不可避免的会引入额外负荷，有三种形式:  
counting：内核提供计数总结，多是Hardware Event、Software Events、PMU计数等。相关命令perf stat。  
sampling：perf将事件数据缓存到一块buffer中，然后异步写入到perf.data文件中。使用perf report等工具进行离线分析。  
bpf：Kernel 4.4+新增功能，可以提供更多有效filter和输出总结。  

counting引入的额外负荷最小；sampling在某些情况下会引入非常大的负荷；bpf可以有效缩减负荷。  
针对sampling，可以通过挂在建立在RAM上的文件系统来有效降低读写I/O引入的负荷。  
```shell
mkdir /tmpfs
mount -t tmpfs tmpfs /tmpfs
```
