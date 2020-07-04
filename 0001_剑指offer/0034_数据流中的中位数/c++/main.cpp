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
struct dataHeap
    {
        vector<int>my_heap;
        int scale;
    }frontHalfMaxHeap,backHalfMinHeap;//数据流前面最小的一半   数据流后面最大的一半
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
    struct dataHeap
    {
        vector<int>my_heap;
        int scale;
        dataHeap():scale(0){}
    }frontHalfMaxHeap,backHalfMinHeap;//数据流前面最小的一半   数据流后面最大的一半
    static bool maxHeapJudgeCond(int currVal, int parentVal){
        return currVal > parentVal;
    }
    static bool minHeapJudgeCond(int currVal, int parentVal){
        return currVal < parentVal;
    }
    
    void heapAddElem(struct dataHeap & heap_str, int ele, bool (*judge_f)(int, int)){ //从大根堆底添加一个元素  创建堆的过程 也是数据流前半部分增加一个数字
        heap_str.my_heap.push_back(ele);
        heap_str.scale += 1;
        int index = heap_str.my_heap.size() - 1;
        int parentIndex;
      
        while(index != 0){
            //cout<<index<<"===========\n"<<endl;
            parentIndex = (index -1) >> 1;
            
            if(judge_f(heap_str.my_heap[index], heap_str.my_heap[parentIndex])){
                heap_str.my_heap[parentIndex] = heap_str.my_heap[parentIndex]^heap_str.my_heap[index];
                heap_str.my_heap[index] = heap_str.my_heap[parentIndex]^heap_str.my_heap[index];
                heap_str.my_heap[parentIndex] = heap_str.my_heap[parentIndex]^heap_str.my_heap[index];
                index = parentIndex;
            }else{
                break;
            }
        }
        //cout<<index<<"===========\n"<<endl;   
    }
    void heapAdjust(struct dataHeap & which_heap_strc, int num, bool(*judge_func)(int, int)){ //大根堆根被替换 自我调整 自顶向下
        which_heap_strc.my_heap[0] = num;       
        int childBigIndex;
        int index = 0;
        int leftIndex;
        int rightIndex;
        while(index < which_heap_strc.scale){
            leftIndex = 2 * index + 1;
            rightIndex = leftIndex + 1;
            childBigIndex = index;
            if(leftIndex < which_heap_strc.scale){
                if(judge_func(which_heap_strc.my_heap[leftIndex], which_heap_strc.my_heap[index]))
                    childBigIndex = leftIndex;
            }

            if(rightIndex < which_heap_strc.scale){
                if(judge_func(which_heap_strc.my_heap[rightIndex], which_heap_strc.my_heap[childBigIndex]))
                    childBigIndex = rightIndex;
            }

            if(childBigIndex == index){
                break;
            }else{
                which_heap_strc.my_heap[index] = which_heap_strc.my_heap[index]^which_heap_strc.my_heap[childBigIndex];
                which_heap_strc.my_heap[childBigIndex] = which_heap_strc.my_heap[index]^which_heap_strc.my_heap[childBigIndex];
                which_heap_strc.my_heap[index] = which_heap_strc.my_heap[index]^which_heap_strc.my_heap[childBigIndex];
                index = childBigIndex;
            }
        }
    }
    void Insert(int num)
    {
        if(frontHalfMaxHeap.my_heap.empty()){
            //直接往前半部分插入
            heapAddElem(frontHalfMaxHeap,num,maxHeapJudgeCond);
            return ;
        }
        // cout<<"****\n"<<endl;
        if(backHalfMinHeap.my_heap.empty()){
            //直接往后半部分插入
            if(frontHalfMaxHeap.my_heap[0] < num){
                heapAddElem(backHalfMinHeap,num, minHeapJudgeCond);
            }else{
                heapAddElem(backHalfMinHeap,frontHalfMaxHeap.my_heap[0],minHeapJudgeCond);
                heapAdjust(frontHalfMaxHeap,num,maxHeapJudgeCond);
                //maxHeapAdjust(num);
            }  
            return;  
        }
        //决定往哪个堆插入 -> 插入数据是哪个？
        if(frontHalfMaxHeap.scale == backHalfMinHeap.scale){ //前半部分增长一个数字
            if(num < backHalfMinHeap.my_heap[0]){ //num直接加入前半部分
                heapAddElem(frontHalfMaxHeap,num,maxHeapJudgeCond);
                return;
            }else{ //后半部分的最小的值即根值应该加入前半部分
                heapAddElem(frontHalfMaxHeap,backHalfMinHeap.my_heap[0], maxHeapJudgeCond);
                heapAdjust(backHalfMinHeap,num,minHeapJudgeCond);
                return;
            }

        }else if(backHalfMinHeap.scale < frontHalfMaxHeap.scale){//后半部分增长一个数字
            if(frontHalfMaxHeap.my_heap[0] < num){ //num直接加入后半部分
                heapAddElem(backHalfMinHeap,num, minHeapJudgeCond);
                return;
            }else{
                heapAddElem(backHalfMinHeap,frontHalfMaxHeap.my_heap[0], minHeapJudgeCond);
                heapAdjust(frontHalfMaxHeap,num, maxHeapJudgeCond);
                //maxHeapAdjust(num);
                return;
            }
        }
        //cout<<"after insert, front part adn back part respectively...\n"<<endl;       
    }
    double GetMedian()
    { 
        if(frontHalfMaxHeap.scale == backHalfMinHeap.scale){
            return ((double)frontHalfMaxHeap.my_heap[0] + (double)backHalfMinHeap.my_heap[0] )/2;
        }else{
            return (double)frontHalfMaxHeap.my_heap[0];
        }
    }

};

int main(){
   
   int testarr[] = {5,2,3,4,1,6,7,0,8};
   vector<int>tes(testarr, testarr + 9);
   Solution test;
   for(int i = 0; i < 9; i++){
       cout<<"insert "<<tes[i]<<endl;
       test.Insert(tes[i]);
       printVector(test.frontHalfMaxHeap.my_heap);
       printVector(test.backHalfMinHeap.my_heap);
       cout<<"midle number is:"<<test.GetMedian()<<endl;
   }
    return 0;
}


