#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void bubbleSort(vector<int>&vec, int lo, int hi){
    int end = hi;
    int temp;
    
    while(end > lo){  // 扫描区间 [lo, end] 无序向量 相邻两个元素异序

        for(int ix = lo;ix < end;ix++)
            if(vec[ix] > vec[ix + 1]){
                swap(vec[ix], vec[ix + 1]);
                temp = ix;
            }  //区间扫描结束 要产生一个右端点 右端点到hi是有序的，该区间不必再做交换

        end = temp;    
    }
}
void printVector(vector<int>&vec){
    vector<int>::iterator it = vec.begin();
    while(it != vec.end()){
        cout<<*it<<" ";
        it++;
    }

}
int main(){
    int arr[] = {7,6,5,8,4,9,10,11,2};
    vector<int>vect(arr, arr+9);
    printVector(vect);
    cout<<"\n----------------------"<<endl;
    bubbleSort(vect, 0, vect.size() - 1);
    printVector(vect);
    

    return 0;
}