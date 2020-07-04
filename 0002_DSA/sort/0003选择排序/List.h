#pragma once
#include <iostream>
#include <vector>
using namespace std;
struct ListNode{
    public:
        int data;
        ListNode* pred;
        ListNode* succ;
        ListNode(int ele = 0, ListNode*pr = NULL, ListNode*su = NULL):
            data(ele),pred(pr),succ(su){

        }
};

class List{
    public:
        List(int si = 0):size(si){cout <<"List(int si = 0):size(si)"<<endl;header.succ = &trailer;trailer.pred = &header;}
        List(vector<int>&);
        ~List();
        void print()const;
        void insert(vector<int>&);
        ListNode* max(ListNode* lo, ListNode* hi)const;
        void selectSort();
    private:
        int size;
        ListNode header;
        ListNode trailer;
        
};

