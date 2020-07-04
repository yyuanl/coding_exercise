#pragma once
#include <vector>
#include <algorithm>
#include "./list/ListNode.h"
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"
using namespace std;
template <typename T>
class Sort{
public:
/*冒泡排序*/
    void bubbleSort(vector<T> &v, int lo, int hi);
/*选择排序,无须索引访问。例子针对链表*/
    ListNodePosi(T) selectSort(ListNodePosi(T) first);
/*归并排序*/
    void mergeSort(vector<T> &v, int lo, int hi);
/*插入排序*/
    ListNodePosi(T) insertionSort(ListNodePosi(T)first);
/*堆排序*/
    void heapSort(vector<T> &v, int lo, int hi);
/*快速排序*/
    void quickSort(vector<T> &v, int lo, int hi);
/*希尔排序*/
    void shellSort(vector<T> &v, int lo, int hi);

/*访问vector每一个元素，方便排序前后比较*/    // 模板写在类外出错，还不会改
    template <typename VST>
    void visitvtr(vector<T>&v,VST &visit){
        int len = v.size();
        cout<<"start to visiting vector element..."<<endl;
        for(int i = 0; i < len;i++){
            visit(v[i]);
        }
        cout<<"\nend to visiting..."<<endl;
    }
/*访问list每一个元素，方便排序前后比较*/       
    template <typename VST>
    void visitList(ListNodePosi(T) lis,VST &visit){
        cout<<"start to visiting List element..."<<endl;
        for(ListNodePosi(T) i = lis; i != NULL;i = i ->succ){
            visit(i->data);
        }
        cout<<"\nend to visiting..."<<endl;
    }
private:
/*归并排序，左右两个部分有序合并例程*/
    void merge(vector<T>&v, int lo, int mid, int hi);
/*选择排序，从前边无序部分选择最大节点例程*/
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int nums);
/*删除双向链表某个节点例程,仅仅是把节点摘除，构造好前驱和后继*/
    ListNodePosi(T) removeListNode(ListNodePosi(T) node);
/*双向链表例程，在node1前插入node2*/
    void insertB(ListNodePosi(T) node1, ListNodePosi(T) node2);
/*双向链表例程，p的前n个节点，不包括p，选择不大于目标的最后者 */
    ListNodePosi(T) search(T target, int nums, ListNodePosi(T) node);
/*双向链表例程， 在node1后插入node2*/
    void insertA(ListNodePosi(T) node1, ListNodePosi(T) node2);
    
};


/*冒泡排序*/
template <typename T>
void Sort<T>::bubbleSort(vector<T> &v, int lo, int hi){
    int lastswap = --hi; //需要扫描的区间[lo,lastswap);初始化
    while(lo < lastswap){
        hi = lastswap;  //得到上次扫描最后的位置
        lastswap = lo;  //初始化，如果本次扫描没有交换，则向量有序，循环退出
        for(int i = lo;i < hi; i ++ ){
            if(v[i] > v[i+1]){
                lastswap = i; // 动态记录最后一次扫描位置
                swap(v[i], v[i+1]);
            }
        }
    }
}
/*选择排序,无须索引访问。例子针对链表*/
template <typename T>
ListNodePosi(T) Sort<T>::selectSort(ListNodePosi(T) first){ // 排序整个链表
/*维护无序和有序部分，从无序部分选择最大的插入有序部分头部。[first, sortedFirst) [sortedFirst, tailer)*/
/*加上头尾便于插入、删除、返回等操作*/
    int len = 0;
    ListNodePosi(T)res;
    ListNodePosi(T) sortedFirst; // 有序部分得首元素
    ListNode<T> header(0, NULL, first);
    first->pred = &header;
    for(ListNodePosi(T) p = first;p != NULL;p = p->succ){
        ++len; sortedFirst = p; // 先遍历到最后一个元素
    }
    ListNode<T> tailer(0, sortedFirst, NULL); 
    sortedFirst->succ = &tailer;
    sortedFirst = sortedFirst->succ;
    for(int n = len;n > 1;--n){
        /*
        p = selectMax(first, n);
        removeListNode(p);
        insertA(end,p)
        */
        insertB(sortedFirst, removeListNode(selectMax(first, n)));
        sortedFirst = sortedFirst->pred;
        // Visit<int> vst;
        // visitList(header.succ, vst);
    }
    res = header.succ;
    res->pred = NULL;
    tailer.pred->succ = NULL;
    return res;       
}
/*插入排序*/
template <typename T>
ListNodePosi(T) Sort<T>::insertionSort(ListNodePosi(T)first){
    /*封装头尾：便于操作*/
    ListNode<T> header(0, NULL, first);
    first->pred = &header;
    ListNode<T> tailer;
    ListNodePosi(T) unsortedHead = first; // 维护无序部分首部
    ListNodePosi(T) temp;
    ListNodePosi(T) res;
    int len = 0;
    for(ListNodePosi(T) p = first;p != NULL; p = p->succ){
        tailer.pred = p;
        len++;
    } 
    tailer.pred->succ = &tailer;
    for(int sortedLen = 0; sortedLen < len;sortedLen++){
        temp = unsortedHead->succ;
        insertA(search(unsortedHead->data, sortedLen, unsortedHead),removeListNode(unsortedHead));
        unsortedHead = temp;
        // Visit<int> vst;
        // visitList(header.succ, vst);
    }
    res = header.succ;
    res->pred = NULL;
    tailer.pred->succ = NULL;
    return res;
}
/*双向链表例程，p的前n个节点，不包括p，选择不大于目标的最后者 */
template <typename T>
ListNodePosi(T) Sort<T>::search(T target, int nums, ListNodePosi(T) node){
    ListNodePosi(T)res = node->pred;
    while(res->data > target){
        if(nums == 0) // 返回头部哨兵
            break;
        res = res->pred;
        nums--;
    }
    return res;
}
/*双向链表例程， 在node1后插入node2*/
template <typename T>
void Sort<T>::insertA(ListNodePosi(T) node1, ListNodePosi(T) node2){
    node2->succ = node1->succ; node1->succ->pred = node2; node1->succ = node2; node2->pred = node1;
}


