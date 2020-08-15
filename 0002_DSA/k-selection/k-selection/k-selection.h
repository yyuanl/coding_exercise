#ifndef __K_SELECTION__
#define __K_SELECTION__
#include <vector>
#include <iostream>
#include "D:/coding_exercise/0002_DSA/heap/heap.h"
//#define VTR(v) ( *(v))
using namespace std;
template <typename T>
class K_SELECTION{
public:
    K_SELECTION(vector<T>&vtr, int k_args):v(vtr), k(k_args){}
    int heap_selection(){
        vector<int>big_v(v.begin(),v.begin() + k);
        vector<int>small_v(v.begin() + k, v.end());
        Heap<int>big_hp(big_v,big_v.size(), true);
        Heap<int>small_hp(small_v,small_v.size(), false);
        while(big_hp.getTop() > small_hp.getTop()){
            T t = big_hp.getTop();
            big_hp.reaplaceTop(small_hp.getTop());
            small_hp.reaplaceTop(t);
        }
        return small_hp.getTop();
    }
    int quick_selection(){
        int i , j;
        for(int lo = 0, hi = v.size() - 1;lo < hi;){
            i = lo; j = hi; int pivot = v[lo];
            while( i < j){ //  维护 LUG 。使得轴点就为 
                while(i<j&&pivot<=v[j]){j--;}v[i] = v[j];
                while(i<j&&v[i]<=pivot){i++;}v[j] = v[i];
            }
            v[i] = pivot;
            if(k == i){
                return v[k];
            }else if(k < i){
                hi = i-1;
            }else{
                lo = i + 1;
            }
        }

    }
private:
    vector<int> &v;
    int k;
};
#endif