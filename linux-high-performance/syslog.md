* 系统日志

                    终端输出内核信息
                          ↑
                        dmesg
                          ↑
内核  -> printk -> ring buffer -> /proc/kmsg
                                    ↓
用户进程 -> syslog -> /dev/log -> syslogd -> /var/log/*


* 用户信息

int setuid(uid_t);
int seteuid(uid_t);
int setgid(gid_t);
int setegid(gid_t);

UID
    - 当前进程的真实用户ID
EUID
    - 有效用户ID
    - 运行程序的用户拥有该程序的有效用户的权限：例如su的所有者是root，它被设置了set-user-id标志，该标志表示，任何普通用户运行su程序时，其有效用户就是该程序的所有者root。
GID
    - 真实组ID
EGID
    - 有效组ID

* 切换用户

'''
    static bool switch_to_user(uid_t user_id, gid_t gp_id){
        
        /* 确保目标用户不是root */
        if((user_id == 0) && (gp_id == 0)){
            return false;
        }

        /* 确保当前用户是合法用户：root或者目标用户 */
        git_t gid = getgid();
        uid_t uid = getuid();
        if(((gid != 0) || (uid != 0)) && ((gid != gp_id) || (uid != user_id))){
            return false;
        }

        if(uid != 0){
            return true;
        }

        if((setgid(gp_id) < 0) || (setuid(user_id) < 0)){
            return false;
        }

        return true;
    }
'''

一个进程只能设置自己或其子进程的PGID，子进程执行exec后，父进程不能再对其设置PGID。

coredump is a file containing process memory contents when the process terminated unexpectedly.

program crash -> kernel trigger -> coredump file

临时开启：ulimit -S -c unlimited
    -S: soft
    -c: size

永久开启：echo "* soft core unlimited" >> /etc/security/limit.conf

coredump file location stored in: /proc/sys/kernel/core_pattern
    /data/coredump/core-%t-%u-%g-%s-%p-%e


* 池
预先申请系统资源，后续使用时，由池来分配和回收，回收是池的管理动作，并没有归还给系统。

预期分配多少资源？
    - 静态分配：分配足够多的资源
    - 动态分配：先申请一部分，发现资源不够用时，再动态分配放入池中
    - 内存池、进程池、线程池、连接池

内存池：
    - 通常用于socket的接收缓存和发送缓存

进程池、线程池：
    - 预先创建好进程和线程
    - 考虑到进程切换和线程切换带来的开销，进程线程数目

连接池：
    - 预先建立内部永久连接，比如数据库连接

* 避免不必要的数据复制，尤其发生在用户代码和内核之间的时候
当应用程序不关心数据内容的时候，内核可以直接处理。
零拷贝：sendfile可以实现该功能。无须将数据拷贝至应用程序空间，然后调用send来发送。

用户代码内部数据复制也应该避免。例如多个进程间传递数据，应该考虑使用共享内存来在它们之间直接共享数据，而不是用管道或者消息队列来传递。








