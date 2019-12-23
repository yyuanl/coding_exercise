#include<iostream>
using namespace std;
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
ListNode* getKTHFromTail(ListNode*pHead, int k){
    if(pHead == NULL)
        return NULL;
    ListNode* po_left = pHead;
    ListNode* po_right = pHead;
    for(int i = 0; i < k - 1;i++)
        po_right = po_right->next;
    
    cout<<"right is "<<po_right->val<<", left is "<<po_left->val<<endl;
    
    while(po_right->next != po_left){
        
        po_left = po_left -> next;
        po_right = po_right -> next;
    }
    
    return po_left;
}
ListNode* EntryNodeOfLoop(ListNode* pHead){
    if(pHead == NULL)
        return NULL;

    // 定位到环内结点
    ListNode* fast_po = pHead;
    ListNode* slow_po = pHead;
    while(fast_po != NULL && fast_po->next != NULL ){ 
        slow_po = slow_po->next;
        fast_po = fast_po->next->next;
        if(fast_po == slow_po)
            break;
        
    }

    if(fast_po == slow_po)
        cout<<"reach same node ,val is "<<fast_po->val<<endl;
    // 获取环的长度
    int len_loop = 1;
    slow_po = slow_po -> next;
    while(fast_po != slow_po){
        slow_po = slow_po -> next;
        len_loop++;
    }
    cout<<"the length of loop is "<<len_loop<<endl;
    // 定位入口结点
    ListNode* entry_po = getKTHFromTail(pHead, len_loop);
    


    return entry_po;

}
int main(){
    
    ListNode first(2);
    ListNode second(3);
    ListNode third(65);
    ListNode forth(13);
    ListNode fifth(5);
    ListNode sixth(8);
    ListNode seventh(9);
    first.next = &second;
    second.next = &third;
    third.next = &forth;
    forth.next = &fifth;
    fifth.next = &sixth;
    sixth.next = &seventh;
    seventh.next = &forth;





    
    int count = 0;
    ListNode* po = &first;
    while(count < 10){
        cout<<"node valude is "<< po->val<<endl;
        po = po->next;
        count++;

    }

    ListNode* entry_po =  EntryNodeOfLoop(&first);
    cout<<"the entry node of loop is "<<entry_po->val<<endl;

    return 0;
}