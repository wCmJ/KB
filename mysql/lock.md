锁设计的初衷是处理并发问题。

根据加锁的范围：锁可以分为全局锁、表级锁和行锁。

全局锁：
    Flush tables with read lock(FTWRL)

官方自带逻辑备份工具是mysqldump。

对于引擎不支持RR时，需要使用FTWRL。








