#include <stack>
#include <iostream>
using std::stack;



struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v):val(v),left(NULL),right(NULL){}
};


class Solution {
public:
    void recoverTree(TreeNode* root) {
        if(root == NULL)return;
        TreeNode* last = NULL;
        TreeNode* first = NULL, *second = NULL;
        stack<TreeNode*> record;
        while(true){
            while(root){
                record.push(root);
                root = root->left;
            }
            if(record.empty())break;
            root = record.top();
            record.pop();
            if(last != NULL){
                std::cout<<"last not null"<<std::endl;
                std::cout<<"last->val: "<<last->val<<" . root->val: "<<root->val<<std::endl;
                if(root->val < last->val){
                    if(first == NULL){
                        first = last;
                    }
                    second = root;
                }
            }
            last = root;
            root = root->right;
        }
        if(first == NULL || second == NULL){
            std::cout<<"first: "<<first<<std::endl;
            std::cout<<"second: "<<second<<std::endl;
        }
        int tmp = first->val;
        first->val = second->val;
        second->val = tmp;
    }
};


int main(){
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(2);
    Solution so;
    so.recoverTree(root);

    return 0;

}



