#include<iostream>
#include<string>
using namespace std;
struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x)
        : val(x), left(NULL), right(NULL){}
};
void printNode(TreeNode &TN){ 
    string left;
    string right;
    if(TN.left != NULL){
        left = to_string(TN.left -> val);
    }else{
        left = "NULL";
    }
    if(TN.right != NULL){
        right = to_string(TN.right -> val);
    }else{
        right = "NULL";
    }
    cout << "node "<<TN.val<<", left is "<<left<<", right is "<<right<<endl;
}
//非递归
// 1. 先序
void DLR(const TreeNode *root){
    if(root = NULL)
        return ;
    
    TreeNode* note = root;
    TreeNode* rightnode = NULL;
    stact<TreeNode*>treeStack;  //用栈来存访问过的结点，因为后面要用存储的结点来访问右子树
    //遍历整个树
    while(){
        // 先遍历左子树
        while(note != NULL){
            treeStack.push(note);
            note = note -> left;
        }

        while(){
            treeStack.pop();  // 栈顶是某个根结点
            rightnode = treeStack.top() -> right;  // 只是利用根节点取出其右子树
            leftnode = treeStack.top() -> left;    // 左子树
            while(leftnode != NULL){
                treeStack.push(leftnode);


            }
        }
    }
    



}


int main(){
    TreeNode TN1(1);
    TreeNode TN2(2);
    TreeNode TN3(3);
    TreeNode TN4(4);
    TreeNode TN5(5);
    TreeNode TN6(6);
    TreeNode TN7(7);
    TreeNode TN8(8);
    TreeNode TN9(9);
    TreeNode TN10(10);
    TreeNode TN11(11);
    TreeNode TN12(12);
    TN1.left = &TN2; TN1.right = &TN3;
    TN2.left = &TN4; TN2.right = &TN5;
    TN3.left = &TN6; TN3.right = &TN7;
    TN4.left = NULL; TN4.right = NULL;
    TN5.left = &TN8; TN5.right = &TN9;
    TN6.left = NULL; TN6.right = &TN10;
    TN7.left = &TN1; TN7.right = &TN12;
    TN8.left = NULL; TN8.right = NULL;
    TN9.left = NULL; TN9.right = NULL;
    TN10.left = NULL; TN10.right = NULL;
    TN11.left = NULL; TN11.right = NULL;
    TN12.left = NULL; TN12.right = NULL;
    printNode(TN1);

    return 0;
}