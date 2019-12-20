#include<iostream>
using namespace std;
struct ListNode{
    public:
        int val;
        struct ListNode *next;
};

ListNode* ReverseList(ListNode* pHead){
    ListNode *left = NULL;
    ListNode *mid = pHead;
    ListNode *right = NULL;
    while(mid != NULL){
        right = mid->next;
        mid->next = left;
        cout<<"reverse..."<<endl;
        left = mid;
        mid = right;
       
    }
    return left;
    
}
int main(){
    ListNode LianBiao[4];

    LianBiao[0].val = 1;
    LianBiao[0].next = &LianBiao[1];

    LianBiao[1].val = 2;
    LianBiao[1].next = &LianBiao[2];

    LianBiao[2].val = 3; 
    LianBiao[2].next = &LianBiao[3];

    LianBiao[3].val = 4;
    LianBiao[3].next = NULL;
    ListNode *p_ListNode = ReverseList(LianBiao);
    while(p_ListNode != NULL){
        cout<<p_ListNode->val<<"\n"<<endl;
        p_ListNode = p_ListNode -> next;
    }


    return 0;
}