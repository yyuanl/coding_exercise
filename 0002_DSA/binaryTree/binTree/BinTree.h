/*
二叉树模板类：
1.维护根节点，及其规模；
2.维护每个节点的高度属性
3.一些接口：插入/接入（需要指定被接入的父节点），删除子树，遍历（具体封装于节点类模板）
*/
#pragma once
#include <stack>
#include "BinNode.h"
#include "Release.h"

#define FromParentTo(x)(\
	IsRoot(x) ? (&x) : (\
		IsLChild(x)?(x).parent->lChild:(x).parent->rChild \
	)\
)//返回来自父亲的指针，如果x作为左子树，就返回父亲的节点的lChild成员，以便连接操作

#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"
using namespace std;

template<typename T> class BinTree {
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);//更新x的高度
	void updateHeightAbove(BinNodePosi(T) x);//更新x及其祖先的高度
public:
    BinTree() : _size ( 0 ), _root ( NULL ) { } //构造函数
    ~BinTree() { if ( 0 < _size ) remove ( _root );} //析构函数
    int size() const { return _size; } //规模
    bool empty() const { return !_root; } //判空
    BinNodePosi(T) root() const { return _root; } //树根
    //插入：返回插入节点的地址
    BinNodePosi(T) insertAsRoot ( T const& e ); //插入根节点
    BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e作为x的左孩子（原无）插入
    BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e作为x的右孩子（原无）插入
    BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &s ); //T作为x左子树接入
    BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &s ); //T作为x右子树接入
    int remove ( BinNodePosi(T) x ); //删除以位置x处节点为根的子树，返回该子树原先的规模
    BinTree<T>* secede ( BinNodePosi(T) x ); //将子树x从当前树中摘除，并将其转换为一棵独立子树
	template<typename VST>
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }//层次遍历
	template<typename VST>
	void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template<typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }

	void print(BinNodePosi(T) node){
		if(node == NULL)return ;
		Visit<T> vst;
		vst(node->data);
	}

	//comparator
	bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) { return _root &&t._root && (_root == t._root); }
};

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {//O(depth(v)+1)
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));//具体规则根据树决定
}
template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
	while (x) { updateHeight(x); x = x->parent; }
}


template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot ( T const& e ){ 
	_size = 1; 
	return _root = new BinNode<T> ( e ); 
} //将e当作根节点插入空的二叉树
/*DSA*/
/*DSA*/template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC ( BinNodePosi(T) x, T const& e )
/*DSA*/{ _size++; x->insertAsLC ( e ); updateHeightAbove ( x ); return x->lChild; } //e插入为x的左孩子

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC ( BinNodePosi(T) x, T const& e )
{ _size++; x->insertAsRC ( e ); updateHeightAbove ( x ); return x->rChild; } //e插入为x的右孩子

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) {
	//将S作为节点x的左子树插入，S本身置空
	if (x->lChild = S->_root) x->lChild->parent = x;//??
	_size += S->_size; updateHeightAbove(x);
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x;
}
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S) {
	//将S作为节点x的右子树插入，S本身置空
	if (x->rChild = S->_root) x->rChild->parent = x;//??
	_size += S->_size; updateHeightAbove(x);
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x;
}
template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {//assert:x is valid in the tree
	//FromParentTo(*x) = NULL;
	(IsRoot(*x))?_root:(IsLChild(*x) ? x->parent->lChild : x->parent->rChild) = NULL;
	updateHeightAbove(x->parent);//更新祖先高度
	int n = removeAt(x); _size -= n; return n;
}

template<typename T>
static int removeAt(BinNodePosi(T) x) {//删除x及其后代，返回被删除节点的数值
	if (!x)return 0;
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
	release(x->data); release(x); return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {//将子树x从当前树中摘除，并封装为一棵独立子树返回
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL;
	S->_size = x->size(); _size -= S->_size; return S;
}


