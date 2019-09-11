* 设置线程名称的两种方法  
```c
prctl(PR_SET_NAME,(unsigned long)(thread_name));
int pthread_setname_np(pthread_t thread, const char *name);
```

* 小结  
  - 1.当线程间有逻辑先后顺序时，可以考虑使用信号量
  - 2.当线程需要等待某种条件才执行，可以考虑使用条件变量，而不是使用锁来不断循环检测条件有没有满足
