#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;


/*
    给定一个非负整数数组，最初位于数组的第一个位置

    数组中的每个元素代表你在该位置可以跳跃的最大长度

    你的目标是使用最少的跳跃次数到达数组的最后一个位置

*/

int jump(vector<int> &nums){
    if(nums.size() < 2)return 0;
    int max_idx = nums[0];
    int i = 0, res = 0;
    while(i <= max_idx){
        ++res;
        if(max_idx >= nums.size() - 1)break;
        int tmp = max_idx;
        while(i <= tmp){
            max_idx = std::max(max_idx, i + nums[i]);
            ++i;
        }
    }
    return max_idx >= nums.size() - 1 ? res : 0;
}

string base(const string& s){
        int cnts[26] = {0};
        for(auto &c: s){
            cnts[(int)(c - 'a')]++;
            //std::cout<<"c: "<<c<<". cnts[(int)(c - 'a')]"<<cnts[(int)(c - 'a')]<<std::endl;
        }
        string res;
        for(int i = 0;i<26;++i){
            if(cnts[i] > 0){
                res += string(cnts[i], (char)('a' + i));
            }
        }
        std::cout<<"base return: "<<res<<". from:"<<s<<std::endl;
        return res;
    }


    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> matchs;
        for(auto &s: strs){
            auto tmp = base(s);
            std::cout<<"tmp: "<<tmp<<". s:"<<s<<std::endl;
            matchs[tmp].push_back(s);
        }
        vector<vector<string>> res;
        for(auto &node: matchs){
            res.push_back(node.second);
        }
        return res;
    }



int main(){
    {
        vector<string> words{"cat","rye","aye","cud","cat","old","fop","bra"};
        auto res = groupAnagrams(words);

    }



    vector<int> nums{2,3,1,1,1,4};
    std::cout<<jump(nums)<<std::endl;

    return 0;
}
