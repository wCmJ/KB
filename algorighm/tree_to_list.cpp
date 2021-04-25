#include <iostream>
#include <stack>

using std::stack;

typedef struct bst{
    bst* left;
    bst* right;
    int v;
    bst(int vi):v(vi), left(NULL), right(NULL){}
}bst;


typedef struct slist{
    slist* next;
    int v;
    slist(int vi):v(vi), next(NULL){}
}slist;

static bst* _tree2list(bst* root){
    if(root==NULL)return NULL;
    if(root->left == NULL && root->right == NULL)return root;
    if(root->left == NULL)return _tree2list(root->right);
    if(root->right == NULL){
        root->right = root->left;
        root->left = NULL;
        return _tree2list(root->right);
    }
    bst* tr = root->right;
    root->right = root->left;
    root->left = NULL;
    bst* tl = _tree2list(root->right);
    tl->left = NULL;
    tl->right = tr;
    return _tree2list(tr);
}


bst* tree2list(bst* root){
    if(root == NULL)return NULL;
    _tree2list(root);
    return root;
}

void pre_tree2list(bst* root){
    if(root == NULL)return;
    stack<bst*> sb;
    bst* last = NULL;
    while(true){
        while(root){
            bst* l = root->left, *r = root->right;
            if(last != NULL){
                last->left = NULL;
                last->right = root;
            }
            last = root;
            root = l;
            if(r)sb.push(r);
        }
        if(sb.empty())break;
        root = sb.top();
        sb.pop();
    }
}



void pbst(bst* root){
    if(root == NULL)return;
    pbst(root->left);
    std::cout<<root->v<<" ";
    pbst(root->right);
}

int main(){
    {
        bst* root = new bst(1);
        root->left = new bst(2);
        root->right = new bst(5);
        root->left->left = new bst(3);
        root->left->right = new bst(4);
        root->right->right = new bst(6);
        std::cout<<"tree2list: "<<std::endl;
        pbst(root);
        tree2list(root);
        std::cout<<std::endl;
        pbst(root);
        std::cout<<std::endl;
    }
    {
        bst* root = new bst(1);
        root->left = new bst(2);
        root->right = new bst(5);
        root->left->left = new bst(3);
        root->left->right = new bst(4);
        root->right->right = new bst(6);
        std::cout<<"pre_tree2list: "<<std::endl;
        std::cout<<root->v<<std::endl;
        pbst(root);
        pre_tree2list(root);
        std::cout<<std::endl;
        pbst(root);
        std::cout<<std::endl;
    }
    std::cout<<"----------------------------------------"<<std::endl;
    {
        bst* root = new bst(1);
        root->left = new bst(2);
        root->left->left = new bst(3);
        root->left->left->left = new bst(4);
        root->left->left->left->left= new bst(5);
        root->left->left->left->left->left = new bst(6);
        std::cout<<"tree2list: "<<std::endl;
        pbst(root);
        tree2list(root);
        std::cout<<std::endl;
        pbst(root);
        std::cout<<std::endl;
    }
    {
        bst* root = new bst(1);
        root->left = new bst(2);
        root->left->left = new bst(3);
        root->left->left->left = new bst(4);
        root->left->left->left->left= new bst(5);
        root->left->left->left->left->left = new bst(6);
        std::cout<<"pre_tree2list: "<<std::endl;
        pbst(root);
        pre_tree2list(root);
        std::cout<<std::endl;
        pbst(root);
        std::cout<<std::endl;
    }

    return 0;
}
