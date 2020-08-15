#include <iostream>
#include <vector>
#include <algorithm>
#include "k-selection.h"
using namespace std;
int main(){
    //vector<int>v{5,6,8,4,7,3,2,1,9};
    vector<int>v;
    for(int i = 0; i < 15;i++){
        v.push_back(rand()%50 + 1);
    }
    int k = rand()%5+1;
    vector<int>vsort;
    vsort.assign(v.begin(), v.end());
    sort(vsort.begin(), vsort.end());
    for(auto e:vsort){
        cout<<e<<" ";
    }
    cout<<endl;
    cout<<"the "<<k<<" th is "<<vsort[k]<<endl;

    K_SELECTION<int>k_selection(v, k);
    cout<<"use heap to get "<<k<<"th element is "<< k_selection.heap_selection()<<endl;
    K_SELECTION<int>k_test(v, k);
    cout<<"use quickSelect to get "<<k<<"th element is "<< k_test.heap_selection()<<endl;
    return 0;
}