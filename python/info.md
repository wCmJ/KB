# 创建虚拟环境：
    - python3 -m venv env

# 激活虚拟环境
    - . env/bin/activate


# 面向对象
    - 双下划线开头的变量和函数，需要增加前缀_className才能访问
    - 实际开发中，不建议将属性设置为私有的，这会导致子类无法访问
    - 可以采用单下划线开头，表示属性是受保护的


    - @property：用来为单下划线开头的变量提供getter和setter方法，使得对象可以通过不加下划线的方式访问
    - __slots__：动态语言允许在运行时给对象绑定或解绑新的属性和方法，通过__slots__限定对象只能绑定某些属性，只对当前类的对象生效，对子类不起作用
        - __slots__ = ('n1','n2')

    - 静态方法： @staticmethod
    - 类方法：@classmethod，第一个参数为cls，代表当前类相关的信息的对象（类本身也是一个对象，有时也称为类的元数据对象）

    - 类之间的关系：
        - is-a
        - has-a
        - use-a

# 文件和异常
    - 通过内置函数open，可以指定文件名、操作模式、编码信息来获得操作文件的对象，
        操作模式	 具体含义
        'r'	        读取 （默认）
        'w'	        写入（会先截断之前的内容）
        'x'	        写入，如果文件已经存在会产生异常
        'a'	        追加，将内容写入到已有文件的末尾
        'b'	        二进制模式
        't'	        文本模式（默认）
        '+'	        更新（既可以读又可以写）
    - open('致橡树.txt', 'r', encoding='utf-8')
        - 指定模式为读，如果不指定，默认也是读取
        - 指定编码，如果不指定，默认为None，那么在读取时使用的是操作系统默认的编码

    - f.read()返回一个str
    - f.readlines()返回一个list
    - 模式为'w'或者'a'时，如果文件不存在，会自动创建

    - json
        - 有四个重要的函数：
            - dump：将python对象按照json格式序列化到文件中
            - dumps：将python对象处理成json格式的字符串
            - load：将文件中的json数据反序列成对象
            - loads：将字符串的内容反序列化成python对象

# 正则表达式
    - r''，r表示原始字符串，字符串中的每个字符都是它本来的意义


# 装饰器
    - 定义函数，把函数赋值给一个变量
    - 函数中定义函数
    - 函数返回另一个函数
    - 函数作为参数传递给另一个函数

    @a
    @b
    @c
    def f():
    等价于 f = a(b(c(f)))


# 协程
    - 单线程 + 异步IO称为协程
    - 有了协程的支持，可以基于事件驱动编写高效的多任务程序
    - 优势一：协程效率高，因为子程序切换不是线程切换，由程序自身控制，没有线程切换的开销
    - 优势二：不需要锁机制，只有一个线程，不存在读写变量冲突，控制变量资源不用加锁，判断状态就可以了


```
def scope_test():
    def do_local():
        spam = "local spam"

    def do_nonlocal():
        nonlocal spam
        spam = "non local spam"

    def do_global():
        global spam
        spam = "global spam"

    spam = "test spam"
    do_local()
    print("After local assignment: ", spam)
    do_nonlocal()
    print("After nonlocal assignment: ", spam)
    do_global()
    print("After global assignment: ", spam)


scope_test()
print("In global scope:", spam)

nonlocal 会引用此作用域外层的变量，需要实现定义好
global 会引用全局变量，事先可以不存在


------------------------------------------------------------------------------------------------------------------------------
@dataclass
class Error:
    tricks = []
    level = 1
    line = 2

