
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
ListNode* List::search(ListNode*sortedLeftNode, ListNode* sortedRightNode,  ListNode* node)const{
    //[sortedLeftNode, sortedRightNode) 返回合适位置
    ListNode* moveP = sortedRightNode->pred;
    while(moveP != &header){
        if((moveP->data < node->data)||(moveP->data == node->data)){
            break;
        }
        moveP = moveP->pred;
    }
    //cout<<"\nsearch result is "<<moveP->data<<endl;
    return moveP;
}

void List::internalMove(ListNode*postion, ListNode*node){
    //接触node节点
    node->pred->succ = node->succ;
    node->succ->pred = node->pred;

    postion->succ->pred = node;
    node->succ = postion->succ;
    postion->succ = node;
    node->pred = postion;

}

void List::insertSort(){
    ListNode* unsortedFirstNode = header.succ->succ;
    ListNode* sortedLeftNode  = header.succ;
    // ListNode* testp = NULL;
    while(unsortedFirstNode != &trailer){
        // testp=search(sortedLeftNode,unsortedFirstNode, unsortedFirstNode);
        // cout<<"search result is "<<testp->data<<endl;
        internalMove(search(sortedLeftNode,unsortedFirstNode, unsortedFirstNode), unsortedFirstNode);
        

        unsortedFirstNode = unsortedFirstNode->succ;
    }


}

//插入排序平均复杂度o(n^2)  主要花费在search。属于 input sensetive类型算法