/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "../binTree/BinTree.h" //引入BinTree
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"

template <typename T> class BST : public BinTree<T> { //由BinTree派生BST模板类
//using BinTree<T>::_root;
protected:
   BinNodePosi(T) _hot; //“命中”节点的父亲
   BinNodePosi(T) connect34 ( //按照“3 + 4”结构，联接3个节点及四棵子树
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) );
   BinNodePosi(T) rotateAt ( BinNodePosi(T) x ); //对x及其父亲、祖父做统一旋转调整
public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
   virtual BinNodePosi(T) & search ( const T& e ); //查找
   virtual BinNodePosi(T) insert ( const T& e ); //插入
   // BinNodePosi(T) insert ( const T& e ); //插入
   virtual bool remove ( const T& e ); //删除
//    /*DSA*/
//    /*DSA*/void stretchToLPath() { stretchByZag ( _root ); } //借助zag旋转，转化为左向单链
//    /*DSA*/void stretchToRPath() { stretchByZig ( _root ); } //借助zig旋转，转化为右向单链
//    /*DSA*/void stretch();
};

/******************************************************************************************
 * 按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
 * 子树根节点与上层节点之间的双向联接，均须由上层调用者完成
 * 可用于AVL和RedBlack的局部平衡调整
 ******************************************************************************************/
template <typename T> BinNodePosi(T) BST<T>::connect34 (
   BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
   BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
   //*DSA*/print(a); print(b); print(c); printf("\n");
   a->lChild = T0; if ( T0 ) T0->parent = a;
   a->rChild = T1; if ( T1 ) T1->parent = a; this->updateHeight ( a );
   c->lChild = T2; if ( T2 ) T2->parent = c;
   c->rChild = T3; if ( T3 ) T3->parent = c; this->updateHeight ( c );
   b->lChild = a; a->parent = b;
   b->rChild = c; c->parent = b; this->updateHeight ( b );
   return b; //该子树新的根节点
}


template <typename T> BinNodePosi(T) & BST<T>::search ( const T & e ) { //在BST中查找关键码e,迭代版本
   if ( !BinTree<T>::_root || e == BinTree<T>::_root->data ) { _hot = NULL; return BinTree<T>::_root; } //在树根v处命中
   for ( _hot = BinTree<T>::_root; ; ) { //自顶而下
      BinNodePosi(T) & c = ( e < _hot->data ) ? _hot->lChild : _hot->rChild; //确定方向
      if ( !c || e == c->data ) 
        return c;
     _hot = c; //命中返回，或者深入一层
   } //无论命中或失败，hot均指向v之父亲（或为NULL）
} //返回目标节点位置的引用，以便后续插入、删除操作

template <typename T> BinNodePosi(T) BST<T>::insert ( const T& e ) { //将关键码e插入BST树中  
   BinNodePosi(T) & x = BST<T>::search ( e ); 
   //cout<<"search result is "<<x->data<<endl;
   if ( x ) return x; //确认目标不存在（留意对_hot的设置）
   x = new BinNode<T> ( e, _hot ); //创建新节点x：以e为关键码，以_hot为父
   BinTree<T>::_size++; //更新全树规模
   BinTree<T>::updateHeightAbove ( x ); //更新x及其历代祖先的高度
   return x; //新插入的节点，必为叶子
} //无论e是否存在于原树中，返回时总有x->data == e


/******************************************************************************************
 * BST节点删除算法：删除位置x所指的节点（全局静态模板函数，适用于AVL、Splay、RedBlack等各种BST）
 * 目标x在此前经查找定位，并确认非NULL，故必删除成功；与searChildhIn不同，调用之前不必将hot置空
 * 返回值指向实际被删除节点的接替者，hot指向实际被删除节点的父亲——二者均有可能是NULL
 ******************************************************************************************/
