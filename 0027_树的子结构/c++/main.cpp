#include<iostream>
using namespace std;
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x):val(x), left(NULL), right(NULL){}
}; 
bool IsSubtree(TreeNode* parent, TreeNode* child){  // 根节点相同情况下是否是子树
   if(child == NULL){  // 这里判断注意理解， 这个函数关注parent ->val等于child->val情况下 是否为父子树关系
                        //因此，我们认为child为空，我们要返回true， 这里要区分和题目表达的不同。这是递归基
       return true;
   }else if(parent == NULL){
       return false;
   }
   if(parent -> val != child -> val){
       return false;
   }else{
       return IsSubtree(parent->left, child->left) && IsSubtree(parent->right, child->right);
   }
}
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
    if(pRoot1 == NULL || pRoot2 == NULL)  // 这里判断很注意理解 这个函数是找pRoot1中某个节点是否与pRoot2->val相同
        return false;
    bool res;
    if(pRoot1->val == pRoot2->val){
        res = IsSubtree(pRoot1, pRoot2);
        if(res){
            return true;
        }else{
            return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
        }
    }else{
        return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    }

}
int mian(){




    return 0
}