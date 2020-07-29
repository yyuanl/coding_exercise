#pragma once
typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template <typename T> class Vector{
protected:
    Rank _size; int _capacity;  T* _elem; //规模、容量、数据区
    void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
public:
    // 构造函数
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v
    { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c
    Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
    Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
    Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
    Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
    // 析构函数
    ~Vector() { delete [] _elem; } //释放内部空间
    Rank search ( T const& e ) const //有序向量整体查找
    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
    Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找
    T remove ( Rank r ); //删除秩为r的元素
    int remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素

};

template <typename T> //元素类型
void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) { //以数组区间A[lo, hi)为蓝本复制向量
   _elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零
   while ( lo < hi ) //A[lo, hi)内的元素逐一
      _elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
}


// 二分查找算法（版本C）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
template <typename T> static Rank binSearch ( T* S, T const& e, Rank lo, Rank hi ) {
   /*DSA*/printf ( "BIN search (C)\n" );
   while ( lo < hi ) { //每步迭代仅需做一次比较判断，有两个分支
      /*DSA*/ //for ( int i = 0; i < lo; i++ ) printf ( "     " ); if ( lo >= 0 ) for ( int i = lo; i < hi; i++ ) printf ( "....^" ); printf ( "\n" );
      Rank mi = ( lo + hi ) >> 1; //以中点为轴点（区间宽度的折半，等效于宽度之数值表示的右移）
      ( e < S[mi] ) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
   } //成功查找不能提前终止
   /*DSA*/ //for ( int i = 0; i < lo - 1; i++ ) printf ( "     " ); if ( lo > 0 ) printf ( "....|\n" ); else printf ( "<<<<|\n" );
   return lo - 1; //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
} //有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置

template <typename T> //在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
Rank Vector<T>::search ( T const& e, Rank lo, Rank hi ) const { //assert: 0 <= lo < hi <= _size
//    return ( rand() % 2 ) ? //按各50%的概率随机使用二分查找或Fibonacci查找
//           binSearch ( _elem, e, lo, hi ) : fibSearch ( _elem, e, lo, hi );
    binSearch ( _elem, e, lo, hi );
}

template <typename T> 
T Vector<T>::remove ( Rank r ) { //删除向量中秩为r的元素，0 <= r < size
   T e = _elem[r]; //备份被删除元素
   remove ( r, r + 1 ); //调用区间删除算法，等效于对区间[r, r + 1)的删除
   return e; //返回被删除元素
}
template <typename T> 
int Vector<T>::remove ( Rank lo, Rank hi ) { //删除区间[lo, hi)
   if ( lo == hi ) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0)
   while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移hi - lo个单元
   _size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
   shrink(); //若有必要，则缩容
   return hi - lo; //返回被删除元素的数目
}