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

/*
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

*/



class Solution {
public:
    int cutRope(int number) {
       if(number == 2)return 1;
       if(number == 3)return 2;
       if(number == 4)return 4;
        int quotient = number / 3;
       if(number % 3 == 1 )return(pow(3, quotient - 1)*4);
       if(number % 3 == 2 )return(pow(3, quotient)*2);
       return pow(3, quotient);
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


