#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

#include <thread>

typedef void*(*)(int) FUNC_1;

void* impl(int input){
    std::cout<<input<<std::endl;
    return NULL;
}

std::once_flag g_flag;
static void do_once(){
    std::cout<<"do_once"<<std::endl;
}


int main(){

    FUNC_1 funcs[20];
    

    for(int i = 0;i<20;++i){
        std::call_once(g_flag, do_once);
    }
    std::cout<<"end for loop"<<std::endl;


    int fileId = open("./test.log", O_RDWR | O_CREAT, S_IRWXU);
    uint m_file_size = 0;
    struct stat st = {0};
    int ret = fstat(fileId, &st);
    if(ret != -1){
        m_file_size = static_cast<size_t> (st.st_size);
    }
    std::cout<<"old file size is:"<<m_file_size<<std::endl;
    if(ftruncate(fileId, m_file_size + 10) != 0){
        std::cout<<"new file size is: "<<st.st_size<<std::endl;
    }

    return 0;
}


