#include<iostream>
#include<vector>
#include<queue>
#include <algorithm> 
using namespace std;
/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
// struct dataHeap
//     {
//         vector<int>my_heap;
//         int scale;
//     }frontHalfMaxHeap,backHalfMinHeap;//数据流前面最小的一半   数据流后面最大的一半
// void printVector(vector<int>& v){
//     int size = v.size();
//     cout<<"[";
//     for(int i = 0;i < size;i++)
//         cout<<v[i]<<" ";
//     cout<<"]"<<endl;
// }
/*
                                9
                        6              5
                    4      3        2      1
对应大根堆用一个数组表示[9,6,5,4,3,2,1] 
*/
/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        // 如果有右子树，接下来必然打印右子树的最左边的那个数字
        // 如果没有右子树，向上找，如果能找到某个结点p，使得p的左边部分包含pNode，则下个打印P。如果没有
        // 这样的结点，说明pNode是最后一个结点
        TreeLinkNode* node;
        if(pNode->right != NULL){
            node = pNode->right;
            while(node -> left != NULL)
                node = node -> left;
            return node;
        }else{
            node = pNode;
            while(node -> next != NULL){
                if(node -> next -> left == node)
                    return node -> next;
                node = node -> next;
            }
            return NULL;
        }
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


