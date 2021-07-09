## 基本命令
| 命令                    | 用途                                                         |
| ----------------------- | ------------------------------------------------------------ |
| cd                      | 切换到当前用户的 home，相当于 cd ~                           |
| cd -                    | 切换到上次 cd 过的目录                                       |
| l.                      | 只显示隐藏目录和隐藏文件                                     |
| ll -a                   | 显示所有文件，包括隐藏目录和隐藏文件                         |
| ll -aF                  | -F：显示区分目录和文件，显示目录时带/，软链接时带~           |
| ls -l \|head -n 5 | 查看 ll 前5行 |
| cat -b file.txt         | 显示行号及内容          |
| cat 1.txt 2.txt 3.txt > all.txt         | 合并多个文件到一个文件          |
| mkdir -p dir1/dir2/dir3 | 新建多级目录                                                 |
| cp -r dir dst           | 递归拷贝目录                                                 |
| cp a.log{,.bak} | 拷贝文件时追加.bak后缀                                                |
| cp a.log{,\_\`date +%m%d\`} | 拷贝文件时追加日期后缀                                    |
| ctrl + r                | 搜索历史命令                                                 |
| ctrl + l                | 清屏                                                         |
| tar zcvf xxx.tar.gz xxx | 压缩文件/目录                                                |
| tar zxvf xxx.tar.gz | 解压文件                                                |
| tar xf \*.tar.xz         | 解压 .tar.xz 文件                                            |
| gzip -d \*.gz            | 解压 .gz                                                     |
| zip out xxx         | 压缩 xxx 成 out.zip（自动加zip后缀）                                          |
| zip -j out.zip /home/pingz/xxx.txt | 只压缩文件到zip，压缩文件中不包含原有目录 |
| unzip xxx.zip | 解压zip文件 |
| rz -e xxxFile          | rz 传输乱码时需加 -e 选项(准备上传的文件最好不要放在中文目录下)                                                     |
| rename str1 str2 str1*  | 把 str1 开头的文件名重命名为 str2 开头                       |
| rename .txt .log \*.txt  | 把以.txt 为后缀的文件名修改为 .log 后缀                      |
| more/less fileName      | 查看多页文件，空格向下一屏，b 向上一屏。less 分页查看文件内容（不加载整个文件）。more 命令会加载整个文件                       |
| aa && ls                | 执行 aa 命令成功后，接着执行 ls 命令                         |
| aa & ls                 | 执行 aa 命令后，就接着执行 ls 命令                           |
| aa \|\| ls              | 并行执行 aa 和 ls，没有先后顺序                              |
| > file.txt              | 新建/清空文件，eg: echo "abcd" > file.txt  # 写入内容;  > file.txt  # 清空内容 |
| >> file.txt             | 新建/追加内容到文件，用法同上                                |
| mkdir \`date +%y%m%d\`  | 创建以当前日期命名的目录,注意 date 后的空格只能这么写                                     |
| split --numeric-suffixes=1 -l100 http.log | 按第个文件100行分割文件，文件名后缀从数字1开始 |
| split -b 1m http.log | 按第个文件大小为1M来分割文件，类似地，单位可指定为k/m/g/t等 |
| grep -C 2 str file1 | 查看文件file1中匹配str以及前后2行 |
| grep -rn "some text" | 在当前目录，递归搜索文本内容，并显示匹配行号 |
| grep -E "str1\|str2" file1 | 查看文件file1中匹配str1或str2的行 |
| grep abc$ file1 | 查看文件中以abc结尾的行,fgrep命令类似 |
| pgrep str | 模糊查找进程名中含有str的进程PID，-l 列出PID及进程名；-a 参数显示进程启动完整命令；-w 列出进程所有TID |
| tail -f xxx.log  | 跟踪/滚动查看文件                                           |
| lsof 命令 | 查看系统打开的文件，lsof -c -p 1234，显示进程号1234打开的文件， lsof /filepath/file，查看打开该文件的进程； lsof -c mysql，查看以mysql开头的进程名所打开的文件； lsof +d /usr/local/ 显示目录下被进程开启的文件；lsof -i[46] [protocol][@hostname|
| journalctl -a -f -u cpftp_upload_du | 跟踪/滚动查看程序执行 |
| nl file | 加行号显示文件 |
| wc | 统计字符数/行数 |
| sort |  |
| uniq | 去除文件中相邻的重复行 |
| diff |   |
| netstat | 显示与IP、TCP、UDP和ICMP协议相关的统计数据 |
| at | 在一个指定的时间执行一个指定任务，只能执行一次 |
| watch -n5 ls | 每5s执行一次 ls 命令，默认2s执行一次 |


## 程序
```shell
man ascii  # 查看ascii码表
date +%s   # 当前时间的时间戳
date +%Y-%m-%d %H:%M:%S.%3N  # 带3位毫秒时间

&	# 加在一个命令的最后，可以把这个命令放在后台执行
nohup	# 不挂断的运行命令
ctrl + z   # 将当前程序放到后台运行
fg	# 将后台程序调至前台运行，如有多个在后台运行的程序，可用 jobs 查看 objnum，然后 job %N

alias cd2tmp='cd /home/pingz/temp'  # 设置临时别名（常用固定命令可用别名来简化）
# 设置永久别名（对当前用户一直生效）
vim ~/.bashrc
alias cd2tmp='cd /home/pingz/temp'  # alias命令追加到.bashrc文件末尾
source ~/.bashrc  # 立即生效
# 取消别名
unalias cd2tmp
# 查看别名
alias
alias | grep XXX
# 使用命令本身而不是别名
\vi  # 在命令前使用反斜线\

# 查看环境变量  
env  
echo $(xxxVar)  

# top命令相关
top -p PID # 查看进程占用资源情况
-b 批处理
-c 显示整个命令行而不只是显示命令名
-d 间隔时间（秒）
-I 忽略失效过程
-s 保密模式
-S 累积模式
-i<时间> 设置间隔时间
-u<用户名> 指定用户名
-p<进程号> 指定进程
-n<次数> 循环显示的次数
-H -p PID top显示进程线程

# 追踪 cpftp_upload_du 程序日志
journalctl -afu cpftp_upload_du

# 查看进程号  
pidof xxx  
ps -ef | grep xxxExe | grep -v grep | awk '{print $2}'
# 查看进程中的线程
ps -T -p PID

# 进程id作为其它命令的参数
pidstat -p `pidof xxxExe` -t  
pidstat -p `ps -ef | grep xxxExe | grep -v grep | awk '{print $2}'` -t  

# 查看进程启动路径
ll /proc/`pidof xxxExe`

# 获取进程当前路径  
sprintf(link, "/proc/%d/exe", getpid()); 
int i = readlink(link, path, sizeof(path));
if (-1 == i)
{
	print_screen("get current path err: %s\n", strerror(errno));
	return -1;
}
path[i] = '\0';

# 查看进程启动的线程
ps -T -p xxxPID

# 查看进程使用cpu情况  
pidstat -p xxxPID -t

# 查看进程内存情况  
pidstat -p xxxPID -r -t 1  

# 查看进程启动时间
ps -eo pid,lstart,etime,cmd | grep xxxKeyword  

# 查看逻辑核等信息  
# 两个的processor下的core id相同表示支持超线程，且它们属于同一个物理核      
cat /proc/cpuinfo 
# CPU总核数 = 物理CPU个数 * 每个物理CPU的核数  
cat /proc/cpuinfo| grep "physical id"| sort| uniq| wc -l  // 查看物理CPU个数  
cat /proc/cpuinfo| grep "cpu cores"| uniq  // 每个物理CPU的核数
# 总逻辑CPU数 = CPU总核数 * 超线程数 
# 一般超线程数为2，总逻辑CPU数可通过【lscpu】命令查看  


# 查看信号值含义
kill -l

# 回放包 
tcpreplay -i p4p2 -p 10000 /home/pingz/ipgroup/*.pcap
tcpreplay -i p4p2 -p 10000 -l 0 /home/pingz/ipgroup/*.pcap  # -l 0 不停回放包

# 允许生成core dump文件  
ulimit -c unlimited

# 设置网口mtu
ifconfig eth1 mtu 9000 up

# 自定义系统服务
cd /lib/systemd/system
vi xxx.service  # 按 service 脚本编写
```

## 抓包

01、抓取所有网络包，并在`terminal`中显示抓取的结果，将包以十六进制的形式显示。

```shell
tcpdump
```

02、抓取所有的网络包，并存到 `result.cap` 文件中。

```powershell
tcpdump -i any -w result.cap
```

03、抓取所有的经过`eth0`网卡的网络包，并存到`result.cap` 文件中。

```powershell
tcpdump -i eth0 -w result.cap
```

04、抓取源地址是`192.168.1.100`的包，并将结果保存到 `result.cap` 文件中。

```powershell
tcpdump src host 192.168.1.100 -w result.cap
```

05、抓取地址包含是`192.168.1.100`的包，并将结果保存到 `result.cap` 文件中。

```powershell
tcpdump host 192.168.1.100 -w result.cap
```

06、抓取目的地址包含是`192.168.1.100`的包，并将结果保存到 `result.cap` 文件中。

```powershell
tcpdump dest host 192.168.1.100 -w result.cap
```

07、抓取主机地址为 `192.168.1.100` 的数据包

```powershell
tcpdump -i eth0 -vnn host 192.168.1.100
```

08、抓取包含`192.168.1.0/24`网段的数据包

```powershell
tcpdump -i eth0 -vnn net 192.168.1.0/24
```

09、抓取网卡`eth0`上所有包含端口`22`的数据包

```powershell
tcpdump -i eth0 -vnn port 22
```

10、抓取指定协议格式的数据包，协议格式可以是「udp,icmp,arp,ip」中的任何一种,例如以下命令：

```powershell
tcpdump udp  -i eth0 -vnn
```

11、抓取经过 eth0 网卡的源 ip 是 192.168.1.100 数据包，`src`参数表示源

```powershell
tcpdump -i eth0 -vnn src host 192.168.1.100
```

12、抓取经过 eth0 网卡目的 ip 是 192.168.1.100 数据包，`dst`参数表示目的

```powershell
tcpdump -i eth0 -vnn dst host 192.168.1.100
```

13、抓取源端口是`22`的数据包

```powershell
tcpdump -i eth0 -vnn src port 22
```

14、抓取源`ip`是 `192.168.1.100` 且目的`ip`端口是`22`的数据包

```powershell
tcpdump -i eth0 -vnn src host 192.168.1.100 and dst port 22
```

15、抓取源`ip``192.168.1.100``22`

```powershell
tcpdump -i eth0 -vnn src host 192.168.1.100 or port 22
```

16、抓取源`ip``192.168.1.100``22`

```powershell
tcpdump -i eth0 -vnn src host 192.168.1.100 and not port 22
```

17、抓取源`ip`是`192.168.1.100`且目的端口是`22`，或源`ip`是`192.168.1.102`且目的端口是`80`的数据包。

```powershell
tcpdump -i eth0 -vnn ( src host 192.168.1.100 and dst port 22 ) or ( src host 192.168.1.102 and dst port 80 )
```

18、把抓取的数据包记录存到`/tmp/result`文件中，当抓取`100`个数据包后就退出程序。

```powershell
tcpdump –i eth0 -vnn -w /tmp/result -c 100
```

19、从`/tmp/result`记录中读取`tcp`协议的数据包

```powershell
tcpdump -i eth0  tcp  -vnn -r /tmp/result
```

20、想要截获所有`192.168.1.100`的主机收到的和发出的所有的数据包：

```powershell
tcpdump host 192.168.1.100
```

21、如果想要获取主机`192.168.1.100`除了和主机`192.168.1.101`之外所有主机通信的ip包，使用命令：

```powershell
tcpdump ip host 192.168.1.100 and ! 192.168.1.101
```

22、如果想要获取主机 `192.168.1.100` 接收或发出的 `telnet` 包，使用如下命令：

```powershell
tcpdump tcp port 23 host 192.168.1.100
```

23、同时抓取多个网口的包

```shell
tcpdump -i ens1f0 host 117.131.214.29 -w tt0.pcap & tcpdump -i ens1f1 host 117.131.214.29 -w tt1.pcap & tcpdump -i ens1f2 host 117.131.214.29 -w tt2.pcap & tcpdump -i ens1f3 host 117.131.214.29 -w tt3.pcap &
```



## 运维

```shell
# 查看程序运行日志
journalctl -a -f -u cpftp_upload_du
```