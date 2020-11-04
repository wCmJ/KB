#include<iostream>
#include<cstdlib>


int main(int argc, char* argv[]){
    std::cout<<"argc is: " << argc << std::endl;
    std::cout<<argv[0]<<std::endl;
    if(argc > 1){
        const double inputValue = std::stod(argv[1]);
        std::cout<<"hello world: "<< inputValue << std::endl;
    }
    return 0;
}

