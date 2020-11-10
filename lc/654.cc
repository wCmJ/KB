
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

int main(){
    vector<int> nums{3,2,1,6,0,5};
    Solution so;
    auto res = so.constructMaximumBinaryTree(nums);
    printTree(res);
    return 0;
}

