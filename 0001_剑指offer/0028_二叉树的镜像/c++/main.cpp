#include<iostream>
using namespace std;
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    treeNode(int x):val(x), left(NULL), right(NULL){}
    
}
void Mirror(TreeNode *pRoot) {
    if(pRoot == NULL)
        return ;
    TreeNode* node = pRoot->left;
    pRoot->left = pRoot->right;
    pRoot->right = node;
    Mirror(pRoot->left);
    Mirror(pRoot->right);
}
int main(){



    return 0;
}
