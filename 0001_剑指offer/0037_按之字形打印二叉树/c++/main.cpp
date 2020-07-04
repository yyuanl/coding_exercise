#include<iostream>
#include<vector>
#include<stack>
#include <algorithm> 
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
    int s = v.size();
    cout<<"[";
    for(int i = 0;i < s;i++)
        cout<<v[i]<<" ";
    cout<<"]\n"<<endl;

}
void printEveryLeve(vector<vector<int> > &res){
    int s = res.size();
    for(int i = 0; i < s; i++){
        cout<<i<<": ";
        printVector(res[i]);
    }
}


class Solution {
public:
    vector<vector<int> > res;
    vector<vector<int> > Print(TreeNode* pRoot) {
        if(pRoot == NULL)
            return res;
        
        stack<TreeNode*> s_level[2];
        s_level[0].push(pRoot);
        vector<int>v_every_level;
        #define L2R 0
        #define R2L 1
        int current_level = L2R;
        int next_level = R2L;
        TreeNode* tem_top;

        while( ( !(s_level[current_level]).empty() )  ||  ( !(s_level[next_level]).empty() ) ){
            tem_top = s_level[current_level].top();
            s_level[current_level].pop();
            v_every_level.push_back(tem_top->val);
            // 构造下一层栈
            if(current_level == L2R){
                if(tem_top->left != NULL)
                    s_level[next_level].push(tem_top->left);
                if(tem_top->right != NULL)
                    s_level[next_level].push(tem_top->right);
            }
            if(current_level == R2L){
                if(tem_top->right != NULL)
                    s_level[next_level].push(tem_top->right);
                if(tem_top->left != NULL)
                    s_level[next_level].push(tem_top->left);
            }
            if(s_level[current_level].empty()){
                res.push_back(v_every_level);
                v_every_level.clear();
                current_level = 1 - current_level;
                next_level = 1 - next_level;
            }

        }
        return res;    
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

    Solution test;
    TreeNode n1(1);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n4(4);
    TreeNode n5(5);
    TreeNode n6(6);
    TreeNode n7(7);
    n1.right = &n3; n1.left = &n2;
    n2.right = &n5; n2.left = &n4;
    n3.right = &n7; n3.left = &n6;
    test.Print(&n1);
    printEveryLeve(test.res);


    return 0;
}
/*
                                                            1
                                                2                      3
                                            4       5              6       7
*/


