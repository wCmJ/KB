#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using std::unordered_set;
using std::vector;

int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for(const int& n: nums){
            num_set.insert(n);
        }

        int longestStreak = 0;
        for(const int& num: num_set){
            if(!num_set.count(num - 1)){
                int currentNum = num;
                int currentStreak = 1;
                while(num_set.count(currentNum + 1)){
                    currentNum += 1;
                    currentStreak += 1;
                }
                longestStreak = std::max(longestStreak, currentStreak);
                std::cout<<longestStreak<<"   "<<currentStreak<<std::endl;
            }
        }
        return longestStreak;
    }

int main(){
    vector<int> nums{100,4,200,1,3,2};
    std::cout<<longestConsecutive(nums)<<std::endl;

    return 0;
}

