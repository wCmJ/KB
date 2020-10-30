#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int res = INT_MAX;
        dfs(heights, 0, 0, 0, res);
        return res;
    }

    void dfs(vector<vector<int>>& heights, int row, int col, int sum, int &res){
        std::cout<< row << ": "<< col << std::endl;
        if(row == heights.size() - 1 && col == heights[0].size() - 1){
            if(sum < res){
                res = sum;
                std::cout<< "sum : " << sum << ". res : " << res << std::endl;
            }
            std::cout<<std::endl;
            return;
        }
        int v = heights[row][col];
        heights[row][col] = -1;

        int dir[5] = {0,1,0,-1,0};
        for(int i = 0;i<4;++i){
            int ri = row + dir[i], ci = col + dir[i + 1];
            if(ri < 0 || ri >= heights.size() || ci < 0 || ci >= heights[0].size() || heights[ri][ci] == -1){
                continue;
            }
            int val = (heights[ri][ci] > v) 
                    ? (heights[ri][ci] - v) 
                    : (v - heights[ri][ci]);
            //if(val > res)continue;
            dfs(heights, ri, ci, std::max(val, sum), res); 
        }
        heights[row][col] = v;
    }

};


int main(){
    vector<vector<int> > data {{1,2,2},{3,8,2},{5,3,5}};
    Solution s1;
    s1.minimumEffortPath(data);

    return 0;
}



