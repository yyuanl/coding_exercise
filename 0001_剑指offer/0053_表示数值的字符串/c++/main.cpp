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
    void scanDigistStr(char *&s){ // 扫描数字字符串
        while(isdigit(*s)) s++;
    }
    bool scanExpStr(char *&s){ // 扫描指数部分 e1212
        if(*s != 'e' && *s != 'E') return false;
        s++;  //过e
        if(*s == '\0')return false;
        if(*s == '+' || *s == '-')s++;//过符号
        scanDigistStr(s);
        if(*s != '\0')return false;
        return true;
    }
    bool isNumeric(char* string)
    {
        if(string == nullptr)   return false;
        if( *string == '+' || *string == '-')
            string++;
        if(*string == '\0')
            return false;
        scanDigistStr(string);
        if(*string != '\0'){
            if(*string == '.'){// 是小数
                
                if(*(++string) == '\0')return false;
                scanDigistStr(string);
                if(*string == '\0')return true;
                return scanExpStr(string);
            }else if(*string == 'e' || *string == 'E'){
                return scanExpStr(string);
            }else{
                return false;
            }
        }
        return true;
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


