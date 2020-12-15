IP detail
    - IP头部信息
        - 
            4-b version | 4-b header-length | 8-b tos | 16-b total-length
                    16-b identify | 3-b flag | 13-b offset
            8-b ttl     |     8-b protocol  |   16-b header checksum
                            32-b source ip
                            32-b destination ip




    - IP数据包的路由与转发
        - 收到IP数据时：
            1. 放入输入队列
            2. 解析头部CRC是否正确，如果错误，？？？。如果正确，分析头部具体信息。
            3. 如果头部设置了源站选路选项，则调用数据报转发模块来处理；
               如果头部中目标IP是本机的某个IP或者是广播地址，IP模块根据协议字段发送给具体的应用；
               如果不是发送给本机的，调用数据报转发模块来处理
            4. 数据包转发模块首先检测系统是否允许转发（/proc/sys/net/ipv4/ip_forward），如果不允许，数据报被丢弃；如果允许，则转交给路由模块处理。
                    




