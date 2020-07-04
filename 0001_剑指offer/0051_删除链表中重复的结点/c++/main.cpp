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

class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(pHead == nullptr)
            return nullptr;

        ListNode *curr = pHead;
        ListNode hder(-1);hder.next = pHead;
        ListNode *prev = &hder;
        ListNode *diffNode = nullptr;
        while(curr != nullptr){

            if(curr->next != nullptr && curr->val == curr->next->val){
                diffNode = curr->next->next;
                while(diffNode != nullptr){
                    if(diffNode->val != curr->val)
                        break;
                    diffNode = diffNode->next;
                }
                prev->next = diffNode;
                curr = diffNode;
                continue;
            }
            curr = curr->next;
            prev = prev->next;

        }
        return hder.next;
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


