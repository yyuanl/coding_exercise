#include<iostream>
#include<string>
using namespace std;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

void print_List(ListNode *p_head_node){
    cout<<"\n"<<endl;
    ListNode* p = p_head_node;
    string str_next;
    while(p != NULL){
        if(p->next == NULL){
            str_next = "NULL";
        }else{
            str_next = to_string(p->next->val);
        }
        cout<<"node value is "<<p->val<<", next node value is "<<str_next<<endl;
        p = p->next;
    }
    cout<<"\n";

}
int get_list_length(ListNode* pHead){
    int count_num = 0;
    ListNode* po = pHead;
    while(po != NULL){
        count_num ++;
        po = po->next;
        
    }
    return count_num;
}

ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {

    if(pHead1 == NULL || pHead2 == NULL)
        return NULL;
    
    int len_first = get_list_length(pHead1);
    int len_second = get_list_length(pHead2);
    ListNode* po_longer = (len_first > len_second) ? pHead1 : pHead2;
    ListNode* po_short = (len_first < len_second) ? pHead1 : pHead2;
    int i = (len_first > len_second) ? len_first - len_second : len_second - len_first;
    while(i > 0){
        po_longer = po_longer -> next;
        i -- ;
    }
    while(po_longer != po_short && po_longer != NULL && po_short != NULL){
        po_longer = po_longer -> next;
        po_short = po_short -> next;
    }
    return po_longer;
}
int main(){
    ListNode a_first(2);
    ListNode a_second(5);
    ListNode a_third(6);
    ListNode a_forth(8);
    ListNode a_fifth(45);
    a_first.next = &a_second;
    a_second.next = &a_third;
    a_third.next = &a_forth;
    a_forth.next = &a_fifth;
    a_fifth.next = NULL;

    ListNode b_first(3);
    b_first.next = &a_forth;

    print_List(&a_first);
    print_List(&b_first);

    
    print_List(FindFirstCommonNode(&a_first, &b_first));

    return 0;
}