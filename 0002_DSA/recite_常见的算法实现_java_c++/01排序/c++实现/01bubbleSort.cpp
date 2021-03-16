#include <iostream>
#include <vector>
using namespace std;
void printv(vector<int>&v){
    for(auto &e:v){
        cout<<e<<" ";
    }
    cout<<endl;
}

void bubbleSort(vector<int>&v,int low, int hi){//[)左闭右开区间
    if(low < 0 || hi > v.size()){
        return ;
    }
    int last = hi;
    while(last - low > 1){ //扫描区间等于1时结束
        int scan_end = last; //scan_end表示每次扫描区间的右端点
        last = low;    // 很关键，如果当前扫描last没有被修改，说明扫描区间已经有序，外循环要退出
        for(int i = low;i < scan_end-1;i++){//在扫描区间内逐次相邻扫描比较  
            if(v[i] > v[i+1]){
                swap(v[i], v[i+1]);
                last = i+1;
            }
        }
        printv(v);
    }
}

int main(){
    vector<int>v{15,7,8,10,6,11,20,18};
    bubbleSort(v,0,v.size());
    printv(v);
    return 0;
}