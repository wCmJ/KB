
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.empty())return NULL;
        if(nums.size() == 1)return new TreeNode(nums[0]);
        int idx = 0;
        for(int i = 1;i<nums.size();++i){
            if(nums[i] > nums[idx]){
                idx = i;
            }
        }
        TreeNode* root = new TreeNode(nums[idx]);
        vector<int> left(nums.begin(), nums.begin() + idx);
        vector<int> right(nums.begin() + idx + 1, nums.end());
        root->left = constructMaximumBinaryTree(left);
        root->right = constructMaximumBinaryTree(right);
        return root;
    }
};

void printTree(TreeNode* root){
    if(root == NULL)return;
    std::cout<<root->val<<" ";
    printTree(root->left);
    printTree(root->right);
}


int maxProfitInfinityTimes(vector<int>& prices) {
    return maxProfit(prices, prices.size()/2);
}



int maxProfit(vector<int> prices){
    if(prices.size() < 2)return 0;
    return maxProfit(prices, 2);
}
//1: hold, 0: non-hold
int maxProfit(vector<int> prices, int k){
    int len = prices.size();
    vector<vector<vector<int>>> dp(len, vector<vector<int>>(k, vector<int>(2, 0)));
    for(int i = 1;i<k;++i){
        dp[0][i][1] = -prices[0];
    }
    for(int i = 1;i<prices.size();++i){
        for(int j = 1;j<k;++j){
            dp[i][j][0] = max(dp[i-1][j][1] + prices[i], dp[i-1][j][0]);
            dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] -prices[i]);     
        }           
    }
    return dp[len-1][k-1][0];
}

int maxProfitWithCold(vector<int> prices){
    int len = prices.size();
    {
        // 0: sell, 1: hold, 2: sell many days(>1 day)
        vector<vector<int>> dp(len, vector<int>(3, 0));
        dp[0][1] = -prices[0];
        for(int i = 1;i<len;++i){
            dp[i][0] = dp[i-1][1] + prices[i];
            dp[i][1] = max(dp[i-1][1], dp[i-1][2] - prices[i]);
            dp[i][2] = max(dp[i-1][2], dp[i-1][0]);
        }
        return max(dp[len-1][0], dp[len-1][2]);
    }

    vector<vector<vector<int>>> dp(len, vector<vector<int>>(k, vector<int>(3, 0)));
    for(int i = 1;i<k;++i){
        dp[0][i][1] = -prices[0];
    }
    for(int i = 1;i<prices.size();++i){
        for(int j = 1;j<k;++j){
            dp[i][j][0] = dp[i-1][j][1] + prices[i];
            dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][2] - prices[i]);
            dp[i][j][2] = max(dp[i-1][j][2], dp[i-1][j][0]);     
        }           
    }
    return max(dp[len-1][k-1][0], dp[len-1][k-1][2]);    
}


int main(){
    vector<int> nums{3,2,1,6,7,5};
    std::cout<<maxProfit(nums)<<std::endl;

    Solution so;
    auto res = so.constructMaximumBinaryTree(nums);
    printTree(res);
    return 0;
}



/*

    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])
    dp[i][k][1] = max(dp[i-1][k-1][0] - price[i], dp[i-1][k][1])
    
    //case 1: k = 1
    dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + price[i])
    dp[i][1][1] = max(dp[i-1][0][0] - price[i], dp[i-1][1][1])

    and dp[i-1][0][0] is always zero.





*/
