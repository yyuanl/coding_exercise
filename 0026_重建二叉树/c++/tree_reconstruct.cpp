#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
void printVe(vector<int>& v){
    int size = v.size();
    for(int i = 0;i < size;i++){
        cout<<v[i]<<" ";
    }
    cout<<"\n"<<endl;
}
TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
    cout<<"pre:\n"<<endl;
    printVe(pre);
    cout<<"vin:\n"<<endl;
    printVe(vin);
    if(pre.empty() || vin.empty()){
        return NULL;
    }
    if(pre.size() != vin.size())
        return NULL;


    int root_val = pre[0];
    int index_root;
    TreeNode* root = new TreeNode(root_val);
    vector<int>pre_left, pre_right; //左子树的前序输出 右子树的中序输出
    vector<int>vin_left, vin_right;
    vector<int>::iterator it = find(vin.begin(), vin.end(), root_val);
    
    
    if(pre.size() == 1)  //叶子节点的情况
        return root;
    // if(it == vin.begin()){  // 无左孩子树
    //     root -> left = NULL;
    //     pre_right.assign(pre.begin() + 1, pre.end());
    //     vin_right.assign(vin.begin() + 1, vin.end());
    //     root -> right = reConstructBinaryTree(pre_right, vin_right);
    // }else{

    // }
    index_root = distance(vin.begin(), it);
    pre_left.assign(pre.begin() + 1, pre.begin() + index_root + 1);
    vin_left.assign(vin.begin(), it);
    pre_right.assign(pre.begin() + index_root + 1, pre.end());
    vin_right.assign(it + 1, vin.end());
    root->left = reConstructBinaryTree(pre_left, vin_left);
    root->right = reConstructBinaryTree(pre_right, vin_right);
    return root; 
}
void freeTree(TreeNode* root){
    if(root == NULL)
        return ;
    freeTree(root -> left);
    freeTree(root -> right);
    delete root;

}
void printTree(TreeNode* root){
    if(root == NULL)
        return;
    cout<<root->val<<" ";
    printTree(root -> left);
    printTree(root -> right);

}
int main(){
    int arr[] = {1,2,4,7,3,5,6,8};
    int arr1[] = {4,7,2,1,5,3,8,6};
    int size;
    int index;
    TreeNode* tree;
    vector<int>::iterator it;
    vector<int>pre(arr, arr + 8);
    vector<int>vin(arr1, arr1 + 8);
    // vector<int>test;

    // it = find(vin.begin(), vin.end(), 1);
    // index = distance(vin.begin(), it);
    // cout<<"it val is "<<*it<<endl;
    // test.assign(pre.begin() + 1,pre.begin() + index + 1);
    // size = test.size();
    // cout<<"size is "<<size<<"\n"<<endl;
    // for(int i = 0; i <size;i++)
    //     cout<<test[i]<<"\n"<<endl;
    tree = reConstructBinaryTree(pre, vin);
    cout<<"reconstructed tree is :\n"<<endl;
    printTree(tree);

    freeTree(tree);





    return 0;
}