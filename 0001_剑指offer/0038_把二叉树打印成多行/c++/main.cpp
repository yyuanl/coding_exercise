#include<iostream>
#include<vector>
#include<stack>
#include <algorithm> 
#include <queue>
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
    cout<<"----------"<<endl;
    int s = v.size();
    cout<<"[";
    for(int i = 0;i < s;i++)
        cout<<v[i]<<" ";
    cout<<"]\n"<<endl;

}
void printEveryLeve(vector<vector<int> > &res){
    cout<<"----------"<<endl;
    int s = res.size();
    cout<<"-*********---"<<s<<endl;
    for(int i = 0; i < s; i++){
        cout<<"-*********---"<<endl;
        cout<<i<<": ";
        printVector(res[i]);
    }
}


class Solution {
public:
    char* Serialize(TreeNode *root) {    
        
    }
    TreeNode* Deserialize(char *str) {
    
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
    cout<<"here.."<<endl;
    printEveryLeve(test.res);


    return 0;
}
/*
                                                            1
                                                2                      3
                                            4       5              6       7
*/


