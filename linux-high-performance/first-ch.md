1. TCP/IP协议体系及主要协议
    - ping -> icmp, telnet -> tcp, ospf -> ip, dns -> udp
    - icmp -> ip, tcp -> ip, udp -> ip
    - ip -> data link, arp -> data link, rarp -> data link

    - 数据链路层实现了网卡接口的网络驱动程序，为上层提供一个统一的接口。
        - 常用协议有 ARP， RARP
        - 以太网、令牌环网、802.11无线网络都使用 MAC 地址
        - 以太网帧格式：
            - 6-byte 目的mac地址 | 6-byte 源mac地址 | 2-byte 协议 | 46~1500-byte 数据 | 4-byte CRC
            - 帧头和帧尾总共 18-byte

    - 网络层
        - ICMP：主要用于检测网络连接
            - 8-bit type | 8-bit code | 16-bit checksum
            - 前8bit用来区分报文类型：
                - 差错报文：回应网络错误（目标不可达、重定向）
                - 查询报文：ping（查看目标是否可达）
            - 8-bit code：进一步细分
            - 16-bit CRC：检验传输过程中是否有损坏


    - ARP：
        - 2-byte 硬件类型 | 2-byte 协议类型 | 2-byte 硬件地址长度 | 2-byte 协议地址长度 | 2-byte 操作 | 6-byte 发送端以太网地址 | 4-byte 发送端ip地址 | 6-byte 目的端以太网地址 | 4-byte 目的端IP地址

        - 2-byte 操作字段表明是ARP请求、ARP应答、RARP请求、RARP应答
        - arp请求和应答包是以太网驱动程序发出的
        - ARP请求中，除目的端以太网地址字段填写全1，其他字段均正常填写
        - ARP应答中，所有字段均需填写
        - arp -a： 查看arp缓存
        - arp -d ip地址：删除指定arp缓存项
        - arp -s ip地址 mac地址：添加arp缓存项

    - DNS：
        - 分布式域名服务系统。每个DNS服务器上存储着大量的机器名和IP地址的映射，并且是动态更新的
        - 


