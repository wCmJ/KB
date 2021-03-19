数据类型： string， list， hash， set， zset

python-redis:
    安装： pip3 install redis
    redis提供两个类：Redis和StrictRedis，StrictRedis用于实现大部分官方的命令，Redis是StrictRedis的子类，用于向后兼用旧版本

    redis取出的结果默认是字节，设定decode_responses=True改成字符串

    每个Redis实例会维护一个自己的连接池，可以直接建立一个连接池，实现多个Redis实例共享一个连接池

    基本命令String
    r.set(key, value, ex=3, px = 10, nx=True, xx=False)
    ex表示过期时间，单位为秒
    px表示过期时间，单位为毫秒
    nx表示只有当key不存在时，才执行当前set操作
    xx表示只有当key存在时，才执行当前set操作

    

