#include<iostream>
#include<vector>
using namespace std;

int minNumberInRotateArray(const vector<int> &rotateArray){
    // 顺序查找 O(N)
    if(rotateArray.size() == 0)
        return 0;   
    for(int index1 = 0, index2 = 1;index2 < rotateArray.size(); index2 ++ ){
        if(rotateArray[index1] > rotateArray[index2]){
            return rotateArray[index2];
        }
    }
}
int main(){
    int array[6] = {4,5,6,1,2,3};
    vector<int>rotateArray(array, array + 6);
    cout << "min of rotateArray is :" << minNumberInRotateArray(rotateArray) << endl;

    return 0;
}