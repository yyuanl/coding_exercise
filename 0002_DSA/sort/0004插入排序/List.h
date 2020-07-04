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
        void internalMove(ListNode*postion, ListNode*node);
        ListNode* max(ListNode* lo, ListNode* hi)const;
        void selectSort(); //选择排序
        void insertSort(); // 插入排序
        ListNode* search(ListNode*lo, ListNode* hi, ListNode* node)const; // 查找 ，返回[,)不大于查找的最大元素
    private:
        int size;
        ListNode header;
        ListNode trailer;
        
};

