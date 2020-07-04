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

void printVector(vector<char>& v){
    cout<<"----------"<<endl;
    int s = v.size();
    cout<<"[";
    for(int i = 0;i < s;i++)
        cout<<v[i]<<" ";
    cout<<"]\n"<<endl;
}


class Solution {
public:
    vector<int>res;
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        if(array.size()<2)
            return res;
        int len=array.size();
        int small = 0,big = len-1;
        int currSum = 0;
        for(;small < big;){
            currSum = array[small] + array[big];
            if(currSum == sum){
                res.push_back(array[small]);
                res.push_back(array[big]);
                return res;
            }else if(currSum < sum){
                ++small;
            }else{
                --big;
            }
        }
        return res;
        
    }
};

int main(){
    string s("cdefgab");
    Solution test;
    test.LeftRotateString(s,2);
    
    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


