#include<iostream>
using namespace std;
struct ListNode{
    public:
        int val;
        struct ListNode *next; 
};
ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
    if(pHead1 == NULL){
        return pHead2;
    }else if(pHead2 == NULL){
        return pHead1;
    }
    
    ListNode* p1 = pHead1;
    ListNode* p2 = pHead2;

    ListNode* p_Merge = NULL;  // 合成链表
    // 确定头结点
    if(p1->val < p2 -> val){
        p_Merge = p1;
        p1 = p1->next;
    }else{
        p_Merge = p2;
        p2 = p2->next;
    }

    ListNode* p_temp = p_Merge; // 合成链表p_Merge的指针
    while((p1 != NULL) && (p2 != NULL)){

        if((p1->val) < (p2->val)){         
                p_temp->next = p1;  // 合成链表链接到p1
                p1 = p1 ->next;   // p1后移， 准备下一次比较            
                p_temp = p_temp->next;  // 合成链表指针，指向未结点
            
        }else{
                p_temp->next = p2;               
                p2 = p2 -> next;
                p_temp = p_temp -> next;      
        }
        
    }

    // 比较完成，把剩余链接上
    if(p1 == NULL){
        p_temp->next = p2;
    }else{
        p_temp->next = p1;
    }
    return p_Merge;
}



void print_list(ListNode* pHead){
    ListNode* p_temp = pHead;
    while(p_temp != NULL){
        cout<<p_temp -> val<<" "<<endl;
        p_temp = p_temp -> next;
    }
}
int main(){
    
    ListNode lianbiao_1[4];
    lianbiao_1[0].val = 1;
    lianbiao_1[0].next = &lianbiao_1[1];
    lianbiao_1[1].val = 5;
    lianbiao_1[1].next = &lianbiao_1[2];
    lianbiao_1[2].val = 13;
    lianbiao_1[2].next = &lianbiao_1[3];
    lianbiao_1[3].val = 19;
    lianbiao_1[3].next = NULL;

    ListNode lianbiao_2[4];
    lianbiao_2[0].val = 3;
    lianbiao_2[0].next = &lianbiao_2[1];
    lianbiao_2[1].val = 4;
    lianbiao_2[1].next = &lianbiao_2[2];
    lianbiao_2[2].val = 9;
    lianbiao_2[2].next = &lianbiao_2[3];
    lianbiao_2[3].val = 50;
    lianbiao_2[3].next = NULL;

    ListNode* list_temp = Merge(lianbiao_1, lianbiao_2);
    print_list(list_temp);
    return 0;
}