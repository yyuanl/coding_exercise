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


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
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
void printEveryLeve(vector<vector<int> > &res){
    cout<<"----------"<<endl;
    int s = res.size();
    cout<<"-*********---"<<s<<endl;
    for(int i = 0; i < s; i++){
        cout<<"-*********---"<<endl;
        cout<<i<<": ";
        printVector(res[i]);
    }
}

class Solution {
public:
    vector<string>res;
    void f(string str, vector<string>&set_string){
        //vector<string>rt;
        vector<string>temp;
        if(str.empty())
            return ;
        for(int i = 0;i<str.size();i++){
            temp.clear();
            f(str.substr(0, i) + str.substr(i+1,str.size()-i-1), temp);

            if(temp.empty()){
                set_string.push_back(str);
            }else{

                for(int j = 0;j<temp.size();j++){
                    set_string.push_back(str[i] + temp[j]);
                    //cout<<"push back is "<<str[i] + temp[j]<<endl;
                }

            }
            
        }
       
    }
    


    vector<string> Permutation(string str) {
       
       f(str,res);
       set<string>s(res.begin(), res.end());
       res.assign(s.begin(), s.end());
       return res;
    }
        

};
int main(){
    string s = "123";
    vector<string>test;
    Solution so_t;
    test = so_t.Permutation(s);
    int size = test.size();
    
    for(int i = 0; i < size;i++){
        cout<<test[i]<<endl;
    }
    cout<<"size is "<<size<<",7! is "<<7*6*5*4*3*2<<endl;



    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


