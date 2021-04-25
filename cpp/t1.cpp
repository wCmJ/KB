#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


class Solution {
public:

    struct compare{
        bool operator()(vector<int>& l, vector<int>& r){
            return l[1]>r[1];
        }
    };

    struct compare_int{
        bool operator()(int l, int r){
            return l < r;
        }
    };

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        if(people.empty())return vector<vector<int>>();
        unordered_map<int, priority_queue<vector<int>, vector<vector<int>>, compare>> record;
        priority_queue<int,vector<int>, compare_int> lens;
        for(auto &vi: people){
            std::cout<<vi[0]<<", "<<vi[1]<<std::endl;
            if(record.count(vi[0]) == 0){
                lens.push(vi[0]);
            }
            record[vi[0]].push(vi);
        }

        vector<vector<int>> res;
        while(!lens.empty()){
            int len = lens.top();
            lens.pop();
            auto pq = record[len];
            while(!pq.empty()){
                auto node = pq.top();
                pq.pop();
                std::cout<<"insert: "<<node[0]<<", "<<node[1]<<std::endl;
                res.insert(res.begin() + node[1], node);
            }
        }
        return res;
    }
};


int main(){
    vector<vector<int>> datas{
        {7,0}, {4,4}, {7,1}, {5,0}, {6,1},{5,2}
        //7,0],[4,4],[7,1],[5,0],[6,1],[5,2
    };

    Solution so;
    auto res = so.reconstructQueue(datas);
    std::cout<<"-----------------------------"<<std::endl;
    for(auto &node: res){
        std::cout<<node[0]<< ", "<<node[1]<<std::endl;
    }

    return 0;
}




