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
    double Power(double base, int exponent) {
        if(exponent == 0)
            return 1.0;
        int exp;
        if(exponent < 0){

            if(fabs(base - 0.0) < 0.0000001){
                return 0.0;
            }else{
                return 1.0 / normalPower(base, (unsigned int)(-exponent));
            }

        }else{

            return normalPower(base, (unsigned int )(exponent));

        }
    }

    double normalPower(double base, unsigned int exp){
        double impulNum = base;
        double res = 1;
        while(exp != 0){
            if( (exp & 1) == 1 ){
                res *= impulNum;
            }
            impulNum *= impulNum;
            exp = exp >> 1;
        }
        return res;
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


