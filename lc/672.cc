#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    static int cnt;
    int flipLights(int n, int m) {
        //first: open
        //int op[4];
        //将m分配到4组操作中，
        int op[4] = {0};
        string base(n + 1, '1');
        std::cout<<"base is: "<<base<<std::endl;
        unordered_set<string> record;
        unordered_map<string, unordered_set<int>> finished;//memorize
        flipLights(base, m, record, finished);
        /*for(auto it = record.begin(); it != record.end();++it){
            std::cout<<*it<<std::endl;
        }*/
        return record.size();
    }
    
    void flipLights(string base, int m, unordered_set<string> &record, unordered_map<string, unordered_set<int>>& finished){
        ++cnt;
        if(m == 0){
            record.insert(base);
            return;
        }
        if(finished.count(base) && finished[base].count(m)){//memorize
            return;//memorize
        }

        //op1
        string op1 = base;
        for(int i = 1;i<op1.size();++i){
            if(op1[i] == '0')op1[i] = '1';
            else if(op1[i] == '1')op1[i] = '0';
        }
        flipLights(op1, m - 1, record, finished);
        //op2
        op1 = base;
        for(int i = 1;i<op1.size();i+=2){
            if(op1[i] == '0')op1[i] = '1';
            else if(op1[i] == '1')op1[i] = '0';
        }
        flipLights(op1, m - 1, record, finished);
        //op3
        op1 = base;
        for(int i = 2;i<op1.size();i+=2){
            if(op1[i] == '0')op1[i] = '1';
            else if(op1[i] == '1')op1[i] = '0';
        }
        flipLights(op1, m - 1, record, finished);
        //op4
        op1 = base;
        for(int i = 1;i<op1.size();i+=3){
            if(op1[i] == '0')op1[i] = '1';
            else if(op1[i] == '1')op1[i] = '0';            
        }
        flipLights(op1, m - 1, record, finished);
        finished[base].insert(m);
    }
};
int Solution::cnt = 0;

int main(){
    Solution so;
    std::cout<<"so.flipLights(2,2): "<<so.flipLights(2,2)<<std::endl;
    std::cout<<so.cnt<<std::endl;
    std::cout<<"so.flipLights(4,100): "<<so.flipLights(4,100)<<std::endl;
    std::cout<<so.cnt<<std::endl;
    return 0;
}

