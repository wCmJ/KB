/*
    目的：将一个栈排序，只能借助另外一个栈的帮助

*/

#include <stack>
#include <time.h>
#include <iostream>

class SortedStack{
public:
    SortedStack(std::stack<int>& input){
        _nums.swap(input);
    }
    void Sort(){
        std::stack<int> tmp;
        while(!_nums.empty()){
            int val = _nums.top();
            _nums.pop();
            int cnt = 0;
            while(!tmp.empty() && tmp.top() > val){
                _nums.push(tmp.top());
                tmp.pop();
                ++cnt;
            }
            tmp.push(val);
            while(cnt){
                tmp.push(_nums.top());
                _nums.pop();
                --cnt;
            }
        }
        _nums.swap(tmp);
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
    std::stack<int> _nums;

};


int main(){
    std::stack<int> input;
    srand((unsigned int)time(NULL));
    for(int i = 1;i<10;++i){
        int v = rand() % 100;
        std::cout<<v<<" ";
        input.push(v);
    }
    std::cout<<std::endl;
    SortedStack ss(input);
    ss.Sort();
    ss.Print();
    return 0;
}

