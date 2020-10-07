#pragma once
#include <vector>
#include <algorithm>
#include "./list/ListNode.h"
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"
#include <string.h>

/*一些堆的宏*/
// i处元素的左/右孩子元素 的秩
#define LC(i)           (1+((i)<<1))
#define RC(i)           ((1 + (i))<<1)

// 判断大小为n的堆，某秩x是否合法
#define ISINHEAP(n, x)  (  (   (-1) < (x)   )   &&  (   (x) < (n)  )    )
// #define ISINHEAP(n, i)  ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) )
// 判断某节点是否有左/右孩子
#define ISHAVELC(n, i)  (  ISINHEAP(n, LC(i) )  )
#define ISHAVERC(n, i)  (  ISINHEAP(n, RC(i) )  )
#define MAXOFTWOINDEX(v, i, j)  ( ( (v[i]) < (v[j]) ) ? (j) : (i) )
#define MINOFTWOINDEX(v, i, j)  ( ( (v[i]) <= (v[j]) ) ? (i) : (j) )
// 找到父子节点最大的节点在向量中的秩 vector size i  对于堆来说存在右子树存在左子树一定存在
#define ProperParentBigHP(v, n, i)   (  ISHAVERC(n, i) ? MAXOFTWOINDEX( v, MAXOFTWOINDEX(v, i, LC(i)) , RC(i)) :\
                                (  ISHAVELC(n, i) ? MAXOFTWOINDEX( v, i, LC(i)) : (i) )\
                                )
#define ProperParentSmallHP(v, n, i) ( ISHAVERC(n,i) ? MINOFTWOINDEX(v, MINOFTWOINDEX(v, i, LC(i)), RC(i) ) :\
                                        ( ISHAVELC(n, i) ? MINOFTWOINDEX( v, i, LC(i)) : (i) )\
                                    )
                                    
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
/*插入排序，链表*/
    ListNodePosi(T) insertionSort(ListNodePosi(T)first);
/*堆排序*/
    void heapSort(vector<T> &v, bool ascend);
/*快速排序*/
    void quickSort(vector<T> &v, int lo, int hi);
/*希尔排序*/
    void shellSort(vector<T> &v, int lo, int hi);
/*计数排序,桶排序的一种*/
    void countSort(char *str, int len);

