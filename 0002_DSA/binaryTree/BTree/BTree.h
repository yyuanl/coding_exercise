/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "BTNode.h" //����B-���ڵ���
//#include ".../binarySearch/01binarySearch/binSearch.h"
#include "D:/coding_exercise/0002_DSA/binarySearch/01binarySearch/binSearch.h"

template <typename T> class BTree { //B-��ģ����
protected:
   int _size; //��ŵĹؼ�������
   int _order; //B-���Ľ״Σ�����Ϊ3��������ʱָ����һ�㲻���޸�
   BTNodePosi(T) _root; //���ڵ�
   BTNodePosi(T) _hot; //BTree::search()�����ʵķǿգ��������գ��Ľڵ�λ��
   void solveOverflow ( BTNodePosi(T) ); //����������֮��ķ��Ѵ���
   void solveUnderflow ( BTNodePosi(T) ); //��ɾ��������֮��ĺϲ�����
public:
   BTree ( int order = 3 ) : _order ( order ), _size ( 0 ) //���캯����Ĭ��Ϊ��͵�3��
   { _root = new BTNode<T>(); }
   ~BTree() { if ( _root ) release ( _root ); } //�����������ͷ����нڵ�
   int const order() { return _order; } //�״�
   int const size() { return _size; } //��ģ
   BTNodePosi(T) & root() { return _root; } //����
   bool empty() const { return !_root; } //�п�
   BTNodePosi(T) search ( const T& e ); //����
   bool insert ( const T& e ); //����
   bool remove ( const T& e ); //ɾ��
}; //BTree

template <typename T> BTNodePosi(T) BTree<T>::search ( const T& e ) { //��B-���в��ҹؼ���e
   BTNodePosi(T) v = _root; _hot = NULL; //�Ӹ��ڵ����
   BinSearch<int> BS;
   while ( v ) { //������
      //Rank r = v->key.search ( e ); //�ڵ�ǰ�ڵ��У��ҵ�������e�����ؼ���
      int r = BS.binSearch1(v->key, 0, v->key.size(),e); // ����С��e�����������
      if ( ( 0 <= r ) && ( e == v->key[r] ) ) return v; //�ɹ����ڵ�ǰ�ڵ�������Ŀ��ؼ���
      _hot = v; v = v->child[r + 1]; //����ת���Ӧ������_hotָ���丸����������I/O�����ʱ��
   } //�������������Ƕ��ֲ��ң�����ͨ����_order��ֱ��˳�����
   return NULL; //ʧ�ܣ����յִ��ⲿ�ڵ�
}

template <typename T> bool BTree<T>::insert ( const T& e ) { //���ؼ���e����B����
   BTNodePosi(T) v = search ( e ); if ( v ) return false; //ȷ��Ŀ��ڵ㲻����
   //Rank r = _hot->key.search ( e ); //�ڽڵ�_hot������ؼ��������в��Һ��ʵĲ���λ��
   BinSearch<int> BS;
   int r = BS.binSearch1(v->key, 0, v->key.size(), e);
   // _hot->key.insert ( r + 1, e ); //���¹ؼ��������Ӧ��λ��
   // _hot->child.insert ( r + 2, NULL ); //����һ��������ָ��
   _hot->key.insert(_hot->key.begin() + r + 1, e );
   _hot->child.insert(_hot->child.begin() + r + 2, NULL);

   _size++; //����ȫ����ģ
   solveOverflow ( _hot ); //���б�Ҫ����������
   return true; //����ɹ�
}

template <typename T> //�ؼ����������ڵ����磬�����ڵ���Ѵ���
void BTree<T>::solveOverflow ( BTNodePosi(T) v ) {
   if ( _order >= v->child.size() ) return; //�ݹ������ǰ�ڵ㲢δ����
   int s = _order / 2; //��㣨��ʱӦ��_order = key.size() = child.size() - 1��
   BTNodePosi(T) u = new BTNode<T>(); //ע�⣺�½ڵ�����һ���պ���
   // for ( Rank j = 0; j < _order - s - 1; j++ ) { //v�Ҳ�_order-s-1�����Ӽ��ؼ������Ϊ�Ҳ�ڵ�u
   //    u->child.insert ( j, v->child.remove ( s + 1 ) ); //����ƶ�Ч�ʵ�
   //    u->key.insert ( j, v->key.remove ( s + 1 ) ); //�˲��ԿɸĽ�
   // }
   u->key.assign(v->key.begin() + s + 1, v->key.end());
   u->child.assign(v->child.begin() + s + 1, v->child.end());
   v->key.erase(v->key.begin() + s + 1 , v->key.end());
   v->child.erase(v->child.begin() + s + 1, v->child.end());
   //u->child[_order - s - 1] = v->child.remove ( s + 1 ); //�ƶ�v��ҵĺ���
   if ( u->child[0] ) //��u�ĺ����Ƿǿգ���
      for ( int j = 0; j < _order - s; j++ ) //�����ǵĸ��ڵ�ͳһ
         u->child[j]->parent = u; //ָ��u
   BTNodePosi(T) p = v->parent; //v��ǰ�ĸ��ڵ�p
   if ( !p ) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; } //��p���򴴽�֮
   //Rank r = 1 + p->key.search ( v->key[0] ); //p��ָ��u��ָ�����
   vector<int>::iterator it = 1 + find(p->key.begin(), p->key.end(), v->key[0]);
  // p->key.insert ( r, v->key.remove ( s ) ); //���ؼ�������
   p->key.insert(it, v->key[s]); v->key.erase(v->key.begin() + s);
   //p->child.insert ( r + 1, u );  u->parent = p; //�½ڵ�u�븸�ڵ�p����
   p->child.insert(it+1, u); u->parent = p;
   solveOverflow ( p ); //����һ�㣬���б�Ҫ��������ѡ�������ݹ�O(logn)��
}

/*
1. �ҵ������е�
2. ���Ұ벿�����ݹ����µĳ����ڵ㣬������������ӹ�ϵ
3. �е����������ڵ㣬������²���Ĺؼ������Ӧ�ĺ��

*/
