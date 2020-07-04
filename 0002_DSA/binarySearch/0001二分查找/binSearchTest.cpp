#include <iostream>
#include <vector>
#include "binSearch.h"
using namespace std;

int main(){
    int arr[] = {3, 5, 7, 8, 8, 10, 11, 12};  
    vector<int>vec(arr, arr + 8);
    int len = vec.size();
    BinSearch<int>bins;

    cout<<"use binSearch1..."<<endl;
    cout<<"elem :"<<bins.binSearch1(vec, 0, len, 4)<<endl;
    cout<<"elem :"<<bins.binSearch1(vec, 0, len, 4)<<endl;
    cout<<"elem :"<<bins.binSearch1(vec, 0, len, 7)<<endl;

    cout<<"use binSearch2..."<<endl;
    cout<<"elem :"<<bins.binSearch2(vec, 0, len, 4)<<endl;
    cout<<"elem :"<<bins.binSearch2(vec, 0, len, 4)<<endl;
    cout<<"elem :"<<bins.binSearch2(vec, 0, len, 7)<<endl;

    cout<<"test to find repeat element..."<<endl;
    cout<<"elem :"<<bins.binSearch1(vec, 0, len, 8)<<endl;
    cout<<"elem :"<<bins.binSearch2(vec, 0, len, 8)<<endl;
    
}