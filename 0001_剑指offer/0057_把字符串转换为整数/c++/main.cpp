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
    int StrToInt(string str) {
        if(str.empty())return 0;
        string::iterator it = str.begin(); 
        bool is_pos = true;
        while (*it == ' ')
        {
            it++;
        }
        if(*it == '+'){
            it++;
        }
        if(*it == '-'){
            it++;
            is_pos = false;
        }
        long long int ret = 0;
        for(;it != str.end();it++){
            if(*it < '0' || *it > '9')
                return 0;
            ret = ret*10 + *it - '0';
            if( (is_pos && ret > INT_MAX) || (!is_pos && ret > (unsigned int)INT_MIN + 1))
                break;
        }
        if(it != str.end()){
            return 0;
        }else{
            if(!is_pos){
                ret = -ret;
            }
            if(ret > INT_MAX){
                return INT_MAX;
            }
            if(ret < INT_MIN){
                return INT_MIN; 
            }
            return (int)ret;
        }
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


