#include<iostream>
#include<string>
#include<stack>
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
void DLR1(TreeNode * root){ 
    if(root == NULL)
        return ;  
    TreeNode* node = root;  //记录当前结点
    stack<TreeNode*>treeStack;  //用栈来存访问过的结点，因为后面要用存储的结点来访问右子树
    //遍历整个树
    while((node != NULL) || (treeStack.empty() != true)){ //结点为空，栈为空。只要这两件事不同时发生就可以继续
        // 把左边结点放入栈
        while(node != NULL){ //这段代码负责向左 /
            printNode(*node);  //访问树结点的操作，这里定义为打印结点值
            treeStack.push(node);
            node = node -> left;
        } // 这里node一定是最左结点（相对）
        /*这里要做两件事：
        1.当前结点的右子树根节点准备丢入栈 
        2. pop()到当前结点的父结点，以便当前结点平行的右子树（即，父结点的右子树）访问完成，可以对父结点的右子树进行操作*/
        if(treeStack.empty() != true){  /*    这段代码负责向右  \                 */
            node = treeStack.top();  // note 与栈顶同步，pop之后，该栈顶会消失，如果不记录则无法获取其右子树
            node = node -> right;  //当前结点设置为右结点，准备往栈里丢
            treeStack.pop();           
        }

        if(node != NULL){
            cout<<"now node is "<< to_string(node -> val)<<"  ";
        }else{
            cout<<"now node is NULL ";
        }
        if(treeStack.empty() != true){
            cout<<"stack top is "<<to_string(treeStack.top() -> val)<<endl;
        }else{
            cout<<"stack top is NULL" <<endl;
        }
        cout<<"\n"<<endl;
    }
}
// 另外一种写法
void DLR2(TreeNode* root){
    TreeNode* current_node;  //记录当前栈top
    stack<TreeNode*>treeStack;
    treeStack.push(root);
    while(treeStack.empty() != true){
        current_node = treeStack.top(); // 当前结点
        printNode(*current_node);
        treeStack.pop();  //访问当前结点之后pop之

        if(current_node -> right != NULL){ // 先push右子树（后访问）
            treeStack.push(current_node -> right);
        }

        if(current_node -> left != NULL){ // 再push左子树（先访问）
            treeStack.push(current_node -> left);
        }
    }
}

// 2. 中序
void LDR(TreeNode* root){
    TreeNode* current_node = root;
    stack<TreeNode*>treeStack;
    while((current_node != NULL) || (treeStack.empty() != true)){
        while(current_node != NULL){
            treeStack.push(current_node);
            current_node = current_node ->left;
        }
        if(treeStack.empty() != true){
            current_node = treeStack.top();
            printNode(*current_node);
            treeStack.pop();
            current_node = current_node -> right;
        }
    }
}
// 3.后序
void LDR(TreeNode* root){
    TreeNode* current_node = root;
    stack<TreeNode*>treeStack;
    stack<bool>flagStack;  // false表示从当前结点访问左结点
    while(current_node != NULL){
        treeStack.push(current_node);
        current_node = current_node -> left;
        flagStack.push(false);
    }
}




int main(){
    TreeNode TN1 = TreeNode(1);
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
    TN7.left = &TN11; TN7.right = &TN12;
    TN8.left = NULL; TN8.right = NULL;
    TN9.left = NULL; TN9.right = NULL;
    TN10.left = NULL; TN10.right = NULL;
    TN11.left = NULL; TN11.right = NULL;
    TN12.left = NULL; TN12.right = NULL;
    cout<<"..................DLR1............................"<<endl;
    DLR1(&TN1);
    cout<<"..................DLR2............................"<<endl;
    DLR1(&TN1);
    cout<<"..................LDR............................"<<endl;
    LDR(&TN1);


    return 0;
}