template <typename T>
static BinNodePosi(T) removeAt ( BinNodePosi(T) & x, BinNodePosi(T) & hot ) {
   BinNodePosi(T) w = x; //实际被摘除的节点，初值同x
   BinNodePosi(T) rep = NULL; //实际被删除节点的接替者
   if ( !HasLChild ( *x ) ) //若*x的左子树为空，则可
      rep = x = x->rChild; //直接将*x替换为其右子树
   else if ( !HasRChild ( *x ) ) //若右子树为空，则可
      rep = x = x->lChild; //对称地处理——注意：此时succ != NULL
   else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
      w = w->succ(); //（在右子树中）找到*x的直接后继*w
      swap ( x->data, w->data ); //交换*x和*w的数据元素
      BinNodePosi(T) u = w->parent;
      ( ( u == x ) ? u->rChild : u->lChild ) = rep = w->rChild; //隔离节点*w
   }
   hot = w->parent; //记录实际被删除节点的父亲
   if ( rep ) rep->parent = hot; //并将被删除节点的接替者与hot相联
   release ( w->data ); release ( w ); return rep; //释放被摘除节点，返回接替者
} //release()负责释放复杂结构，与算法无直接关系，具体实现详见代码包
/*
remove：找到被删的节点的接替着，做好与hot连接
1.删除5，12这样的节点，接替者是可能不为空的子节点，6和NULL
       9
     /  \   
    5   12
     \
      6
2.删除左右子树都存在的节点：
 1)删除下面的9：其后继8，只需要交换9和8的数据域，对8进行真实的删除就可以，接替者为10，此时hot应该设置为12
    需要连接10和12
        9
     /     \   
    5      12
    \     /   \
     6   8    15
          \
           10
  2）考虑以下情况，删除9：后继（12）的父节点（9）是要删除的节点
    需要连接15和9
        9
     /     \   
    5      12
    \        \
     6       15
*/

template <typename T> bool BST<T>::remove ( const T& e ) { //从BST树中删除关键码e
   BinNodePosi(T) & x = search ( e ); if ( !x ) return false; //确认目标存在（留意_hot的设置）
   removeAt ( x, _hot ); BinTree<T>::_size--; //实施删除
   BinTree<T>::updateHeightAbove ( _hot ); //更新_hot及其历代祖先的高度
   return true;
} //删除成功与否，由返回值指示


/******************************************************************************************
 * BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
 * 注意：尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成
 ******************************************************************************************/
template <typename T> BinNodePosi(T) BST<T>::rotateAt ( BinNodePosi(T) v ) { //v为非空孙辈节点
   /*DSA*/if ( !v ) { printf ( "\a\nFail to rotate a null node\n" ); exit ( -1 ); }
   BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //视v、p和g相对位置分四种情况
   if ( IsLChild ( *p ) ) /* zig */
      if ( IsLChild ( *v ) ) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
         p->parent = g->parent; //向上联接
         return connect34 ( v, p, g, v->lChild, v->rChild, p->rChild, g->rChild );
      } else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
         v->parent = g->parent; //向上联接
         return connect34 ( p, v, g, p->lChild, v->lChild, v->rChild, g->rChild );
      }
   else  /* zag */
      if ( IsRChild ( *v ) ) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
         p->parent = g->parent; //向上联接
         return connect34 ( g, p, v, g->lChild, p->lChild, v->lChild, v->rChild );
      } else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
         v->parent = g->parent; //向上联接
         return connect34 ( g, v, p, g->lChild, v->lChild, v->rChild, p->rChild );
      }
}

/*
无论怎么旋转：三个节点四个子树都要呈现相同的拓扑结构

 按照3+4结构对三个顶点四棵子树进行重组，返回重组后局部子树根节点的位置b
 子树根节点与上层节点之间的双向连接，均由上层调用者完成
 用于AVL和RedBlack的局部平衡调整
 中序遍历序列为{T0,a,T1,b,T2,c,T3}转化为
                  b
             a         c
          T0  T1    T2   T3


zig-zig : 
         g
       /
      p
     / 
    v  
zig-zag:
          g
        /
      p
       \
        v
zag-zag:
      g
       \
        p
        \
         v
zag-zig:
     g
       \
        p
       /
      v


*/


