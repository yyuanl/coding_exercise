/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "../BST/BST.h" //����BSTʵ��Splay
template <typename T> class Splay : public BST<T> { //��BST������Splay��ģ����
using BinTree<T>::_size;
using BinTree<T>::_root;
using BinTree<T>::print;
protected:
   BinNodePosi(T) splay ( BinNodePosi(T) v ); //���ڵ�v��չ����
public:
   BinNodePosi(T) & search ( const T& e ); //���ң���д��
   BinNodePosi(T) insert ( const T& e ); //���루��д��
   bool remove ( const T& e ); //ɾ������д��
};



template <typename NodePosi> inline //�ڽڵ�*p��*lc������Ϊ�գ�֮�佨���������ӹ�ϵ
void attachAsLChild ( NodePosi p, NodePosi lc ) { p->lChild = lc; if ( lc ) lc->parent = p; }

template <typename NodePosi> inline //�ڽڵ�*p��*rc������Ϊ�գ�֮�佨�������ң��ӹ�ϵ
void attachAsRChild ( NodePosi p, NodePosi rc ) { p->rChild = rc; if ( rc ) rc->parent = p; }

template <typename T> //Splay����չ�㷨���ӽڵ�v���������չ
BinNodePosi(T) Splay<T>::splay ( BinNodePosi(T) v ) { //vΪ��������ʶ�����չ�Ľڵ�λ��
   
   if ( !v ) return NULL; BinNodePosi(T) p; BinNodePosi(T) g; //*v�ĸ������游
   while ( ( p = v->parent ) && ( g = p->parent ) ) { //���¶��ϣ�������*v��˫����չ
      BinNodePosi(T) gg = g->parent; //ÿ��֮��*v����ԭ���游��great-grand parent��Ϊ��
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
      if ( !gg ) v->parent = NULL; //��*vԭ�ȵ����游*gg�����ڣ���*v����ӦΪ����
      else //����*gg�˺�Ӧ����*v��Ϊ����Һ���
         ( g == gg->lChild ) ? attachAsLChild ( gg, v ) : attachAsRChild ( gg, v );
      this->updateHeight ( g ); this->updateHeight ( p ); this->updateHeight ( v );
   } //˫����չ����ʱ������g == NULL����p���ܷǿ�
   if ( p = v->parent ) { //��p����ǿգ����������һ�ε���
      /*DSA*/if ( IsLChild ( *v ) ) { printf ( "\tzIg :" ); print ( p ); print ( v ); printf ( "\n" ); }
      /*DSA*/else              { printf ( "\tzAg :" ); print ( p ); print ( v ); printf ( "\n" ); }
      if ( IsLChild ( *v ) ) { attachAsLChild ( p, v->rChild ); attachAsRChild ( v, p ); }
      else                   { attachAsRChild ( p, v->lChild ); attachAsLChild ( v, p ); }
      this->updateHeight ( p ); this->updateHeight ( v );
   }
   v->parent = NULL; return v;
} //����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ظýڵ��λ���Ա��ϲ㺯����������


template <typename T> BinNodePosi(T) & Splay<T>::search ( const T & e ) { //����չ���в���e
   BinNodePosi(T) p = BST<T>::search ( e );
   this->_root = splay ( p ? p : this->_hot ); //�����һ�������ʵĽڵ���չ����
   return this->_root;
} //������BST��ͬ�����۲��ҳɹ����_root��ָ����󱻷��ʵĽڵ�


template <typename T> BinNodePosi(T) Splay<T>::insert ( const T& e ) { //���ؼ���e������չ����
   
   if ( !this->_root ) { _size++; return this->_root = new BinNode<T> ( e ); } //����ԭ��Ϊ�յ��˻����
   if ( e == search ( e )->data ) return this->_root; //ȷ��Ŀ��ڵ㲻����
   _size++; BinNodePosi(T) t = this->_root; //�����½ڵ㡣���µ���<=7��ָ������ɾֲ��ع�
   if ( this->_root->data < e ) { //�����¸�����t��t->rcΪ���Һ���
      t->parent = this->_root = new BinNode<T> ( e, NULL, t, t->rChild ); //2 + 3��
      if ( HasRChild ( *t ) ) { t->rChild->parent = this->_root; t->rChild = NULL; } //<= 2��
   } else { //�����¸�����t->lc��tΪ���Һ���
      t->parent = this->_root = new BinNode<T> ( e, NULL, t->lChild, t ); //2 + 3��
      if ( HasLChild ( *t ) ) { t->lChild->parent = this->_root; t->lChild = NULL; } //<= 2��
   }
   this->updateHeightAbove ( t ); //����t�������ȣ�ʵ����ֻ��_rootһ�����ĸ߶�
   return this->_root; //�½ڵ��Ȼ��������������֮
} //����e�Ƿ������ԭ���У�����ʱ����_root->data == e

template <typename T> bool Splay<T>::remove ( const T& e ) { //����չ����ɾ���ؼ���e
   
   if ( !_root || ( e != search ( e )->data ) ) return false; //�����ջ�Ŀ�겻���ڣ����޷�ɾ��
   BinNodePosi(T) w = _root; //assert: ��search()��ڵ�e�ѱ���չ������
   if ( !HasLChild ( *_root ) ) { //��������������ֱ��ɾ��
      _root = _root->rChild; if ( _root ) _root->parent = NULL;
   } else if ( !HasRChild ( *_root ) ) { //������������Ҳֱ��ɾ��
      _root = _root->lChild; if ( _root ) _root->parent = NULL;
   } else { //����������ͬʱ���ڣ���
      BinNodePosi(T) lTree = _root->lChild;
      lTree->parent = NULL; _root->lChild = NULL; //��ʱ���������г�
      _root = _root->rChild; _root->parent = NULL; //ֻ����������
      search ( w->data ); //��ԭ����ΪĿ�꣬��һ�Σ��ض�ʧ�ܵģ�����
///// assert: ���ˣ�����������С�ڵ����չ�������ң�������ͬ�ڵ㣩���������ؿգ�����  ��ע�⡿��zig���Ŀ��ڵ������������
      _root->lChild = lTree; lTree->parent = _root; //ֻ�轫ԭ�������ӻ�ԭλ����
   }
   release ( w->data ); release ( w ); _size--; //�ͷŽڵ㣬���¹�ģ
   if ( _root ) this->updateHeight ( _root ); //�˺������ǿգ��������ĸ߶���Ҫ����
   return true; //���سɹ���־
} //��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false
