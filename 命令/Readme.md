```shell
* 查看进程号  
pidof xxx

* 查看进程启动的线程
ps -T -p xxxPID

* 查看进程使用cpu情况  
pidstat -p xxxPID -t 1

* 查看进程内存情况  
pidstat -p xxxPID -r -t 1

* 抓包  
tcpdump -i lo tcp and port 50000 -vv -w 50000.pcap

* 允许生成core dump文件  
ulimit -c unlimited
```
