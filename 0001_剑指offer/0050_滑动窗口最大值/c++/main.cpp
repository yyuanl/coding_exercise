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
void printVector(vector<int>& v){
    cout<<"----------"<<endl;
    int s = v.size();
    cout<<"[";
    for(int i = 0;i < s;i++)
        cout<<v[i]<<" ";
    cout<<"]\n"<<endl;
}
void printDeque(deque<int>dq, const vector<int> &num){
    cout<<"deque back:";
    while(!dq.empty()){
        cout<<num[dq.back()]<<" ";
        dq.pop_back();
    }
    cout<<" front"<<endl;
}


class Solution {
public:
    vector<int>maxWin;
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        if(num.empty() || num.size()<size ||size<=0)
            return maxWin;
        deque<int>max_index;
        for(int i = 0;i<size;i++){
            while(!max_index.empty() && num[max_index.back()] < num[i])
                max_index.pop_back();
            max_index.push_back(i);
        }
       
        for(int i = size;i < num.size();i++){
            maxWin.push_back(num[max_index.front()]);   
            while(!max_index.empty() && num[max_index.back()] < num[i])
                max_index.pop_back();
            if(!max_index.empty() && (max_index.front() <= (int)(i - size))){
                 max_index.pop_front();
            }   
            max_index.push_back(i);
            
        }
        maxWin.push_back(num[max_index.front()]);
        return maxWin;
    }
};


int main(){

    int arr[] = {1, 8 ,6, 2,7, 3, 9,6,4};
    vector<int>v(arr, arr + 9);
    Solution s;
    unsigned int a = 3;
    s.maxInWindows(v, a);
    printVector(s.maxWin);
    
    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


