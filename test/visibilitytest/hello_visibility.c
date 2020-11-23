#include "hello.h"

#define DLL_PUBLIC __attribute__((visibility ("default")))

int call_count = 0;

DLL_PUBLIC int hello_init(){
    call_count = 0;
    return 0;
}

int hello_call_count_add(){
    return ++call_count;
}

DLL_PUBLIC int hello_handle(){
    return hello_call_count_add();
}

DLL_PUBLIC void hello_exit(){
    call_count = 0;
}