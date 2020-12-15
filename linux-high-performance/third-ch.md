TCP
    - 
        16-bit source port                  |           16-bit destination port
                                        32-bit sn
                                    32-bit ack-number
        4-bit header-length | 6-bit reserve | U.A.P.R.S.F | 16-bit window-size
                16-bit checksum             |       16-bit urg pointer

iptables -I INPUT -p tcp --syn -i eth0 -j DROP
半关闭状态：
    - TCP是全双工的。一端可以发送结束报文段给对方，但继续接受来自对方的数据，这种状态称为半关闭
    - 判断对方是否已经关闭连接的方法是：read()系统调用返回0
    - shutdown函数提供了对半关闭的支持

连接超时：
    - TCP三次握手丢包情况分析
    - 第一个包丢失，客户端依次以间隔时间1s、2s、4s、8s、16s重连
    - 第二个包丢失，服务端重发
    - 第三个包丢失，客户端已经进入established状态，服务端重发，客户端收到后，发送ACK

状态转移图：
    - CLOSED, SYN_SENT, SYN_RCVD, ESTABLISHED, FIN_WAIT1, FIN_WAIT2, TIME_WAIT, CLOSE_WAIT, LAST_ACK, CLOSING

connect：
    - 发送SYN，进入SYN_SENT
    - 如果目标端口不存在，或者该端口被处于TIME_WAIT状态的连接所占用，收到RST，connect调用失败
    - 如果目标端口存在，但connect在超时时间内未收到服务器的确认报文段，connect调用失败
    - connect调用失败后，连接立即返回到初始的CLOSED状态

FIN_WAIT2:
    - 客户端执行半关闭后，未等服务器关闭连接就强行退出了，客户端连接由内核接管，可称之为孤儿连接。
    - linux为了防止孤儿连接长时间留在内核中，定义两个变量：/proc/sys/net/ipv4/tcp_max_orphans(内核能接管的孤儿连接数目), /proc/sys/net/ipv4/tcp_fin_timeout（孤儿连接在内核中生存的时间）

TIME_WAIT:
    - 存在的原因有：
        - 可靠地终止TCP连接（ACK丢失，服务端重发，正常终止服务端）
        - 保证迟来的TCP报文段有足够的时间被识别并丢弃（该连接所有的报文都消失）
    - Linux系统上，一个连接不能被同时打开两次及以上
    - 当一个TCP连接处于TIME_WAIT状态时，无法立即使用该连接来建立一个新连接
    - 为了避免TIME_WAIT状态，通过socket选项SO_REUSERADDR来强制进程立即使用处于TIME_WAIT状态的连接占用的端口

复位报文段：
    - 访问不存在的端口
    - 异常终止连接：应用恒旭可以使用socket选项SO_LINGER来发送复位报文段，以异常终止一个连接
    - 处理板打开连接：
        - 一端关闭或者异常终止了连接，而对方没有接收到结束报文段（网络故障），此时对端还维护者原来的连接，这种状态为半打开状态
        - 如果往板打开状态的连接写入数据，将收到一个复位报文段

Nagle算法：
    - 解决由于很多小数据包导致的拥塞
    - 该算法要求一个TCP连接的通信双方在任意时刻都最多只能发送一个未被确认的TCP报文段，在该报文段的确认到达之前不能发送其他TCP报文段。
    - 发送方在等待确认的同时收集本端需要发送的微量数据，并在确认到来时以一个TCP报文段发出
    - 这样就极大地减少了网络上的微小TCP报文段的数量
    - 另一个优点是确认到达的越快，数据也就发送的越快

带外数据：
    - 带外数据用于迅速通告对方本端发生的重要事件，比普通数据有更高的优先级
    - 应该立即被发送，而不论发送缓冲区中是否有排队的普通数据
    - 带外数据可以使用一条独立的传输层连接，也可以映射到普通数据的连接中

超时重传：
    - 重传策略：超时时间、重传次数
    - 内核有两个重要的内核参数与超时重传有关：
        - /proc/sys/net/ipv4/tcp_retries1：最少重传次数
        - /proc/sys/net/ipv4/tcp_retries2：最多重传次数

快速重传：
    -        

拥塞控制：
    - 提高网络利用率、降低丢包率、保证网络资源对每条数据流的公平性
    - cubic / vegas / reno算法
    - 拥塞避免
    - 快速重传
    - 快速恢复
    - 拥塞控制的最终变量是发送端向网络依次连续写入的数据量-SWND
    - 发送端最终以tcp报文段来发送数据，所以SWND限定了发送端能连续发送的tcp报文段数量，报文段的最大长度称为SMSS，一般等于MSS
    - 接收方可以通过接收窗口RWND来控制发送端的SWND，但这显然不够，所以发送端引入了一个拥塞窗口CWND
    - SWND = min（RWND, CWND)

    - 慢启动：
        - CWND被初始化为IW≈2~4个SMSS，CWND += MIN(N, SMSS)，N是此次确认中包含的之前的未被确认的字节数
        - CWND按照指数形式扩大
        - TCP模块刚开始发送数据时并不知道网络的实际情况，用一种试探的方法增加CWND
    - 不施加其他手段，慢启动使得CWND膨胀的很快。拥塞控制定义了另一个变量：慢启动门限ssthresh
    - 当CWND大小超过ssthreash时，进入拥塞避免
    - 拥塞避免：
        - 使得CWND按照线性方式增加
        - CWND += SMSS* SMSS/CWND
    - 发送端如何判断拥塞发生：
        - 传输超时
        - 接收到重复的确认报文段

        



















