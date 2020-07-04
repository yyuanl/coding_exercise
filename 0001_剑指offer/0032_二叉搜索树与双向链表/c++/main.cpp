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
void printVector(vector<int>& v){
    int size = v.size();
    cout<<"[";
    for(int i = 0;i < size;i++)
        cout<<v[i]<<" ";
    cout<<"]"<<endl;
}
class Solution {
public:
    TreeNode* combine(TreeNode* leftList, TreeNode *root, TreeNode *rightList){
        if(root == NULL)
            return NULL;
        TreeNode *moveP = NULL;
        if(leftList != NULL){
            moveP = leftList;
            while(moveP->right != NULL){
                moveP = moveP->right;
            }
            moveP->right = root;
            root->left = moveP;
        }
        if(rightList != NULL){
            root->right = rightList;
            rightList->left = root;
        }
        if(leftList == NULL)
            return root;
        return leftList;
    }

    TreeNode* retListHead(TreeNode* node){
        if(node == NULL)
            return NULL;
        TreeNode* leftList = retListHead(node->left);
        TreeNode* rightList = retListHead(node->right);
        // 合并leftList node rightList
        return combine(leftList, node, rightList);
    }

    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(pRootOfTree == NULL)
            return NULL;
        return retListHead(pRootOfTree);
    }

};

    



int main(){
    
    return 0;
}


