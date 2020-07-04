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
    vector<int>res;
    vector<int> printMatrix(vector<vector<int> > matrix) {
        if(matrix.empty())
            return res;

        int rows = matrix.size();
        int cols = matrix[0].size();
        int left = 0, right = cols - 1, top = 0, bottom = rows - 1;
        while(left <= right && top <= bottom){
            for(int i = left; i <= right; i++){
                res.push_back(matrix[top][i]);
            }
            for(int i = top + 1; i <= bottom; i++){
                res.push_back(matrix[i][right]);
            }

            if(top != bottom){
                for(int i = right - 1; i >= left;i--){
                    res.push_back(matrix[bottom][i]);
                } 
            }

            if(left != right){
                for(int i = bottom - 1;i>top;i--){
                    res.push_back(matrix[i][left]);
                }
            }
            left ++, top++, right--, bottom--;
              
        }
        return res;
    }
};


int main(){
    vector<int>v1, v2, v3, v4;
    vector<vector<int> >v;
    vector<vector<int> >v_t;
    Solution test;
    for(int i = 0; i < 4; i++){
        v1.push_back(i + 1);
        v2.push_back(i + 5);
        v3.push_back(i + 9);
        v4.push_back(i + 13);
        
    }
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    cout<<"*******************************\n"<<endl;
    printEveryLeve(v);
    cout<<"*******************************\n"<<endl;
    test.printMatrix(v);
    
    printVector(test.res);
    


    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


