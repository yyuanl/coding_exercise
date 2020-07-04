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
    bool IsContinuous( vector<int> numbers ) {
        if(numbers.empty())
            return false;
        
        sort(numbers.begin(), numbers.end());
        int num0 = 0;
        int notSeq = 0;
        for(int i = 0; i < numbers.size();i++){
            if(numbers[i]==0)
                num0++;

            if(i > 0 && numbers[i-1] != 0){
                
                if(numbers[i]==numbers[i-1]){
                    return false;
                }else{
                    notSeq += (numbers[i]-numbers[i-1] -1);
                }
            }
        }
        
        return (num0 >= notSeq)?true:false;
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


