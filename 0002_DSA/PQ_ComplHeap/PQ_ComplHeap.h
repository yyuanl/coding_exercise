/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once
/*��*/
#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]������
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]���Һ���
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //ȡ���ߣ���ʱǰ�����ȣ�
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���

#include "../vector/Vector.h" //�������ؼ̳л��ƣ���������
#include "../PQ/PQ.h" //�������ȼ�����ADTʵ�ֵ�
template <typename T> struct PQ_ComplHeap : public PQ<T>, public Vector<T> { //��ȫ�����
   //friend class UniPrint; //��ʾ���ʹ�ã����򲻱���������
   PQ_ComplHeap() { } //Ĭ�Ϲ���
   PQ_ComplHeap ( T* A, Rank n ) { copyFrom ( A, 0, n ); heapify ( _elem, n ); } //��������
   void insert ( T ); //���ձȽ���ȷ�������ȼ����򣬲������
   T getMax(); //��ȡ���ȼ���ߵĴ���
   T delMax(); //ɾ�����ȼ���ߵĴ���
}; //PQ_ComplHeap
template <typename T> void heapify ( T* A, Rank n ); //Floyd�����㷨
template <typename T> Rank percolateDown ( T* A, Rank n, Rank i ); //����
template <typename T> Rank percolateUp ( T* A, Rank i ); //����

//#include "PQ_ComplHeap_implementation.h"
template <typename T> T PQ_ComplHeap<T>::getMax() {  return _elem[0];  } //ȡ���ȼ���ߵĴ���

template <typename T> void PQ_ComplHeap<T>::insert ( T e ) { //������������ȫ�������
   Vector<T>::insert ( e ); //���Ƚ��´�����������ĩβ
   percolateUp ( _elem, _size - 1 ); //�ٶԸô���ʵʩ���˵���
}

//�������еĵ�i������ʵʩ���˲�����i < _size
template <typename T> Rank percolateUp ( T* A, Rank i ) {
   while ( 0 < i ) { //�ڵִ�Ѷ�֮ǰ��������
      Rank j = Parent ( i ); //����[i]֮����[j]
      if ( lt ( A[i], A[j] ) ) break; //һ������˳������������ɣ�����
      swap ( A[i], A[j] ); i = j; //���ӻ�λ��������������һ��
   } //while
   return i; //�����������յִ��λ��
}

template <typename T> T PQ_ComplHeap<T>::delMax() { //ɾ���ǿ���ȫ����������ȼ���ߵĴ���
   T maxElem = _elem[0]; _elem[0] = _elem[ --_size ]; //ժ���Ѷ����״���������֮��ĩ����
   percolateDown ( _elem, _size, 0 ); //���¶Ѷ�ʵʩ����
   return maxElem; //���ش�ǰ���ݵ�������
}

//������ǰn�������еĵ�i��ʵʩ���ˣ�i < n
template <typename T> Rank percolateDown ( T* A, Rank n, Rank i ) {
   Rank j; //i���䣨���������������У���Ϊ����
   while ( i != ( j = ProperParent ( A, n, i ) ) ) //ֻҪi��j����
      { swap ( A[i], A[j] ); i = j; } //���߻�λ�������������½����i
   return i; //�������˵ִ��λ�ã���i��j��
}



template <typename T> void heapify ( T* A, const Rank n ) { //Floyd�����㷨��O(n)ʱ��
   for ( int i = n/2 - 1; 0 <= i; i-- ) //�Ե׶��ϣ�����
/*DSA*///{
      percolateDown ( A, n, i ); //���˸��ڲ��ڵ�
/*DSA*///for ( int k = 0; k < n; k++ ) {
/*DSA*///  int kk = k; while ( i < kk ) kk = (kk - 1) / 2;
/*DSA*///  i == kk ? print(A[k]) : print("    " );
/*DSA*///}; printf("\n");
/*DSA*///}
}