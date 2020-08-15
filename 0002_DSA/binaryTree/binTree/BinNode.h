#pragma once
#include <cstdlib>
#include <stack>
#include <queue>
using namespace std;
#define BinNodePosi(T) BinNode<T>* //node position
#define stature(p) ((p)?(p)->height:-1)// node height(empty tree is -1)
typedef enum { RB_RED, RB_BLACK } RBColor;//node color

//用宏来定义一些函数，编译器预处理时直接替换，可以免去传递参数、传递寄存器的开销，有效利用CPU cache，但会增大可执行文件体积
//一般宏函数用于简短的被频繁调用的函数

/*
* BinNode状态与性质的判断
*/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lChild))
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x)||HasRChild(x))
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
/*
* 与BinNode有特定关系的节点和指针（宏函数换行应在行末加/）
*/
#define sibling(p)(\
	IsLChild(*(p)) ? \
		(p)->parent->rChild: \
		(p)->parent->lChild \
)//兄弟
#define uncle(x)(\
	IsLChild(*((x)->parent)) ? \
		(p)->parent->parent->rChild: \
		(p)->parent->parent->lChild \
)//叔叔
/*红黑树相关*/
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //外部节点也视作黑节点
#define IsRed(p) ( ! IsBlack(p) ) //非黑即红
#define BlackHeightUpdated(x) ( /*RedBlack高度更新条件*/ \
   ( stature( (x).lc ) == stature( (x).rc ) ) && \
   ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) \
)



template<typename T> struct BinNode {
	//members
	T data;
	BinNodePosi(T) parent; BinNodePosi(T) lChild; BinNodePosi(T) rChild;
	int height;
	int npl;//Null Path Length(空节点通路长度，用于左式堆,也可直接用height代替??)
	RBColor color;//Red/Black Tree

	//constructor
	BinNode() :parent(NULL), lChild(NULL),rChild(NULL),height(0),npl(1),color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c){}

	//operations ，把一些操作封装与节点类，便于树类进行调用
	int size();//统计当前节点的后代总数，亦即为以其为根的子树的规模
	BinNodePosi(T) insertAsLC(T const&);//insert as left child
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ();//取当前节点的直接后继
   
    /*将遍历算啊封装到节点类*/
	template<typename VST> void travLevel(VST&);//层次遍历
	template<typename VST> void travPre(VST&);//先序遍历
	template<typename VST> void travIn(VST&);//中序遍历
	template<typename VST> void travPost(VST&);//后序遍历

	//comparators
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator<=(BinNode const& bn) { return data <= bn.data; }
	bool operator>(BinNode const& bn) { return data > bn.data; }
	bool operator>=(BinNode const& bn) { return data >= bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }
};

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) { return lChild = new BinNode(e, this); }
template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) { return rChild = new BinNode(e, this);}

//================先序遍历======================
//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST> //元素类型、操作器
static void visitAlongVine ( BinNodePosi(T) x, VST& visit, stack<BinNodePosi(T)>& S ) {
   while ( x ) {
      visit ( x->data ); //访问当前节点
      S.push ( x->rChild ); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
      x = x->lChild;  //沿左分支深入一层
   }
}

template <typename T, typename VST> //元素类型、操作器
void travPre_I2 ( BinNodePosi(T) x, VST& visit ) { //二叉树先序遍历算法（迭代版#2）
   stack<BinNodePosi(T)> S; //辅助栈
   while ( true ) {
      visitAlongVine ( x, visit, S ); //从当前节点出发，逐批访问
      if ( S.empty() ) break; //直到栈空
      x = S.top(); S.pop(); //弹出下一批的起点
   }
}
template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPre ( VST& visit ) { //二叉树先序遍历算法统一入口   
    cout<<"previous traversing "<<endl;
    travPre_I2 ( this, visit );  //迭代版#1  
    printf("\n");  
}
//================先序遍历======================

