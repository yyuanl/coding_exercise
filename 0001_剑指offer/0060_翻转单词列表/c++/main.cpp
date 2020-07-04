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
    string res;
    string ReverseSentence(string str) {

        if(str.empty())return str;
        auto len = str.size();
        stack<string>st;
        string s;
        for(auto c:str){
            if(c != ' '){
                s = s + c;
                continue;
            }
            st.push(s);
            s.clear();
        }
        st.push(s);

        while(!st.empty()){
            if(st.size() == 1){
                res = res + st.top() ;
            }else{
                res = res + st.top()+" ";
            }
            
            st.pop();
        }

        return res;
        
    }
};



int main(){
    string s("student a am I");
    Solution test;
    test.ReverseSentence(s);
    
    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


