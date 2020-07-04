#include<iostream>
#include<vector>
#include<queue>
#include <algorithm> 
using namespace std;

/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/

class Solution {
public:
    bool is_left_mirror_right(TreeNode* node1, TreeNode* node2){ // 丢入两个空间位置对称的结点，判断其是否相同
        if(node1 == NULL && node2 == NULL){
            return true;
        }else if(node1 == NULL || node2 == NULL){
            return false;
        }else if(node1->val != node2->val){
            return false;
        }
        // 能到这里，说明两个结点不为空，且结点值相等
        bool res1 = is_left_mirror_right(node1->left, node2->right);
        bool res2 = is_left_mirror_right(node1->right, node2->left);
        return res1 && res2;
    }
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return true;
        return is_left_mirror_right(pRoot->left, pRoot->right);   
    }

};

int main(){
   
//    int testarr[] = {5,2,3,4,1,6,7,0,8};
//    vector<int>tes(testarr, testarr + 9);
//    Solution test;
//    for(int i = 0; i < 9; i++){
//        cout<<"insert "<<tes[i]<<endl;
//        test.Insert(tes[i]);
//        printVector(test.frontHalfMaxHeap.my_heap);
//        printVector(test.backHalfMinHeap.my_heap);
//        cout<<"midle number is:"<<test.GetMedian()<<endl;
//    }
    return 0;
}