//================中序遍历======================
//中序遍历例程
template <typename T> //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongVine ( BinNodePosi(T) x, stack<BinNodePosi(T)>& S ) {
   while ( x ) { S.push ( x ); x = x->lChild; } //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I1 ( BinNodePosi(T) x, VST& visit ) { //二叉树中序遍历算法例程，丢入一个节点，中序遍历其后代
   stack<BinNodePosi(T)> S; //辅助栈
   while ( true ) {
      goAlongVine ( x, S ); //从当前节点出发，逐批入栈
      if ( S.empty() ) break; //直至所有节点处理完毕
      x = S.top();  S.pop(); visit ( x->data ); //弹出栈顶节点并访问之
      x = x->rChild; //转向右子树
   }
}
template<typename T> template<typename VST>
void BinNode<T>::travIn(VST& visit) {//二叉树中序遍历统一接口
    cout<<"middle oder traversing "<<endl;
    travIn_I1(this, visit);//迭代版#1
    printf("\n");
}
//================中序遍历======================

//================后序遍历======================
template <typename T> //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoLeftmostLeaf ( stack<BinNodePosi(T)>& S ) { //沿途所遇节点依次入栈
   while ( BinNodePosi(T) x = S.top() ) //自顶而下，反复检查当前节点（即栈顶）
      if ( HasLChild ( *x ) ) { //尽可能向左
         if ( HasRChild ( *x ) ) S.push ( x->rChild ); //若有右孩子，优先入栈
         S.push ( x->lChild ); //然后才转至左孩子
      } else //实不得已
         S.push ( x->rChild ); //才向右
   S.pop(); //返回之前，弹出栈顶的空节点
}

template <typename T, typename VST>
void travPost_I ( BinNodePosi(T) x, VST& visit ) { //二叉树的后序遍历（迭代版）
   stack<BinNodePosi(T)> S; //辅助栈
   if ( x ) S.push ( x ); //根节点入栈
   while ( !S.empty() ) { //x始终为当前节点
      if ( S.top() != x->parent ) ////若栈顶非x之父（而为右兄）
         gotoLeftmostLeaf ( S ); //则在其右兄子树中找到HLVFL（相当于递归深入）
      x = S.top(); S.pop(); visit ( x->data ); //弹出栈顶（即前一节点之后继），并访问之
   }
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPost ( VST& visit ) { //二叉树后序遍历算法统一入口 
    cout<<"post traversing "<<endl;
    travPost_I ( this, visit );  //迭代版
    printf("\n");
}
//================后序遍历======================

template<typename T>
BinNodePosi(T) BinNode<T>::succ() {
	//定位当前节点的直接后继，即线性排序后的直接后继，亦为中序遍历后的直接后继
	BinNodePosi(T) s = this;//记录后继的临时变量
	if (rChild) {//如果有右孩子，那么直接后继必然是右子树中最靠左的那个
		s = rChild;
		while (HasLChild(*s)) s = s->lChild;
	}
	else {//否则，直接后继应当是“将当前节点包含于其左子树中的最低祖先”
		while (IsRChild(*s)) s = s->parent;//向左上方移动
		s = s->parent;//再向右上方移动一步，即抵达其直接后继（画图即可发现这一点）
	}
    /*第二张情况：比如求4的后继是1
          1
        /
       2     
        \
         3
          \
           4
    */
	return s;//返回NULL 说明当前节点已经是中序遍历的终点
}
template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST& visit) {
   cout<<"traverse Level:"<<endl;
	//层次遍历
   int currnums = 1;int nextnums = 0;
	queue<BinNodePosi(T)> Q;
	Q.push(this);
	while (!Q.empty()) {
		BinNodePosi(T) x = Q.front(); visit(x->data);Q.pop(); currnums--;
		if (HasLChild(*x)) 
      {
         Q.push(x->lChild);
         nextnums++;
      }
		if (HasRChild(*x))
      {
         Q.push(x->rChild);
         nextnums++;

      } 
      if(currnums == 0){
         cout<<"\n";
         currnums = nextnums;
         nextnums = 0;
      }

	}
}