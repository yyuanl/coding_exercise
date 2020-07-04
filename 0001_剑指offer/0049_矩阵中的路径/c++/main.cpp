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
    bool dfs(int i, int j, vector<vector<bool> >&visted,char *matrix, int rows, int cols, char *str, int pos){
        if(str[pos] == '\0')return true;
        if(i<0|| i>=rows || j<0 || j>=cols || visted[i][j]==true)
            return false;
        
        if(matrix[i*cols+j] != str[pos]) return false;
        bool flag;
        visted[i][j] = true;
        flag = dfs(i+1,j,visted, matrix,rows, cols,str, pos+1)
            || dfs(i-1,j,visted, matrix,rows, cols,str, pos+1)
            || dfs(i,j+1,visted, matrix,rows, cols,str, pos+1)
            || dfs(i,j-1,visted, matrix,rows, cols,str, pos+1);
        visted[i][j] = false;
        return flag;

    }
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        if(matrix == NULL)return false;
        vector<vector<bool> >visted(rows,vector<bool>(cols, false));
        for(int i = 0;i < rows;i++)
            for(int j = 0;j < cols;j++){
                if(dfs(i,j,visted,matrix,rows, cols, str, 0))return true;
            }

        return false;
    
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


