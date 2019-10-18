```shell
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

# 查看进程号  
pidof xxx  
ps -ef | grep xxxExe | grep -v grep | awk '{print $2}'

# 进程id作为其它命令的参数
pidstat -p `pidof xxxExe` -t  
pidstat -p `ps -ef | grep xxxExe | grep -v grep | awk '{print $2}'` -t  

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

# 查看信号值含义
kill -l

# 抓包  
tcpdump -i lo tcp and port 50000 -vv -w 50000.pcap

# 允许生成core dump文件  
ulimit -c unlimited
```
