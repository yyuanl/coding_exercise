#pragma once
#include <iostream>
#include <vector>
#define ListNodePosi(T) ListNode<T>* //列表节点位置
using namespace std;
template <typename T>
struct ListNode{
   T data;
   ListNodePosi(T) pred;
   ListNodePosi(T) succ;
   ListNode(int ele = 0,ListNodePosi(T) pr = NULL,ListNodePosi(T) su = NULL):
      data(ele),pred(pr),succ(su){}
};
/*
template <typename T>
class List{
    public:
        List(int si = 0):size(si){cout <<"List(int si = 0):size(si)"<<endl;header.succ = &trailer;trailer.pred = &header;}
        List(vector<int>&);
        ~List();
        void insert(vector<int>&);
        //T remove ( ListNodePosi(T) p );
        ListNodePosi(T) insertAsLast ( T const& e );
        //ListNode* selectMax(ListNode* lo, ListNode* hi)const;
        //void selectSort();
    private:
        int size;
        ListNode<T> header;
        ListNode<T> trailer;
        
};*/

