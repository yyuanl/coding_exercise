
#include <iostream>
#include <vector>
#include "List.h"
using namespace std;

List::List(vector<int>&vec){
    cout<<"List::List(vector<int>&vec)"<<endl;
    size = vec.size();
    vector<int>::iterator it = vec.begin();
    ListNode*p = &header;
    while(it!=vec.end()){
        p->succ = new ListNode(*it);
        cout<<"new data is "<<p->succ->data<<endl;
        p->succ->pred = p;
        p->succ->succ = &trailer;
        trailer.pred = p->succ;
        p = p->succ;
        it++;
    }
}
List::~List(){
    ListNode*p = NULL;
    if(size){
        p = header.succ;
    }else{return ;}

    while(size){
        ListNode* temp = p;
        p = p->succ;
        delete temp;
        size--;
    }
    header.succ = &trailer;
    trailer.pred = &header;
}
void List::print()const{
    cout<<"--------------------"<<endl;
    ListNode*p = header.succ;

    while(p!=&trailer){
        cout<<"pred is "<<p->pred->data<<", data is "<<p->data<<", succ is "<<p->succ->data<<endl;
        p = p->succ;
    }
}
ListNode* List::max(ListNode* begi, ListNode* las)const{  // [,)
   
    ListNode *p = begi;
    ListNode *maxNode = p;
    
    while(p != las){
       
        if(maxNode->data < p->data){
            //cout<<"maxNode->data is "<<maxNode->data<<" p->data is: "<<p->data<<endl;
            maxNode = p;
        }
       
        p = p->succ;
    }
   
    return maxNode;

}
void List::selectSort(){
    int temp;

    ListNode* right = &trailer;
    ListNode* sortedHeader = &trailer;
    ListNode* maxNode = NULL;

    while(right!=header.succ){
        
        maxNode = max(header.succ, right);
        temp = maxNode->data;
        maxNode->data = sortedHeader->pred->data;
      
        sortedHeader->pred->data = temp;
        sortedHeader = sortedHeader->pred;
        right = right->pred;

    }

}