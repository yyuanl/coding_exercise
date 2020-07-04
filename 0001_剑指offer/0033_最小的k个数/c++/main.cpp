#include<iostream>
#include<vector>
#include<queue>
#include <algorithm> 
using namespace std;
// struct TreeNode {
// 	int val;
// 	struct TreeNode *left;
// 	struct TreeNode *right;
// 	TreeNode(int x) :
// 			val(x), left(NULL), right(NULL) {
// 	}
// };
void printVector(vector<int>& v){
    int size = v.size();
    cout<<"[";
    for(int i = 0;i < size;i++)
        cout<<v[i]<<" ";
    cout<<"]"<<endl;
}
/*
                                9
                        6              5
                    4      3        2      1
对应大根堆用一个数组表示[9,6,5,4,3,2,1] 
*/
class Solution {
public:
    vector<int>maxHeap;
    void createMaxHeap(vector<int>&maxHeap, int ele){//创建大根堆，一个数组，加入一个新的数字，自底向上的调整，使之保证大根堆的规则   
        int parentIndex;
        int temp;
        maxHeap.push_back(ele);
        int index = maxHeap.size() - 1;
        while(index != 0){
            parentIndex = (index - 1)>>1;
            //cout<<"parent index is "<<parentIndex<<" ,index is"<<index<<endl;
            if(maxHeap[parentIndex] < maxHeap[index]){
                temp = maxHeap[parentIndex];
                maxHeap[parentIndex] = maxHeap[index];
                maxHeap[index] = temp;
            }else{
                break;
            }
            index = parentIndex;
        }
    }
    void adjustMaxHeap(vector<int>&maxHeap, int ele){ // 自顶向下
        if(maxHeap[0] < ele)
            return ;
        maxHeap[0] = ele;
        int index = 0;
        int len = maxHeap.size(); 
        int largestIndex;
        int leftIndex;
        int rightIndex;
        int temp;
        while(index < len){
            largestIndex = index;
            leftIndex = 2*index + 1;
            rightIndex = leftIndex + 1;
            if(leftIndex < len){ //存在左子树
                if(maxHeap[largestIndex] < maxHeap[leftIndex])
                    largestIndex = leftIndex;
            }
            if(rightIndex < len){ //存在右子树
                if(maxHeap[largestIndex] < maxHeap[rightIndex])
                    largestIndex = rightIndex;
            }
            if(index == largestIndex){ //符合大根堆
                break;
            }else{
                temp = maxHeap[index];
                maxHeap[index] = maxHeap[largestIndex];
                maxHeap[largestIndex] = temp;
            }  
            index = largestIndex;
        }

    }
    void reversVector(vector<int>&vec){
        int size = vec.size();
        int halfSize = size>>1;
        for(int i = 0; i < halfSize; i++){
            vec[i] = vec[i]^vec[size-1-i];
            vec[size-1-i] = vec[i]^vec[size-1-i];
            vec[i] = vec[i]^vec[size-1-i];
        }

    }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        if(input.empty() || k <= 0 || input.size() < k)
            return maxHeap;
        int inputLen = input.size();
    
        for(int i = 0; i < k; i++){
            //cout<<input[i]<<"will be put to maxHeap..\n"<<endl;
            createMaxHeap(maxHeap, input[i]);  //利用前k个数创建一个大根堆
        }
        // 维护这个大根堆
        for(int i = k; i < inputLen; i++)
            adjustMaxHeap(maxHeap, input[i]);
        
        reversVector(maxHeap);
        //sort(maxHeap.begin(), maxHeap.end());
        return maxHeap;
    }
};
int main(){
    /* test code
    Solution test_solution;  
    int arr[] = {4,5,1,6,2,7,3,8};
    vector<int>ve(arr, arr + 8);
    int len;
    test_solution.GetLeastNumbers_Solution(ve, 4);
    */
    return 0;
}


