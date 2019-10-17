# 简介  
perf 性能剖析工具

# 安装  


# 用法   
perf -h                                         // 帮助信息  
perf -e                                         // 采样事件  
perf -p [pid]                                   // 指定进程  
perf list [hw/sw/cache/pmu]                     // 查看当前系统支持的性能事件，即其它命令中的 -e 参数  
perf test                                       // 对系统进行健全性测试  
perf stat [-a/--all-cpus -C <cpu> -e <event> -p/--pid <pid> -t/--tid <tid>]     // 性能统计  
perf top [-e <event> -p <pid> -K -U -g]         // 实时查看当前系统进程函数占用率情况  
perf lock                                       // 分析锁性能  
perf mem                                        // 分析内存slab性能  
pref record [-e <event> -a/--all-cpus -p <pid> -C <cpu>]    // 记录信息到perf.data，可以精确到函数级别  
perf report                                     // 生成报告  
perf diff                                       // 对两个记录进行diff  
perf evlist                                     // 列出记录的性能事件  
perf annotate                                   // 显示perf.data函数代码  
perf archive                                    // 将相关符号打包，方便在其它机器进行分析  
perf script                                     // 将perf.data输出可读性文本  
perf timechart record                           // 记录事件  
perf timechart                                  // 生成output.svg文档  
    
top适合监控整个系统的性能，stat比较适合单个程序的性能分析，record/report更适合对程序进行更细粒度的分析。  
```shell
# 查看 perf 用法：  
perf -h
# 查看命令的详细用法：  
perf -h record

# 统计cache miss
perf stat -e cache-misses ./a.out

# 以cpu-clock为指标，记录程序各函数调用（-g开关）
perf record -e cpu-clock -g ./a.out

# 记录cache misses
perf record -e cache-misses ./a.out

# 分析上述record命令后的结果
perf report
```

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
