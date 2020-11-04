#ifndef IMPL_H_
#define IMPL_H_

#include<iostream>


class Singleton{
public:
    static Singleton& Instance(){
        static Singleton m_instance;
        return m_instance;
    }

    void Print(){
        std::cout<<"Singleton"<<std::endl;
    }

    void Set(int val){
        std::cout<<"Set v_: "<< v_ << " to:"<<val<<std::endl;
        v_ = val;
    }

    int Get(){
        std::cout<<"Get v_: "<< v_ <<std::endl;
        return v_;
    }


private:
    Singleton():v_(100){}
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    int v_;
};


#endif //#ifndef IMPL_H_