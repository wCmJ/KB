自linux2.6以后，才支持内核线程。

创建线程和结束线程
    - 创建
        - #include <pthread.h>
        - int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void*(*start_routine)(void*), void* arg)
        - 后续pthread_*函数通过thread参数来引用新线程
        - 创建成功时返回0，失败时返回错误码。一个用户可以打开的线程数量不能超过RLIMIT_NPROC软资源限制，此外，系统上所有用户能创建的线程总数也不能超过/proc/sys/kernel/threads-max内核参数所定义的值
    - 结束
        - #include <pthread.h>
        - void pthread_exit(void* retval)
        - 线程一旦被创建好，内核可以调度内核线程来执行start_routine函数指针指向的函数，线程在结束时，调用上述函数可以安全、干净地退出
        - pthread_exit函数通过retval参数向现场的回收者传递其退出信息，执行完之后不会返回到调用者，而且永远不会失败

    - 回收
        - #include <pthread.h>
        - int pthread_join(pthread_t thread, void** retval)
        - 一个进程中的所有线程都可以调用pthread_join函数来回收其他线程，即等待其他线程结束，这类似于回收进程的wait和waitpid系统调用
        - 该函数会一直阻塞，直到被回收的线程结束为止，成功时返回0，失败时返回错误码
        - 错误码
            - EDEADLK：两个线程针对对方调用pthread_join，或者线程对自身调用pthread_join，导致死锁
            - EINVAL：目标线程是不可回收的，或者已经有其他线程在回收该目标线程
            - ESRCH：目标线程不存在

    - 取消
        - #include <pthread.h>
        - int pthread_cancel(pthread_t thread)
        - 接收到取消请求的目标线程可以决定是否允许被取消以及如何取消，由以下两个函数完成：
            - int pthread_setcancelstate(int state, int *oldstate)
            - int pthread_setcanceltype(int type, int *oldtype)

读取和设置线程属性

线程同步方式：POSIX信号量、互斥锁和条件变量

    - 信号量
        - sem_init：初始化
        - sem_destroy：销毁信号量
        - sem_wait：以原子操作的方式将信号量的值减1，如果信号量的值为0，则sem_wait将被阻塞，直到这个信号量具有非0值
        - sem_post：以原子操作的方式将信号量的值加1，当信号量的值大于0时，其他调用sem_wait等待信号量的线程将被唤醒

    - 互斥锁
        - int pthread_mutex_init(pthread_mutex_t* mutext, const pthread_mutexattr_t* mutexattr)
        - int pthread_mutex_destroy(pthread_mutex_t* mutext)
        - int pthread_mutex_lock(pthread_mutex_t* mutex)
        - int pthread_mutex_trylock(pthread_mutex_t* mutex)
        - int pthread_mutex_unlock(pthread_mutex_t* mutex)

        - 使用互斥锁的一个噩耗是死锁，死锁使得线程被挂起而无法继续执行，并且这种情况不容易被发现。
        - 在一个线程中对一个已经枷锁的普通锁再次枷锁，将导致死锁

    - 条件变量
        - 互斥锁用于同步线程对共享数据的访问，条件变量用于在线程之间同步共享数据的值，条件变量提供了一种线程间的通知机制
        - int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* cond_attr)
        - int pthread_cond_destroy(pthread_cond_t* cond)
        - int pthread_cond_broadcast(pthread_cond_t* cond)：以广播方式唤醒所有等待目标条件变量的线程
        - int pthread_cond_signal(pthread_cond_t* cond)：唤醒一个等待目标条件变量的线程，哪个线程被唤醒取决于线程的优先级和调度策略
        - int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex)







线程模型
    - 内核线程
        - LWP（轻量级进程）
        - 运行在内核空间，由内核调度

    - 用户线程
        - 运行在用户空间，由线程库调度

    - 当一个内核线程获得CPU的使用权时，它就加载并运行一个用户线程
      内核线程相当于用户线程运行的容器
      一个进程可以拥有M个内核线程和N个用户线程，M≤N
      在一个系统的所有进程中，M和N的比值是固定的。
      按照M:N的值可以分为：
        - 完全在用户空间实现
            - 完全由线程库管理
            - 线程库利用longjmp来切换线程执行

            - 优点：
                - 创建和调度无须内核干预，速度快
                - 不占用额外内核资源，不会对系统性能造成明显影响
            - 缺点：
                - 对于多处理器系统，一个进程的多个线程无法运行在不同CPU上
                - 线程优先级只对同一个进程中的线程有效
        - 完全由内核调度
            - 与完全用户调度优缺点互换
            - M:N=1:1
        - 双层调度
            - 内核调度M个内核线程，线程库调度N个用户线程

    - 早起实现是用进程模拟线程：clone创建子进程，指定CLONE_THREAD标志，使得子进程与调研进程共享相同的虚拟地址空间、文件描述符和信号处理函数
        - 缺点
            - 每个线程有不同PID，不符合POSIX规范
            - LInux信号处理本来是基于进程的，但现在一个进程内部的所有线程都能而且必须处理信号
            - 用户ID、组ID对一个进程汇总的不同线程来说可能是不一样的
            - 程序产生的coredump不会包含所有线程的信息
            - 系统允许的最大进程数就是最大线程数






