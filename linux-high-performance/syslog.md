* 系统日志

                    终端输出内核信息
                          ↑
                        dmesg
                          ↑
内核  -> printk -> ring buffer -> /proc/kmsg
                                    ↓
用户进程 -> syslog -> /dev/log -> syslogd -> /var/log/*


* 用户信息

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

