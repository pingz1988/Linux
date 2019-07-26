* 查看进程使用cpu情况
pidstat -p `pidof 进程名` -t 1

* 查看进程内存情况
pidstat -p `pidof 进程名` -r -t 1

* 抓包
tcpdump -i lo tcp and port 50000 -vv -w 50000.pcap
