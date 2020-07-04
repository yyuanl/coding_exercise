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
    vector<vector<int>>res;
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        if(root == NULL){
            return res;
        }
        vector<int>path;
        FindPathTraverseTree(root, path, expectNumber, 0);
        return res;

    }
    void FindPathTraverseTree(TreeNode* node, vector<int>path, int expectNumber, int currPathSum){
        path.push_back(node->val);
        currPathSum += node->val;
        if(currPathSum == expectNumber && node->left == NULL && node->right == NULL){ //找到一个符合条件的路径
            res.push_back(path);
        }
        if(node->left != NULL){
            FindPathTraverseTree(node->left, path, expectNumber, currPathSum);
        }
        if(node->right != NULL){
            FindPathTraverseTree(node->right, path, expectNumber, currPathSum);
        }
    }
};

    



int main(){
    int arr[] = {2,4,3,6,11,9,5};
    vector<int>ve(arr, arr + 6);
    cout<<VerifySquenceOfBST(ve)<<endl;
    return 0;
}


