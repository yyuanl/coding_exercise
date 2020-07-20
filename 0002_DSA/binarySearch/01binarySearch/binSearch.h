#pragma once
#include <vector>
using namespace std;

template <typename T>
class BinSearch{
public:
    int binSearch1(vector<T> &v,int lo, int hi, T target){
/*如果target在v中，者返回索引；如果v中没有target,那么target必然位于某个区间[a,b)，此算法将返回a，注意a可能是-1*/
        int mid;
        while(lo < hi){
            mid = (lo + hi) >> 1;
            (target < v[mid]) ? hi = mid : lo = mid+1;
        }
        return --lo;
    }
    int binSearch2(vector<T> &v,int lo, int hi, T target){
/*如果target在v中，者返回索引；如果v中没有target,那么target必然位于某个区间[a,b)，此算法将返回b，注意b可能是正无穷（v.size()）*/
        int mid;
        while(lo < hi){
            mid = (lo + hi) >> 1;
            (target <= v[mid]) ? hi = mid : lo = mid+1;
        }
        return lo;
    }

};