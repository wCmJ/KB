#include "hello.h"

int call_count = 0;

int hello_init(){
    call_count = 0;
    return 0;
}

int hello_call_count_add(){
    return ++call_count;
}

int hello_handle(){
    return hello_call_count_add();
}

void hello_exit(){
    call_count = 0;
}

gcc在链接时设置-fvisibility=hidden，
则不加 visibility声明的都默认为hidden，即都是隐藏的， gcc默认设置-fvisibility=default，即全部可见。