信号量、共享内存、消息队列是IPC最常见的方式。其中，消息队列在IPC中非常重要，是通信的基本手段之一。

* 消息队列、信号量、共享内存的相似之处：  
它们被统称为XSI IPC，它们在内核中有相似的IPC结构（消息队列的msgid_ds，信号量的semid_ds，共享内存的shmid_ds），而且都用一个非负整数的标识符加以引用（消息队列的msg_id，信号量的sem_id，共享内存的shm_id，分别通过msgget、semget以及shmget获得），标志符是IPC对象的内部名，每个IPC对象都有一个键（key_t key）相关联，将这个键作为该对象的外部名。

* XSI IPC和管道（PIPE）、具名管道（FIFO）的区别：  
1. XSI IPC的IPC结构是在系统范围内起作用，没用使用引用计数。如果一个进程创建一个消息队列，并在消息队列中放入几个消息，进程终止后，即使现在已经没有程序使用该消息队列，消息队列及其内容依然保留。而PIPE在最后一个引用管道的进程终止时，管道就被完全删除了。对于FIFO最后一个引用FIFO的进程终止时，虽然FIFO还在系统，但是其中的内容会被删除。  
2. 和PIPE、FIFO不一样，XSI IPC不使用文件描述符，所以不能用ls查看IPC对象，不能用rm命令删除，不能用chmod命令删除它们的访问权限。只能使用ipcs和ipcrm来查看可以删除它们。

* 内存映射 VS 共享内存  
1. mmap是在磁盘上建立一个文件，每个进程地址空间中开辟出一块空间进行映射。而shm共享内存，每个进程最终会映射到同一块物理内存。shm保存在物理内存，这样读写的速度肯定要比磁盘要快，但是存储量不是特别大。  
2. 相对于shm来说，mmap更加简单，调用更加方便，所以这也是大家都喜欢用的原因。
3. 另外mmap有一个好处是当机器重启，因为mmap把文件保存在磁盘上，这个文件还保存了操作系统同步的映像，所以mmap不会丢失，但是shmget在内存里面就会丢失。
4. 总之，共享内存是在内存中创建空间，每个进程映射到此处。内存映射是创建一个文件，并且映射到每个进程开辟的空间中。
