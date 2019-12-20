#include<iostream>
using namespace std;
struct ListNode{
    public:
        int val;
        struct ListNode *next;
};
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k){
     if(pListHead  == NULL)
        return NULL;
    
    ListNode *right = pListHead;
    unsigned int ix = 0;
    for(; ix < k - 1; ix ++){
        if(right->next != NULL){
            cout<<"move "<<ix+1<<endl;
            right = right->next;

        }else{
            break;
        }
            
    }
    if(right->next == NULL)
        cout << "+++++++++";
    if((right -> next == NULL) && ( ix < k - 1)) {
        cout<<"000000";
        return NULL;
    }
        
        
    ListNode *left = pListHead;
    while(right->next != NULL){
        right = right->next;
        left = left->next;
    }
    return left;
}
int main(){
    ListNode LianBiao[2];
    LianBiao[0].val = 1;
    LianBiao[0].next = &LianBiao[1];
    LianBiao[1].val = 2;
    LianBiao[1].next = NULL;

    // LianBiao[2].val = 3; 
    // LianBiao[2].next = &LianBiao[3];
    // LianBiao[3].val = 4;
    // LianBiao[3].next = NULL;
    ListNode *p = FindKthToTail(LianBiao, 3);
    if(p == NULL)
        cout << ".....";
    
    cout<<p->val;

    return 0;
}