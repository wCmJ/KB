* 概念
- 程序能够同时监听多个文件描述符
- 

* 使用场景
- 客户端
    - 同时处理多个socket
    - 同时处理用户输入和网络连接
- 服务器
    - 同时处理监听socket和连接socket
    - 同时处理TCP请求和UDP请求
    - 同时监听多个端口或多个服务

io多路复用本身是阻塞的，多个文件描述符同时就绪时，
    - 如果不采取额外措施，只能按序处理。
    - 如果要实现并发，可以采用多进程或多线程

* Linux实现方式（系统调用）
- select
    - 在一段指定时间内，监听用户感兴趣的文件描述符上的可读、可写及异常事件
    * 函数原型
        - int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout);
        - 返回时，内核修改readdfs，writefds，exceptfds来通知应用程序哪些文件描述符以及就绪
        - 大小
            - long int fds_bits[FD_SIZE/8*sizeof(long int)];
            - FD_SIZE个比特
        - API
            - FD_ZERO(fd_set*)
            - FD_SET(int fd, fd_set*)
            - FD_CLR(int fd, fd_set*)
            - int FD_ISSET(int fd, fd_set*)
        - 可读
            - 接收缓冲区字节数≥低水位标记
            - 对端关闭连接，读返回0
            - 有新的连接请求
            - 未处理的错误
        - 可写
            - 发送缓冲区字节数≥低水位标记
            - 写操作被关闭，对写操作关闭的socket执行写操作产生SIGPIPE信号
            - 使用非阻塞connect连接成功或失败之后
            - 未处理的错误
        - 异常
            - 收到带外数据

- poll
    - #include <poll.h>
    - int poll(struct pollfd* fds, nfds_t nfds, int time_out)


- epoll
    - #include <sys/epoll.h>
    - linux特有的IO复用函数，使用一组函数来完成任务。epoll把用户关心的任务描述符上的事件放在内核里的一个事件表中，无须像select和poll一样每次调用都要重复传入文件描述符或事件集
    - epoll需要使用一个额外的文件描述符，来唯一标识内核中的这个事件表：
        - int epoll_create(int size)
        - size参数并不起作用，只是给内核一个提示，告诉它size多大。
    - int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event)
        - op指定操作类型：
            - EPOLL_CTL_ADD，往事件表中注册fd上的事件
            - EPOLL_CTL_MOD，修改fd上的注册事件
            - EPOLL_CTL_DEL，删除fd上的注册事件
    - int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout)
        - 将就绪事件放入events中，epoll_event中携带fd信息

    - LT and ET
        - LT是默认的工作模式，epoll相当于一个效率较高的poll
        - ET是epoll的高效工作模式，降低了同一个epoll事件被重复触发的次数，因此效率比LT模式高。

- 比较
    - select的fd_set没有将文件描述符和事件绑定，仅仅是一个文件描述符的集合，因此提供三个这种类型的参数来区分不同事件
    - 另一方面内核对fd_set在线修改，在下次调用之前需重置这三个集合

    - poll把文件描述符和事件都定义在其中，事件被同一处理
    - 内核每次修改revents成员，events成员保持不变

    - 

