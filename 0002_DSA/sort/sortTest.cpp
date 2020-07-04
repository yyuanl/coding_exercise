#include<iostream>
#include"Sort.h"
#include<vector>
#include "./list/ListNode.h"
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"
using namespace std;
int main(){
    Visit<int> vst;
    
    Sort<int> srt;
    //=========test vector bobbleSort======
    cout<<"============test bobbleSort:============"<<endl;
    vector<int>vtr_bubb{5, 4, 3, 8, 9, 15,2};
    srt.visitvtr(vtr_bubb, vst);
    srt.bubbleSort(vtr_bubb,0, vtr_bubb.size());
    srt.visitvtr(vtr_bubb, vst);
    //=========test vector mergeSort======
    cout<<"==================test mergeSort:=============="<<endl;
    vector<int>vtr_merg{5, 4, 3, 8, 9, 15,2};
    srt.visitvtr(vtr_merg, vst);
    srt.mergeSort(vtr_merg, 0, vtr_merg.size());
    srt.visitvtr(vtr_merg, vst);
    //=========test list selectionSort======
    cout<<"==================test selectionSort:=============="<<endl;
    ListNode<int>first(2);
    ListNode<int>n1(1);
    ListNode<int>n2(5);
    ListNode<int>n3(10);
    ListNode<int>n4(4);
    ListNode<int>n5(9);
    first.succ = &n1; n1.pred = &first;
    n1.succ = &n2; n2.pred = &n1;
    n2.succ = &n3; n3.pred = &n2;
    n3.succ = &n4; n4.pred = &n3;
    n4.succ = &n5; n5.pred = &n4;
    cout<<"list before selectSort..."<<endl;
    srt.visitList(&first, vst);
    ListNodePosi(int)frt =  srt.selectSort(&first);
    cout<<"list after selecSort..."<<endl;
    srt.visitList(frt, vst);
    //=========test list insertionSort======
    cout<<"=========test insertionSort for list========"<<endl;
    ListNode<int>first_insert(2);
    ListNode<int>n1_insert(1);
    ListNode<int>n2_insert(5);
    ListNode<int>n3_insert(10);
    ListNode<int>n4_insert(4);
    ListNode<int>n5_insert(9);
    first_insert.succ = &n1_insert; n1_insert.pred = &first_insert;
    n1_insert.succ = &n2_insert; n2_insert.pred = &n1_insert;
    n2_insert.succ = &n3_insert; n3_insert.pred = &n2_insert;
    n3_insert.succ = &n4_insert; n4_insert.pred = &n3_insert;
    n4_insert.succ = &n5_insert; n5_insert.pred = &n4_insert;
    cout<<"list before selecSort..."<<endl;
    srt.visitList(&first_insert, vst);
    ListNodePosi(int)frt_insert =  srt.insertionSort(&first_insert);
    cout<<"list after selecSort..."<<endl;
    srt.visitList(frt_insert, vst);
    return 0;
}