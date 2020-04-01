* 设置线程名称的两种方法  
```c
prctl(PR_SET_NAME,(unsigned long)(thread_name));  // 只能设置/获取当前线程的名字
int pthread_setname_np(pthread_t thread, const char *name);  // 也可在进程中设置其他线程的名字
```

* 线程同步小结  
  - 1.当线程间有逻辑先后顺序时，可以考虑使用信号量
  - 2.当线程需要等待某种条件才执行，可以考虑使用条件变量，而不是使用锁来不断循环检测条件有没有满足

* 线程同步几种方式  
互斥锁、读写锁、条件变量、信号量  
