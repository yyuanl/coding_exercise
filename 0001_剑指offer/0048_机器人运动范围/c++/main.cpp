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


/*
class Solution {
public:
    
    bool bitSumIsComply(int plx, int ply, int threshold){
        int sum = 0;
        while(plx){
            sum += plx % 10;
            plx = plx / 10;
        }
        while(ply){
            sum += ply %10;
            ply /= 10;
        }
        if(sum < threshold){
            return true;
        }else{
            return false;
        }
    }


    int f(int x, int y, vector<vector<bool> >&visited, int rows, int cols, int thr){ // 机器人 从(x,y)出发能到达多少个格子
        cout<<"execute here "<<visited[x][y]<<endl;
        if(x<0||y<0||x>=rows||y>=cols||(!bitSumIsComply(x, y, thr))||(visited[x][y]==true))return 0;
        cout<<"execute here "<<bitSumIsComply(x,y,thr)<<endl;
        visited[x][y]=true;
        return 1 + f(x-1,y,visited,rows,cols,thr)
                 + f(x+1,y,visited,rows,cols,thr)
                 + f(x,y-1,visited,rows,cols,thr)
                 + f(x,y+1,visited,rows,cols,thr);

    }
    int movingCount(int threshold, int rows, int cols)
    {
      
        
        vector<vector<bool> >visited(rows, vector<bool>(cols));
        return f(0, 0,visited, rows,cols,threshold);
    }
};*/


class Solution {
public:

int digit_sum(int i){
    int sum = 0;
    while(i>0){
        sum+=i%10;
        i /= 10;
    }
    //cout<<"end digs"<<endl;
    return sum;
    
}
int f(int i, int j, int m, int n,int k,vector<vector<bool> >&visited){
    //cout<<"bit sum is"<<digit_sum(i)<<endl;
    if(i<0||j<0||
        i>=m||j>=n
        ||(digit_sum(i)+digit_sum(j))>k
        ||visited[i][j]==true){return 0;}

    visited[i][j]=true;
    return 1+f(i+1,j,m,n,k,visited)
    + f(i-1,j,m,n,k,visited)
    + f(i, j+1,m,n,k,visited)
    + f(i, j-1,m,n,k,visited);
}
int movingCount(int k,int m, int n){
    vector<vector<bool> >visited(m,vector<bool>(n));
    int ans = f(0,0,m,n,k,visited);
    return ans;
}
};




    







int main(){

    Solution t;
    
    cout<<"res is "<<t.movingCount(5,10,10)<<endl;


    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


