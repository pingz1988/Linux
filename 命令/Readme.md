```shell
# Centos7 提升用户至root
sudo su  # 不加 sudo 会提示 “su故障”

# 递归拷贝目录
cp -r dir dst 

# 搜索历史命令  
Ctrl + R  
# 清屏  
Ctrl + L

# 查看环境变量  
env  
echo $(xxxVar)  

# 压缩目录
tar zcvf xxx.tar.gz xxx

# 解压 *.tar.xz 文件
tar xf *.tar.xz

# 批量重命名  
rename str1 str2 str1* : 把 str1 开头的文件名重命名为 str2 开头
rename .txt .log *.txt : 把以.txt 为后缀的文件名修改为 .log 后缀

# 查看文件
more/less fileName  
空格向下一屏，b 向上一屏  

# 查看隐藏文件
l. ： 只显示隐藏目录和隐藏文件  
ll -a : 显示所有文件，包括隐藏目录和隐藏文件

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

# 查看进程号  
pidof xxx  
ps -ef | grep xxxExe | grep -v grep | awk '{print $2}'

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

# 抓包  
tcpdump -i lo tcp and port 50000 -vv -w 50000.pcap

# 允许生成core dump文件  
ulimit -c unlimited

# 设置网口mtu
ifconfig eth1 mtu 9000 up
```
