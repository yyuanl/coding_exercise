/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "BTNode.h" //引入B-树节点类
//#include ".../binarySearch/01binarySearch/binSearch.h"
#include "D:/coding_exercise/0002_DSA/binarySearch/01binarySearch/binSearch.h"

template <typename T> class BTree { //B-树模板类
protected:
   int _size; //存放的关键码总数
   int _order; //B-树的阶次，至少为3——创建时指定，一般不能修改
   BTNodePosi(T) _root; //根节点
   BTNodePosi(T) _hot; //BTree::search()最后访问的非空（除非树空）的节点位置
   void solveOverflow ( BTNodePosi(T) ); //因插入而上溢之后的分裂处理
   void solveUnderflow ( BTNodePosi(T) ); //因删除而下溢之后的合并处理
public:
   BTree ( int order = 3 ) : _order ( order ), _size ( 0 ) //构造函数：默认为最低的3阶
   { _root = new BTNode<T>(); }
   ~BTree() { if ( _root ) release ( _root ); } //析构函数：释放所有节点
   int const order() { return _order; } //阶次
   int const size() { return _size; } //规模
   BTNodePosi(T) & root() { return _root; } //树根
   bool empty() const { return !_root; } //判空
   BTNodePosi(T) search ( const T& e ); //查找
   bool insert ( const T& e ); //插入
   bool remove ( const T& e ); //删除
}; //BTree

template <typename T> BTNodePosi(T) BTree<T>::search ( const T& e ) { //在B-树中查找关键码e
   BTNodePosi(T) v = _root; _hot = NULL; //从根节点出发
   BinSearch<int> BS;
   while ( v ) { //逐层查找
      //Rank r = v->key.search ( e ); //在当前节点中，找到不大于e的最大关键码
      int r = BS.binSearch1(v->key, 0, v->key.size(),e); // 返回小于e的最大索引者
      if ( ( 0 <= r ) && ( e == v->key[r] ) ) return v; //成功：在当前节点中命中目标关键码
      _hot = v; v = v->child[r + 1]; //否则，转入对应子树（_hot指向其父）——需做I/O，最费时间
   } //这里在向量内是二分查找，但对通常的_order可直接顺序查找
   return NULL; //失败：最终抵达外部节点
}

template <typename T> bool BTree<T>::insert ( const T& e ) { //将关键码e插入B树中
   BTNodePosi(T) v = search ( e ); if ( v ) return false; //确认目标节点不存在
   //Rank r = _hot->key.search ( e ); //在节点_hot的有序关键码向量中查找合适的插入位置
   BinSearch<int> BS;
   int r = BS.binSearch1(v->key, 0, v->key.size(), e);
   // _hot->key.insert ( r + 1, e ); //将新关键码插至对应的位置
   // _hot->child.insert ( r + 2, NULL ); //创建一个空子树指针
   _hot->key.insert(_hot->key.begin() + r + 1, e );
   _hot->child.insert(_hot->child.begin() + r + 2, NULL);

   _size++; //更新全树规模
   solveOverflow ( _hot ); //如有必要，需做分裂
   return true; //插入成功
}

template <typename T> //关键码插入后若节点上溢，则做节点分裂处理
void BTree<T>::solveOverflow ( BTNodePosi(T) v ) {
   if ( _order >= v->child.size() ) return; //递归基：当前节点并未上溢
   int s = _order / 2; //轴点（此时应有_order = key.size() = child.size() - 1）
   BTNodePosi(T) u = new BTNode<T>(); //注意：新节点已有一个空孩子
   // for ( Rank j = 0; j < _order - s - 1; j++ ) { //v右侧_order-s-1个孩子及关键码分裂为右侧节点u
   //    u->child.insert ( j, v->child.remove ( s + 1 ) ); //逐个移动效率低
   //    u->key.insert ( j, v->key.remove ( s + 1 ) ); //此策略可改进
   // }
   u->key.assign(v->key.begin() + s + 1, v->key.end());
   u->child.assign(v->child.begin() + s + 1, v->child.end());
   v->key.erase(v->key.begin() + s + 1 , v->key.end());
   v->child.erase(v->child.begin() + s + 1, v->child.end());
   //u->child[_order - s - 1] = v->child.remove ( s + 1 ); //移动v最靠右的孩子
   if ( u->child[0] ) //若u的孩子们非空，则
      for ( int j = 0; j < _order - s; j++ ) //令它们的父节点统一
         u->child[j]->parent = u; //指向u
   BTNodePosi(T) p = v->parent; //v当前的父节点p
   if ( !p ) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; } //若p空则创建之
   //Rank r = 1 + p->key.search ( v->key[0] ); //p中指向u的指针的秩
   vector<int>::iterator it = 1 + find(p->key.begin(), p->key.end(), v->key[0]);
  // p->key.insert ( r, v->key.remove ( s ) ); //轴点关键码上升
   p->key.insert(it, v->key[s]); v->key.erase(v->key.begin() + s);
   //p->child.insert ( r + 1, u );  u->parent = p; //新节点u与父节点p互联
   p->child.insert(it+1, u); u->parent = p;
   solveOverflow ( p ); //上升一层，如有必要则继续分裂——至多递归O(logn)层
}

/*
1. 找到分裂中点
2. 以右半部分数据构造新的超级节点，处理好其后代连接关系
3. 中点上升到父节点，处理好新插入的关键码和相应的后代

*/
