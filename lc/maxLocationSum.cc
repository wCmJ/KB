
#include <iostream>
#include <unistd.h>

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  };
 
class Solution {
public:
    int ans = INT_MIN;
    int maxPathSum(TreeNode* root) {
        maxPathSum_(root);
        return ans;
    }

    int maxPathSum_(TreeNode* root) {
        if(root == NULL)return 0;
        int left = std::max(0, maxPathSum_(root->left));
        int right = std::max(0, maxPathSum_(root->right));
        ans = std::max(ans, left + right + root->val);
        std::cout<<"root val is: "<<root->val<<"left is: " << left << "right is: " << right << std::endl;
        std::cout<<ans<<std::endl;
        return std::max(left, right) + root->val;
    }
};


int main(){
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    Solution so;
    std::cout<< so.maxPathSum(root) << std::endl;
    return 0;
}

