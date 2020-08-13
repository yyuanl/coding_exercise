#ifndef __HEAP__
#define __HEAP__
#include <vector>
using namespace std;
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

template <typename T>
class Heap{
public:
    //成员变量是引用  构造函数参数必须是引用  必须使用初始化列表  因为引用不能赋值
    Heap(vector<T> &v,int len, bool bg_hp = true):_heap(v),is_big_heap(bg_hp), size(len){
        heapify();
    }
/*堆下滤例程，堆物理呈现为一个数组，对某个秩的元素进行下滤*/
    int percolateDown(int posi);
    T getTop(){return _heap[0];}
    bool reaplaceTop(T e);
private:
    vector<T> &_heap;
    bool is_big_heap;
    int size;
    /*对一个向量重新构建成堆*/
    void heapify();
    void print(){
        for(auto e:_heap){
            cout<<e<<" ";
        }cout<<endl;
    }
};
/*堆下滤例程，堆物理呈现为一个数组，对某个秩的元素进行下滤*/
template <typename T> 
int Heap<T>::percolateDown(int posi){ // 大顶堆还是小顶堆
    int j;
    while( posi != ( j =  (is_big_heap) ? ProperParentBigHP(_heap, size, posi) : ProperParentSmallHP(_heap, size, posi) ) ){   
        swap(_heap[posi], _heap[j]); // 保证堆序性
        posi = j;
    }
    return posi;
}
/*对一个向量重新构建成堆*/
template <typename T>
void Heap<T>::heapify(){ // Floyd建堆算法，O(n)时间
    for( int index = size / 2 - 1;0 <= index;index--){ //从最后一个内部节点 
        percolateDown(index);  // 依次下滤
    }
    // cout<<"create heap is ... "<<endl;
    // print();
}
template <typename T>
bool Heap<T>::reaplaceTop(T e){
    _heap[0] = e;
    percolateDown(0);
    // cout<<"after reapleaceTop ... "<<endl;
    // print();
}
#endif