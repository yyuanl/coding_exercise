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
    int rectCover(int number) {
        // f(n) = f(n - 1) + f(n - 2);
        if(number  <= 0)
            return 0;
        if(number == 1)
            return 1;
        if(number == 2)
            return 2;
        
        int f1 = 1, f2 = 2;
        for(int i = 3; i < number + 1;i++){
            f2 = f1 + f2;
            f1 = f2 - f1;
        }
        return f2;

    }
};


int main(){

    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


