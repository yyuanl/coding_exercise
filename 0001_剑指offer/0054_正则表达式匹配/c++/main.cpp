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

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};


class Solution {
public:
    bool isMatch(char *s, char *p, int i, int j){
        return s[i] == p[j]  || p[j] == '.';
    }
    bool match(char* str, char* pattern)
    {
        int s_len = strlen(str);
        int p_len = strlen(pattern);
       
        vector<vector<bool>>dp(s_len + 1, vector<bool>(p_len + 1, false));
        dp[0][0] = true;
        for(int j = 2;j < p_len + 1;j++){
            dp[0][j] = (pattern[j-1]=='*') && dp[0][j-2];
        }
        for(int i = 0; i < s_len; i++)
            for(int j = 0; j < p_len; j++){
                if(pattern[j] == '*'){
                    dp[i+1][j+1] = dp[i+1][j-1] || (dp[i][j+1] &&  isMatch(str, pattern, i, j-1));
                }else{
                    dp[i+1][j+1] = isMatch(str, pattern, i, j) && dp[i][j];
                }
            }

        return dp[s_len][p_len];

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


