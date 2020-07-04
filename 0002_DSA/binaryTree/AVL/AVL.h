#pragma once
#include "../BST/BST.h"
#define Balanced(x) (stature((x).lChild)==stature((x).rChild))//理想平衡条件
#define BalFac(x) (stature((x).lChild)-stature((x).rChild))//平衡因子
#define AvlBalanced(x) ((-2<BalFac(x)) && (BalFac(x)<2))

/******************************************************************************************
 * 在左、右孩子中取更高者
 * 在AVL平衡调整前，借此确定重构方案
 ******************************************************************************************/
#define tallerChild(x) ( \
   stature( (x)->lChild ) > stature( (x)->rChild ) ? (x)->lChild : ( /*左高*/ \
   stature( (x)->lChild ) < stature( (x)->rChild ) ? (x)->rChild : ( /*右高*/ \
   IsLChild( * (x) ) ? (x)->lChild : (x)->rChild /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先 ,父亲作为做子树，就返回其左子树*/ \
   ) \
   ) \
)

template <typename T>
class AVL : public BST<T>{
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
	//其他接口均可沿用
};
// 模板类继承 子类使用父类的成员，用this或者作用域
template <typename T> BinNodePosi(T) AVL<T>::insert ( const T& e ) { //将关键码e插入AVL树中 
   BinNodePosi(T) & x = this->search ( e ); if ( x ) return x; //确认目标节点不存在
   BinNodePosi(T) xx = x = new BinNode<T> ( e, BST<T>::_hot ); BST<T>::_size++; //创建新节点x
// 此时，x的父亲_hot若增高，则其祖父有可能失衡
   for ( BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent ) { //从x之父出发向上，逐层检查各代祖先g
      if ( !AvlBalanced ( *g ) ) { //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将子树
         //FromParentTo ( *g ) = this->rotateAt ( tallerChild ( tallerChild ( g ) ) ); //重新接入原树
         IsLChild(*g)?(g->parent->lChild):(g->parent->rChild) = this->rotateAt ( tallerChild ( tallerChild ( g ) ) ); //重新接入原树
         break; //g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束
      } else //否则（g依然平衡），只需简单地
         this->updateHeight ( g ); //更新其高度（注意：即便g未失衡，高度亦可能增加）
   } //至多只需一次调整；若果真做过调整，则全树高度必然复原
   return xx; //返回新节点位置
} //无论e是否存在于原树中，总有AVL::insert(e)->data == e

template <typename T> bool AVL<T>::remove ( const T& e ) { //从AVL树中删除关键码e
   BinNodePosi(T) & x = this->search ( e ); if ( !x ) return false; //确认目标存在（留意_hot的设置）
   removeAt ( x, BST<T>::_hot );BST<T>::_size--; //先按BST规则删除之（此后，原节点之父_hot及其祖先均可能失衡）
   for ( BinNodePosi(T) g = this->_hot; g; g = g->parent ) { //从_hot出发向上，逐层检查各代祖先g
      if ( !AvlBalanced ( *g ) ) //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至
         //g = FromParentTo ( *g ) = this->rotateAt ( tallerChild ( tallerChild ( g ) ) ); //原父亲
         g = IsLChild(*g)?(g->parent->lChild):(g->parent->rChild) = this->rotateAt ( tallerChild ( tallerChild ( g ) ) ); //原父亲
      this->updateHeight ( g ); //并更新其高度（注意：即便g未失衡，高度亦可能降低）
   } //可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
   return true; //删除成功
} //若目标节点存在且被删除，返回true；否则返回false