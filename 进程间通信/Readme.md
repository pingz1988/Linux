* fork 子进程
```c

pid_t pid = fork();
if (pid < 0)
{
	printf("fork err\n");
	return -1;
}
	
if (0 == pid) // 子进程
{
	setsid();	// 很重要！父子进程分离
	while(1)
	{
		printf("fa switch: %d\n", g_fa_flag);
		if (0 == is_process_running(fa_name))
			start_process_with_py(fa_name);
		
		if (1 == g_eu_flag)
		{
			g_eu_flag = 0;
			
			pthread_t thd;
			if (pthread_create(&thd, NULL, start_process, (void*)eu_name))
			{
				printf("start packet report failed. %s\n", strerror(errno));
			}
			pthread_detach(thd);
		}
		
		if (1 == g_fa_flag)
		{
			g_fa_flag = 0;
			
			start_process_with_py(fa_name);
		}
		
		if (1 == g_xdr_flag)
		{
			g_xdr_flag = 0;
			
			pthread_t thd;
			if (pthread_create(&thd, NULL, start_process, (void*)xdr_name))
			{
				printf("start data report failed. %s\n", strerror(errno));
			}
			pthread_detach(thd);
		}
		
		if (1 == g_upload_flag)
		{
			
		}
		
		sleep(1);
	}
}
else  // 父进程
{
	S32 ret = init_vty_command();
	if (0 == ret)
	{
		printf("init vty finished\n");
	}
	else
	{
		printf("init vty failed\n");
	}
		
	while(1)
	{
		sleep(1);
	}
}
```

*  用SIGCHLD信号，防止僵尸进程  
当子进程退出时，父进程没有调用wait()或waitpid()函数等待子进程结束，又没有显示忽略SIGCHLD信号，那么它将一直处于僵尸状态，如果这时父进程结束了，init进程会自动接收这个子进程，为它收尸，但是，如果父进程是个循环，不会退出，那子进程将一直保持僵尸状态。

```c
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

void signal_handler(int signo)
{
    if (signo == SIGCHLD)
    {
        pid_t pid;
        while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
	{
            printf("SIGCHLD pid %d\n", pid);
        }
    }
}

void mysleep(int sec)
{
    time_t start = time(NULL), elapsed = 0;
    while (elapsed < sec)
    {
        sleep(sec - elapsed);
        elapsed = time(NULL) - start;
    }
}

int main(int argc, char **argv)
{

    signal(SIGCHLD, signal_handler);

    while (1) {
        pid_t pid = fork();
        if (pid > 0)
	{
            // parent process
            mysleep(5);
        } else if (pid == 0)
	{
            // child process
            printf("child pid %d\n", getpid());
            return 0;
        } else
	{
            fprintf(stderr, "fork error\n");
            return 2;
        }
    }
}
```
