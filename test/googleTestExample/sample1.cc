#include <iostream>


namespace{

int val = 0;

int Factorial(int n){
    if(n <= 1)return 1;
    int res = 1;
    for(int i = 2;i<=n;++i){
        res *= i;
    }
    return res;
}

bool IsPrime(int n){
    if(n < 2 || n % 2 == 0)return false;
    for(int i = 3;i<n/2;i+=2){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
}

int main(){
    std::cout<<Factorial(1)<<std::endl;

    std::cout<<Factorial(3)<<std::endl;
    std::cout<<Factorial(5)<<std::endl;
    std::cout<<Factorial(7)<<std::endl;

    std::cout<<++val<<std::endl;
    std::cout<<++val<<std::endl;
    std::cout<<++val<<std::endl;

    return 0;
}


