进程池和线程池设计的原因是：
    - 耗时：进程、线程创建与销毁耗费时间，导致较慢的客户响应
    - 消耗CPU时间：动态创建的进程和线程通常只为一个客户服务，导致系统产生大量的细微进程，进程间切换将消耗大量CPU时间
    - 资源消耗：动态创建的子进程是当前进程的完整映像，当前进程必须谨慎管理其分配的文件描述符，否则子进程可能复制这些资源，使系统可用资源下降，影响服务器性能

由动态改为静态
    - 服务器预先创建好多个进程或线程
    - 当新任务到来时，通过以下两种方式来选择子进程
        - 随机/轮询/更智能算法均匀分配
        - 主进程和所有子进程共享一个工作队列，所有子进程都睡眠在这个任务队列上，主进程往工作队列中添加任务，唤醒等待的子进程，但只能有一个子进程获得接管权，从队列中取出任务并执行








NonCopyable: 
    - protected:
        - NonCopyable()
        - ~NonCopyable()
    - private:
        - NonCopyable(const NonCopyable&)
        - const NonCopyable& operator=(const NonCopyable&)

IThread: NonCopyable
    - public:
        - virtual ~IThread()
        - virtual void Run() = 0
        - void Start()
        - void Join()
    - private:
        