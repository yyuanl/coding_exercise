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


//排序的链表
class Solution
{
public:
    Solution(){
        str = "";
        for(int i = 0;i < 256;i++)
            countChar[i] = 0;
    }
  //Insert one char from stringstream
    void Insert(char ch)
    {
         str += ch;
         countChar[(int)ch]++;
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        int len = str.size();
        for(int i = 0;i < len;i++){
            if(countChar[(int)str[i]]==1)
                return str[i];
        }
        return '#';
    }
private:
    string str;
    int countChar[256];
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


