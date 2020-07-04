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
    
    vector<int> multiply(const vector<int>& A) {
        int size = A.size();
        vector<int>res(size);
        vector<int>preMult(size); //前i项积
        vector<int>backMult(size);  //后i项积
        preMult[0] = 1; backMult[0] = 1;

        for(int i = 1; i < size;i++){
            preMult[i] = preMult[i-1]*A[i-1];
        }
        printVector(preMult);
        for(int i = 1;i < size;i++){
            backMult[i] = backMult[i-1]*A[size-i];
        }
        printVector(backMult);
        res[0] =  backMult[size-1];
        res[size-1] = preMult[size-1];
        for(int i = 1; i < size;i++){
            res[i] = preMult[i]*backMult[size-i-1];
        }
        printVector(res);
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


