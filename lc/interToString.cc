#include <iostream>

const char digits[] = "9876543210123456789";
const char* zero = digits + 9;


template<typename T>
std::size_t convert(char buf[], T value){
    T i = value;
    char* p = buf;
    do{
        int lsd = static_cast<int>(i % 10);
        i /= 10;
        *p++ = zero[lsd];
    }while(i != 0);
    if(value < 0){
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);
    return p - buf;
}


int main(){
    char buf[100];
    std::cout<<convert(buf, 1234)<<std::endl;
    for(int i = 0;i<10;++i){
        std::cout<<buf[i];
    }
    std::cout<<std::endl;
    std::cout<<convert(buf, 0)<<std::endl;
    for(int i = 0;i<10;++i){
        std::cout<<buf[i];
    }
    std::cout<<std::endl;

    std::cout<<convert(buf, -1234)<<std::endl;
    for(int i = 0;i<10;++i){
        std::cout<<buf[i];
    }
    std::cout<<std::endl;
    return 0;
}


