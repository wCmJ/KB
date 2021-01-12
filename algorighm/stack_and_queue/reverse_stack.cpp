/*
    目的：仅用递归函数和栈操作逆序一个栈

*/
#include <iostream>
#include <stack>

class ReverseStack{
public:
    ReverseStack(std::stack<int>& input){
        _nums.swap(input);
    }

    void Reverse(){
        if(_nums.empty())return;
        int last = getLastElement();
        Reverse();
        _nums.push(last);
    }

    void Print(){
        if(_nums.empty())return;
        int first = _nums.top();
        _nums.pop();
        std::cout<<first<<" ";
        Print();
        _nums.push(first);
    }


private:
    int getLastElement(){
        int val = _nums.top();
        _nums.pop();
        if(_nums.empty()){
            return val;
        }
        int res = getLastElement();
        _nums.push(val);
        return res;
    }
    std::stack<int> _nums;
};


int main(){
    std::stack<int> input;
    for(int i = 0;i<5;++i){
        input.push(i);
    }

    ReverseStack rs(input);
    std::cout<<"before: "<<std::endl;
    rs.Print();
    rs.Reverse();
    std::cout<<std::endl<<"after: "<<std::endl;
    rs.Print();
    return 0;
}