/*归并排序*/
template <typename T>
void Sort<T>::mergeSort(vector<T> &v, int lo, int hi){
    if(hi - lo < 2)return; // 单元素自然有序
    int mid = (lo + hi) >> 1;  // 切分
    mergeSort(v, lo, mid); // 使前半部分有序
    mergeSort(v, mid, hi); // 使后半部分有序
    merge(v, lo, mid, hi); // 合并前后两个有序的部分
}



/*堆排序*/
template <typename T>
void Sort<T>::heapSort(vector<T> &v, int lo, int hi){}
/*快速排序*/
template <typename T>
void Sort<T>::quickSort(vector<T> &v, int lo, int hi){}
/*希尔排序*/
template <typename T>
void Sort<T>::shellSort(vector<T> &v, int lo, int hi){}

/*访问每一个元素，方便排序前后比较*/    
// template <typename T,typename VST>
// void Sort<T>::visitvtr(vector<T>&v,VST &visit){
//     int len = v.size();
//     cout<<"start to visiting vector element..."<<endl;
//     for(int i = 0; i < len;i++){
//         visit(v[i]);
//     }
//     cout<<"\nend to visiting..."<<endl;
// }

// template <typename T,typename VST>
// void Sort<T>::visitList(ListNodePosi(T) lis,VST &visit){
//     cout<<"start to visiting List element..."<<endl;
//     for(ListNodePosi(T) i = lis; i != NULL;i = i ->succ){
//         visit(i->data);
//     }
//     cout<<"\nend to visiting..."<<endl;
// }
template <typename T>
void Sort<T>::merge(vector<T>&v, int lo, int mid, int hi){
    int lenLeft = mid - lo;
    vector<T>B;
    B.assign(v.begin()+lo, v.begin()+lo+mid);
    for(int idx_a = lo,idx_b = 0, idx_c = mid; idx_b < lenLeft;){ // 这里不能判断idx_b是否越界
        v[idx_a++] = (idx_c >= hi || B[idx_b] < v[idx_c]) ? B[idx_b++] : v[idx_c++]; // 这里判断idx_b是否越界
    }
    /*A:[lo,             hi)
        B:[lo,    mid)
                C:[mid,  hi)  
    如果B已经遍历完了，C还未完成的部分本身就在A中，无需遍历C，归并结束
    如果C已经遍历完了，需要把B中剩余的元素拷贝到A中相应的部分。
    */
}
template <typename T>   
ListNodePosi(T) Sort<T>::selectMax(ListNodePosi(T) p, int nums){/*从节点往后n个包括自身里面选择最大的节点*/
    ListNodePosi(T) max = p;
    for(ListNodePosi(T) curr = p;nums > 0;nums--){
        if(curr->data >= max->data){ // 带上等于，排序稳定，靠后的同值先进入有序部分
            max = curr;
        }
        curr = curr->succ;
    }
    return max;
}
template <typename T> 
ListNodePosi(T) Sort<T>::removeListNode(ListNodePosi(T) node){
    ListNodePosi(T) temp = node->pred;
    temp->succ = node->succ;
    node->succ->pred = temp;
    return node;
}
template <typename T> 
void Sort<T>::insertB(ListNodePosi(T) node1, ListNodePosi(T) node2){ // node2移动到node1前
    node1->pred->succ = node2; node2->pred = node1->pred;
    node2->succ = node1; node1 -> pred = node2;

}