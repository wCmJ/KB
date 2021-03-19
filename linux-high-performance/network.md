* accept对于客户端网络断开毫不知情，accept只是从监听队列中取出连接，而不论连接处于何种状态（established或者close_wait状态），更不关心任何网络状况的变化

* listen调用被动接受连接，

* connect主动与对端建立连接

* close并非总是关闭一个连接，而是将fd的引用计数减1，只有当fd的引用计数为0时，才真正关闭连接。多进程程序中，一次fork系统调用默认将使父进程中打开的socket引用计数加1，因此我们必须在父进程和子进程中都对该socket执行close调用才能将连接关闭。如果无论如何都要立即终止连接（而不是将引用计数减1），可以使用shutdown系统调用。shutdown能够分别关闭socket上的读或写，而close只能同时关闭。

* recv返回0时，意味着对方已经关闭连接了。成功时返回实际读取到的数据的长度。

* send成功时返回实际写入的数据的长度。

* recvfrom读取sockfd上缓冲区的数据，

* sendto向写缓冲区写入数据

* getsockname获取sockfd对一个的本端socket地址

* getpeername获取sockfd对应的远端socket地址



