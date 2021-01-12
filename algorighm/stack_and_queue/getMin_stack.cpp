/*
    目的：设计一个特殊的栈，实现栈的基本功能的基础上，再实现返回栈中最小元素的操作
    要求：pop、push、getMin的时间复杂度都是O(1);可以使用现有的栈结构
*/

#include <stack>

class NewStack{
public:
    int pop(){
        if(_num.empty()){
            throw "no num";
            return 0;
        }

        //method1
        {
            int res = _num.top();
            _num.pop();
            _min.pop();
            return res;
        }

        //method2
        {
            int res = _num.top();
            _num.pop();
            if(res == _min.top()){
                _min.pop();
            }
            return res;
        }
    }

    void push(int v){
        _num.push(v);
        //method1
        {
            if(_min.empty() || v <= _min.top()){
                _min.push(v);
            }
            else{
                _min.push(_min.top());
            }
        }
        //method2
        {
            if(_min.empty() || v <= _min.top()){
                _min.push(v);
            }
        }
    }

    int getMin(){
        if(_min.empty()){
            throw "getMin error! stack is empty";
            return 0;
        }
        return _min.top();
    }
private:
    std::stack<int> _num;
    std::stack<int> _min;
};








