#include<iostream>
#include<vector>
#include<stack>
#include <algorithm> 
#include <queue>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cmath>
#include <set>
#include <climits>

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

void printVector(vector<int>& v){
    cout<<"----------"<<endl;
    int s = v.size();
    cout<<"[";
    for(int i = 0;i < s;i++)
        cout<<v[i]<<" ";
    cout<<"]\n"<<endl;
}


class Solution {
public:
    int Sum_Solution(int n) {
        //递归实现循环
        int res=n;
        n && (res+=Sum_Solution(n-1));
        return res;
    }
};



int main(){
    int arr[] = {1,2,3,4,5};
    const vector<int>v(arr, arr + 5);
    Solution s;
    s.multiply(v);
    
    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


