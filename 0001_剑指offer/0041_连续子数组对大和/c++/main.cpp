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
    int FindGreatestSumOfSubArray(vector<int> array) {
        if(array.empty())
            return 0;
        int maxNum = 0;
        int size = array.size();
        int subSum = 0;
        for(int i = 0; i < size; i++){
            if(maxNum == 0)
                maxNum = array[i];
            
            if(subSum + array[i] < array[i]){
                subSum = array[i];
            }else{
                subSum += array[i];
            }
            
            if(maxNum < subSum)
                maxNum = subSum;
        }
        return maxNum;
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


