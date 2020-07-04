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
    string LeftRotateString(string str, int n) {
        if(str.empty())
            return str;
        int len = str.size();
        vector<char>v;
        n = n % (str.size());
        for(int i = 0;i < n;i++){
            v.push_back(str[i]);
        }
        printVector(v);    
        
        for(int i = n, ix = 0;i < len;i++,ix++){
            cout<<"str["<<ix<<"] is "<<str[ix]<<", and str["<<i<<"]is "<<str[i]<<endl;
            str[ix] = str[i];
            
        }  
        cout<<"now string is "<<str<<endl;
        cout<<"fen ge xian ...................."<<endl;
        for(int i = len-n, j = 0; i < len;i++, j++){
            cout<<"str["<<i<<"] is "<<str[i]<<", and str["<<j<<"]is "<<str[j]<<endl;
            str[i] = v[j];
        }    
        cout<<"string is "<<str<<endl;  
        return str;
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


