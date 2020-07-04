/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "../BST/BST.h" //基于BST实现Splay
template <typename T> class Splay : public BST<T> { //由BST派生的Splay树模板类
using BinTree<T>::_size;
using BinTree<T>::_root;
using BinTree<T>::print;
protected:
   BinNodePosi(T) splay ( BinNodePosi(T) v ); //将节点v伸展至根
public:
   BinNodePosi(T) & search ( const T& e ); //查找（重写）
   BinNodePosi(T) insert ( const T& e ); //插入（重写）
   bool remove ( const T& e ); //删除（重写）
};



template <typename NodePosi> inline //在节点*p与*lc（可能为空）之间建立父（左）子关系
void attachAsLChild ( NodePosi p, NodePosi lc ) { p->lChild = lc; if ( lc ) lc->parent = p; }

template <typename NodePosi> inline //在节点*p与*rc（可能为空）之间建立父（右）子关系
void attachAsRChild ( NodePosi p, NodePosi rc ) { p->rChild = rc; if ( rc ) rc->parent = p; }

template <typename T> //Splay树伸展算法：从节点v出发逐层伸展
BinNodePosi(T) Splay<T>::splay ( BinNodePosi(T) v ) { //v为因最近访问而需伸展的节点位置
   
   if ( !v ) return NULL; BinNodePosi(T) p; BinNodePosi(T) g; //*v的父亲与祖父
   while ( ( p = v->parent ) && ( g = p->parent ) ) { //自下而上，反复对*v做双层伸展
      BinNodePosi(T) gg = g->parent; //每轮之后*v都以原曾祖父（great-grand parent）为父
      if ( IsLChild ( *v ) )
         if ( IsLChild ( *p ) ) { //zig-zig
            /*DSA*/printf ( "\tzIg-zIg :" ); 
            print ( g ); print ( p ); print ( v ); printf ( "\n" );
            attachAsLChild ( g, p->rChild ); attachAsLChild ( p, v->rChild );
            attachAsRChild ( p, g ); attachAsRChild ( v, p );
         } else { //zig-zag
            /*DSA*/printf ( "\tzIg-zAg :" ); 
            print ( g ); print ( p ); print ( v ); printf ( "\n" );
            attachAsLChild ( p, v->rChild ); attachAsRChild ( g, v->lChild );
            attachAsLChild ( v, g ); attachAsRChild ( v, p );
         }
      else if ( IsRChild ( *p ) ) { //zag-zag
         /*DSA*/printf ( "\tzAg-zAg :" );
         print ( g ); print ( p ); print ( v ); printf ( "\n" );
         attachAsRChild ( g, p->lChild ); attachAsRChild ( p, v->lChild );
         attachAsLChild ( p, g ); attachAsLChild ( v, p );
      } else { //zag-zig
         /*DSA*/printf ( "\tzAg-zIg :" ); 
         print ( g ); print ( p ); print ( v ); printf ( "\n" );
         attachAsRChild ( p, v->lChild ); attachAsLChild ( g, v->rChild );
         attachAsRChild ( v, g ); attachAsLChild ( v, p );
      }
      if ( !gg ) v->parent = NULL; //若*v原先的曾祖父*gg不存在，则*v现在应为树根
      else //否则，*gg此后应该以*v作为左或右孩子
         ( g == gg->lChild ) ? attachAsLChild ( gg, v ) : attachAsRChild ( gg, v );
      this->updateHeight ( g ); this->updateHeight ( p ); this->updateHeight ( v );
   } //双层伸展结束时，必有g == NULL，但p可能非空
   if ( p = v->parent ) { //若p果真非空，则额外再做一次单旋
      /*DSA*/if ( IsLChild ( *v ) ) { printf ( "\tzIg :" ); print ( p ); print ( v ); printf ( "\n" ); }
      /*DSA*/else              { printf ( "\tzAg :" ); print ( p ); print ( v ); printf ( "\n" ); }
      if ( IsLChild ( *v ) ) { attachAsLChild ( p, v->rChild ); attachAsRChild ( v, p ); }
      else                   { attachAsRChild ( p, v->lChild ); attachAsLChild ( v, p ); }
      this->updateHeight ( p ); this->updateHeight ( v );
   }
   v->parent = NULL; return v;
} //调整之后新树根应为被伸展的节点，故返回该节点的位置以便上层函数更新树根


template <typename T> BinNodePosi(T) & Splay<T>::search ( const T & e ) { //在伸展树中查找e
   BinNodePosi(T) p = BST<T>::search ( e );
   this->_root = splay ( p ? p : this->_hot ); //将最后一个被访问的节点伸展至根
   return this->_root;
} //与其它BST不同，无论查找成功与否，_root都指向最后被访问的节点


template <typename T> BinNodePosi(T) Splay<T>::insert ( const T& e ) { //将关键码e插入伸展树中
   
   if ( !this->_root ) { _size++; return this->_root = new BinNode<T> ( e ); } //处理原树为空的退化情况
   if ( e == search ( e )->data ) return this->_root; //确认目标节点不存在
   _size++; BinNodePosi(T) t = this->_root; //创建新节点。以下调整<=7个指针以完成局部重构
   if ( this->_root->data < e ) { //插入新根，以t和t->rc为左、右孩子
      t->parent = this->_root = new BinNode<T> ( e, NULL, t, t->rChild ); //2 + 3个
      if ( HasRChild ( *t ) ) { t->rChild->parent = this->_root; t->rChild = NULL; } //<= 2个
   } else { //插入新根，以t->lc和t为左、右孩子
      t->parent = this->_root = new BinNode<T> ( e, NULL, t->lChild, t ); //2 + 3个
      if ( HasLChild ( *t ) ) { t->lChild->parent = this->_root; t->lChild = NULL; } //<= 2个
   }
   this->updateHeightAbove ( t ); //更新t及其祖先（实际上只有_root一个）的高度
   return this->_root; //新节点必然置于树根，返回之
} //无论e是否存在于原树中，返回时总有_root->data == e

template <typename T> bool Splay<T>::remove ( const T& e ) { //从伸展树中删除关键码e
   
   if ( !_root || ( e != search ( e )->data ) ) return false; //若树空或目标不存在，则无法删除
   BinNodePosi(T) w = _root; //assert: 经search()后节点e已被伸展至树根
   if ( !HasLChild ( *_root ) ) { //若无左子树，则直接删除
      _root = _root->rChild; if ( _root ) _root->parent = NULL;
   } else if ( !HasRChild ( *_root ) ) { //若无右子树，也直接删除
      _root = _root->lChild; if ( _root ) _root->parent = NULL;
   } else { //若左右子树同时存在，则
      BinNodePosi(T) lTree = _root->lChild;
      lTree->parent = NULL; _root->lChild = NULL; //暂时将左子树切除
      _root = _root->rChild; _root->parent = NULL; //只保留右子树
      search ( w->data ); //以原树根为目标，做一次（必定失败的）查找
///// assert: 至此，右子树中最小节点必伸展至根，且（因无雷同节点）其左子树必空，于是  【注意】：zig类的目标节点的左子树不变
      _root->lChild = lTree; lTree->parent = _root; //只需将原左子树接回原位即可
   }
   release ( w->data ); release ( w ); _size--; //释放节点，更新规模
   if ( _root ) this->updateHeight ( _root ); //此后，若树非空，则树根的高度需要更新
   return true; //返回成功标志
} //若目标节点存在且被删除，返回true；否则返回false