/*访问vector每一个元素，方便排序前后比较*/    // 模板写在类外出错，还不会改
    template <typename VST>
    void visitvtr(vector<T>&v,VST &visit){ // 第二个参数为函数对象
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
public:
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
/*堆下滤例程，堆物理呈现为一个数组，对某个秩的元素进行下滤*/
    int percolateDown(vector<T>&heap, const int len, int posi, bool big_heap);
/*对一个向量重新构建成堆*/
    void heapify(vector<T>&v, const int len, bool big_heap);
/*快速排序培养轴点，LUG划分*/
    int my_partition_LUG(vector<T>&v, int lo, int hi);
    int my_partition_LGU(vector<T>&v, int lo, int hi);
    
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


/*快速排序*/
template <typename T>
void Sort<T>::quickSort(vector<T> &v, int lo, int hi){
    if(hi - lo < 2) return ;
    int mi = ((rand() % 2) == 0)  ?  my_partition_LUG(v, lo, hi) : my_partition_LGU(v, lo, hi); // LUG 培养轴点
    quickSort(v, lo, mi);
    quickSort(v, mi + 1, hi);
}
/*希尔排序*/
template <typename T>
void Sort<T>::shellSort(vector<T> &v, int lo, int hi){
    /*
            ...  i -d ...
            ...  i    ...
    */
    //采用ps序列{1，3，5，7，...,1073741823,...}
    for(int d = 0x3FFFFFFF;d>=1;d >>= 1){
        for(int i = lo + d; i < hi;i++){ // 按照矩阵行分别对每列的前i行进行插入排序,实质上就是从序列lo+d处开始到hi-1
            T x = v[i]; // 备份待插入的元素，插入排序需要依次移动元素
            int k = i - d; // 初始化插入的位置
            while( lo <= k && v[k] > x){
                v[k+d] = v[k]; 
                k -= d;
            }
            v[k + d] = x;  //插入待排序的元素
        }
    }
}
/*计数排序*/
template <typename T>
void Sort<T>::countSort(char *str, int len){
    int count[26];
    memset(count, '\0', sizeof(count));
    int acc[26];
    for(int i = 0; i < len;i++){
        count[str[i] - 0x61]++;
        cout<<"num is "<<count[str[i] - 0x61]<<endl;
    }
    int k = 0;
    for(int i = 0; i < 26;i++){ 
        int j = count[i];
        while(j-- > 0){
            str[k++] = 0x61 + i;
        }
    }
}
//  模板定义在类外出错
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
<<<<<<< HEAD
    B.assign(v.begin()+lo, v.begin()+lo+mid);
    for(int idx_a = lo,idx_b = 0, idx_c = mid; idx_b < lenLeft;){ // 这里不能判断idx_c是否越界
        //前半段归入的条件是：前半段元素小或者后半段已经遍历完（idx_c越界）
        v[idx_a++] = (idx_c >= hi || B[idx_b] < v[idx_c]) ? B[idx_b++] : v[idx_c++]; // 这里判断idx_c是否越界
=======
    B.assign(v.begin()+lo, v.begin()+mid);
    for(int idx_a = lo,idx_b = 0, idx_c = mid; idx_b < lenLeft;){ // 这里不能判断idx_b是否越界
        v[idx_a++] = (idx_c >= hi || B[idx_b] <= v[idx_c]) ? B[idx_b++] : v[idx_c++]; // 这里判断idx_b是否越界  【注意  使用小于等于保证时稳定排序】
>>>>>>> 1261ceff0439c61f6da4fe2fe51c1045c1f82cd2
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

/*堆下滤例程，堆物理呈现为一个数组，对某个秩的元素进行下滤*/
template <typename T> 
int Sort<T>::percolateDown(vector<T>&heap, const int len, int posi, bool big_heap){ // 大顶堆还是小顶堆
    int j;
    while( posi != ( j =  (big_heap) ? ProperParentBigHP(heap, len, posi) : ProperParentSmallHP(heap, len, posi) ) ){   
        swap(heap[posi], heap[j]); // 保证堆序性
        posi = j;
    }
    return posi;
}
/*对一个向量前len个元素重新构建成堆*/
template <typename T>
void Sort<T>::heapify(vector<T>&v, const int len, bool big_heap){ // Floyd建堆算法，O(n)时间
    for( int index = len / 2 - 1;0 <= index;index--){ //从最后一个内部节点 
        percolateDown(v, len, index, big_heap ? true : false);  // 依次下滤
    }
}
/*堆排序*/
template <typename T>
void Sort<T>::heapSort(vector<T> &v, bool ascend){
    int unsortedLen = v.size();
    heapify(v, unsortedLen, ascend ? true:false); // 建堆 大顶堆和小顶堆
    while(0 < unsortedLen--){
        swap(v[0], v[unsortedLen]); // 选最大的放到有序的右边部分
        percolateDown(v, unsortedLen, 0, ascend?true:false); // 对交换上去堆顶再进行下滤
    }
}
/*快排之培养轴点，LUG划分*/
template <typename T>
int Sort<T>::my_partition_LUG(vector<T> &v, int lo, int hi){
    cout<<"use LUG algorithm "<<endl;
    swap(v[lo], v[rand() % (hi-lo) + lo]); // 随机取得轴点
    int pivot = v[lo]; hi--;
    // 拓展G ----> 拓展L ----> 拓展G ----> 拓展L......
    while(lo < hi){
        while(lo < hi && pivot <= v[hi]) {
            --hi;   //向左拓展G
        }
        v[lo] = v[hi];  // 小于轴点皆归入L
        while(lo < hi && v[lo] <= pivot){  //向右拓展L
            ++lo;
        }
        v[hi] = v[lo];// 大于轴点者皆归入G
    }
    v[lo] = pivot;
    return lo;
}

template <typename T>
int Sort<T>::my_partition_LGU(vector<T> &v, int lo, int hi){
    /*
    [lo                                                    hi)
                    k                      m
  L:(lo             k]  
                    G:(k                   m)     
                                        U: [m              hi)
    */
   cout<<"use LGU algorithm "<<endl;
   swap(v[lo], v[lo + rand() % (hi - lo)]);
   int pivot = v[lo]; int k = lo; // 开始L G皆为空
   for(int m = lo + 1; m < hi;m++){
       if(v[m] < pivot){
           //swap(v[m++], v[++k]);
           swap(v[m], v[++k]);
       }//else {m++;}
   }
   swap(v[lo], v[k]);
   return k;
}