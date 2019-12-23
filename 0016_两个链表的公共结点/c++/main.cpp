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

ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
    if(pHead1 == NULL || pHead2 == NULL)
        return NULL;
    ListNode* p1 = pHead1;
    ListNode* p2 = pHead2;
    while(p1 != p2 && p1 != NULL && p2 != NULL){
        p1 = (p1->next == NULL) ? pHead2 : p1->next;
        p2 = (p2->next == NULL) ? pHead1 : p2->next;
    }

    return p1;
        
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