#include <iostream>
#include <stdio.h>

void func(){
    int *p;
    p = (int*)__builtin_frame_address(0);
    printf("func frame: %p\n", p);
    p = (int*)__builtin_frame_address(1);
    printf("main frame: %p\n", p);
}



const static int NUM = 18;

int main(){

    int *p;
    p = (int*)__builtin_frame_address(0);
    printf("main func frame: %p\n", p);
 
    func();

    unsigned long pc[NUM]{};
    for(int i = 0;i<NUM;++i){
	std::cout<<pc[i]<<" ";
    }
    std::cout<<std::endl;


    return 1;
}


