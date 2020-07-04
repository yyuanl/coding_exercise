#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
bool PrintFromTopToBottom(TreeNode* root, vector<int>res) {
    if(root == NULL)
        return false;
    queue<TreeNode*>qe;
    TreeNode* temp_p;
    qe.push(root);
    while(!qe.empty()){
        temp_p = qe.front();
        res.push_back(temp_p->val);
        qe.pop();
        if(temp_p->left != NULL){
            qe.push(temp_p->left);
        }
        if(temp_p->right != NULL){
            qe.push(temp_p->right);
        }

    }
    return true;
    
/*
     1
  2    3
4  5  6  7 
意思是返回一个{1234567}
依次把 root left right 丢到队列里 队头每次压入vector，处理完就pop之；

*/


}
int main(){


    return 0;
}


