#include<iostream>
#include<vector>
using namespace std;

int special_find(const vector<int> &rotateArray){
    // 顺序查找 O(N)
    if(rotateArray.size() == 0)
        return 0;   
    for(int index1 = 0, index2 = 1;index2 < rotateArray.size(); index2 ++ ){
        if(rotateArray[index1] > rotateArray[index2]){
            return rotateArray[index2];
        }
    }
}

int minNumberInRotateArray(const vector<int> &rotateArray){
    /*
    最小元素小于等于右边元素，小于等于左边元素，利用二分查找缩小范围 O（lg(n) )
    特殊情况， {0,1,1,1,1,1}=>{1，1，1，1，0，1}或者=>{1,0,1,1,1,1},中间等于最左、最右数值，需要使用顺序查找
    */
    if(rotateArray.size() == 0)
        return 0;
    
    int left_index = 0, right_index = rotateArray.size() - 1;
    int middle_index = (right_index + left_index) / 2;
    if(rotateArray[middle_index] == rotateArray[left_index] && rotateArray[middle_index] == rotateArray[right_index]){
        // 顺序查找
        cout<<"use special find..."<< endl;
        return special_find(rotateArray);
    }else{
        // 二分查找
       
        while(right_index - left_index > 2){

            if(right_index == left_index + 2){  // 退出循环条件
                // middle_index = (left_index + right_index) / 2;
                cout <<"quit while ..." <<endl;
                break; 
            }

            if(rotateArray[left_index] < rotateArray[middle_index])
                left_index = middle_index;
                           
            if(rotateArray[middle_index] < rotateArray[right_index])
                right_index = middle_index;

            middle_index = (left_index + right_index) / 2;
           
            cout << "left middle left "<<left_index<<" "<<middle_index<<" "<<right_index<<endl;
                         
        }
        return rotateArray[middle_index];
        
    }
}
int main(){
    int array1[7] = {3,4,5,6,7,1,2};
    int array2[6] = {1,1,1,1,0,1};
    int array3[6] = {1,0,1,1,1,1};
    vector<int>rotateArray1(array1, array1 + 7);
    vector<int>rotateArray2(array2, array2 + 6);
    vector<int>rotateArray3(array3, array3 + 6);
    cout<<"rotateArray1 min value is "<<minNumberInRotateArray(rotateArray1)<<"\n"<<endl;
    cout<<"rotateArray2 min value is "<<minNumberInRotateArray(rotateArray2)<<"\n"<<endl;
    cout<<"rotateArray3 min value is "<<minNumberInRotateArray(rotateArray3)<<"\n"<<endl;
    return 0;
}