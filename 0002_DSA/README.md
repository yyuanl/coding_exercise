##### 一、BST（二叉搜索树）

二叉搜索树的中序遍历结果是一个非递减的向量，可以想象把树的结点垂直投影到水平线上得到。**局部处处具有顺序性，全局具有单调性**。

###### A、基本操作

1. **查找**

   有点二分的思想：

   ``````c++
   struct NodeBst
   {
       int val;
       struct NodeBst *left;
       struct NodeBst *right;
       NodeBst(int v):val(v),left(NULL),right(NULL){}
   };
   
   //查找，与根节点比较分治
   //hot语义：查找结点的父节点，查找失败，返回的NULL假象成一个目标结点作为哨兵
   NodeBst *search(NodeBst *node, int e, NodeBst *&parent){//也可以是迭代版本，代码有
       if(!node || node->val == e)return node;
       parent = node;
       return search((parent->val < e)?node->right:node->left, e, parent);
   }
   ``````

2. **插入：**

   ``````c++
   void insert(NodeBst *root, NodeBst *insertNode){
       int e = insertNode->val;
       NodeBst *parent = root;
       if(!search(root, e, parent)){ // 利用search中对parent的设置，找到插入位置
           if(parent -> val < e){
               parent->right = insertNode;
           }else{
               parent->left = insertNode;
           } 
       }
   }
   ``````

3. **删除：**
   * 单分支：删除的结点的子树最多为1个，直接将子树提升一层到被删除的结点；
   * 双分支：待删除的结点和其后继结点交换（数据域交换），变为单分支情况（后继结点必然左子树为空），即删除后继结点。

4. **总结**：基本操作的时间复杂度正比于树的高度h.

###### B、平衡与等价

​	BST的复杂度取决于高度，有必要进行等价变换使其保持全局单调但高度平衡成为BBST，且操作时间不超过o(logn)，高度为logn.

<img src="./assets/1.png" style="zoom:50%;" />

###### C、AVL树：重平衡

​	完全二叉树的高度可以严格达到llogn，但是这种情况很少。所有的BBST都有两个重要规则：平衡标准和重平衡算法。

1. 平衡因子：

   某结点的平衡因子定义为其左右子树的高度查，AVL树平衡因子小于等于1。

2. 插入操作：

* **LL形式：左边插入引起的失衡，假设k2是最低层次的失衡结点，插入在k1的左侧**

<img src="./assets/2.png" style="zoom:80%;" />

``````c++
/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
    AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
    {
        AVLTreeNode<T>* k1;

        k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        k2->height = max( height(k2->left), height(k2->right)) + 1;
        k1->height = max( height(k1->left), k2->height) + 1;

        return k1;
    }
``````

* **RR形式，右侧某个结点右边插入引起的失衡**

  <img src="./assets/3.png" style="zoom:80%;" />

 ``````c++
/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}
 ``````

* **LR形式，左侧某个结点右边插入引起的失衡**，先对子树（k1）进行RR形式的旋转操作，在对整个(k3)进行LL形势的旋转操作：

  <img src="./assets/4.png" style="zoom:100%;" />

``````c++
/*
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}
``````

* **RL形式，先LL旋转再RR旋转：**<img src="./assets/5.png" style="zoom:100%;" />

``````c++
/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}
``````

* 整个插入接口：**递归的插入，语义是返回被插入树的根，递推返回时，就可以明确重平衡的类型，而且重平衡判断是从底层向上对每个回溯的结点执行的（实际上仅仅一次可以了）**，例如，k2结点失衡了，k1是k2的**左**子树，经过数据判断，插入发生在k1的**右**侧，那么就是**LR**形式了

``````c++

/*
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{ // tree非空，实际就返回tree，直到找到合适的地方，返回新结点
    if (tree == NULL)
    {
        // 新建节点
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if (tree==NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key) // 应该将key插入到"tree的左子树"的情况
    {
        tree->left = insert(tree->left, key);//构造好树型，递归返回的是丢入的的结点（可能new出的）  
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->left) - height(tree->right) == 2) // 递归回溯时就从新结点检查所有父结点
        {
            if (key < tree->left->key)  // 失衡类型
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key) // 应该将key插入到"tree的右子树"的情况
    {
        tree->right = insert(tree->right, key);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else //key == tree->key)
    {
        cout << "添加失败：不允许添加相同的节点！" << endl;
    }

    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}
``````

3. 删除操作：

   和插入同理会引起失衡，需要注意的是**新重构的部分可能会引起更高祖先失衡**，所以可能是O(logn)的操作。

4. 3+4重构：

   每次重平衡过程只会涉及到三个节点，四个子树，不论怎么旋转，最终都会呈现相同的拓扑结构。

<img src="./assets/6.png" style="zoom:100%;" />

​		不妨写一个函数connect34，设计出这种结构，返回重构后的根节点便于调用者连接。在具体的接口设计时，根据不同情况传不同顺序的参数。这个算法封装在BST模板类里面，可供子类使用。

``````c++
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
``````

<img src="./assets/7.png" style="zoom:100%;" />

​	AVL树能够在最坏logn的情况下保证自身平衡，避免了BST的极端退化。但是其删除操作有时成本过高，得不偿失。

#####  二、高级搜索树

###### 1. 伸展树

​	**将刚刚访问的节点逐层的做zig和zag旋转，使其到达根节点，旋转保证BST的单调性。利用访问的局部性，有效的加快信息的访问效率**。

* 逐层伸展，最坏情况下，恶意访问最深的节点，效率仍然低下，因为整个树高没有改变：

  <img src="./assets/13.png" style="zoom:80%;" />

* 双层伸展：**向上追溯两层而非一层**

  * 具体地，子孙异侧调整情况和逐层伸展方法一致

  * **子孙同侧调整方法不同，首先越级到祖节点做旋转调整，之后再到父节点做旋转调整**

    <img src="./assets/15.png" style="zoom:80%;" />

* 最坏情况也得到改善

<img src="./assets/14.png" style="zoom:80%;" />

* splay: 类似与3+4重构

  <img src="./assets/16.png" style="zoom:80%;" />

* search:在伸展树里属于动态操作

  <img src="./assets/17.png" style="zoom:80%;" />

* insert:利用伸展树自身的search算法，不仅定位需要插入的位置，并将其伸展到根节点，然后在根节点附近进行实质的插入。

  <img src="./assets/18.png" style="zoom:80%;" />

* remove:同插入思想类似。找到目标，并将其伸展到根节点（自身的search算法完成），然后将其右子树中的最小的节点作为新的根，这步操作只需要再次使用自身的search来查找原本被删除的节点即可。

  <img src="./assets/19.png" style="zoom:80%;" />

* 伸展树无须记录节点的高度和平衡因子，分摊复杂度也是O(logn)，假如数据的访问具有局部性，则效率会更高。伸展树本身不是BBST，只是在访问树时其本身可以智能的进行调整，减少树的高度。

###### 2. B-树

​	逻辑上与BBST等价，在多级存储结构中使用B树，针对外部查找可减少I/O操作次数。m阶B树指定了每个节点分支数的范围[m/2, m]（m/2取上界）。**B-树的高度变化幅度有限**，大概认为是O(log<sub>m</sub>n)。



​	理解B树节点的关键码向量（有序）和孩子引用的向量关系：

​	<img src="./assets/20.png" style="zoom:100%;" />

* 查找：从根节点依次在每个节点的关键码向量做顺序查找，成功则返回，失败则进入下一节点继续进行查找。每个关键码向量的查找并非使用二分查找，因为超级节点包含的节点数只有几百个，这种规模的向量使用二分查找比顺序查找效率低。

  <img src="./assets/21.png" style="zoom:60%;" />

* 插入：先利用B-树search定位需要插入的节点（必然是在叶节点查找失败），然后再利用向量的search定位关键码的插入位置，最后考察上溢问题。

  <img src="./assets/22.png" style="zoom:60%;" />

  ​	主要要解决上溢问题，多次向上分裂直到满足阶次要求：

  <img src="./assets/23.png" style="zoom:60%;" />

* 删除：先找到要删除的节点，删除关键码。需要解决下溢的问题，“左顾右盼”后，如果兄弟节点能有多余的关键码借出，则进行“旋转”，若无，则需要合并。

  <img src="./assets/24.png" style="zoom:60%;" />

  

<img src="./assets/25.png" style="zoom:60%;" />

###### 3. 红黑树

​	需要一种数据结构，其满足任何的动态操作而引发的结构性变化量不超过O(1)。插入删除操作过程比较复杂，结合代码理解。

* 定义规则：添加外部节点使之成为真二叉树

  * 根部必为黑色
  * 外部节点均为黑色
  * **红**节点的**子**节点和**父**结点必为**黑**色
  * 外部节点到根途径**黑色节点数目相等**

* 插入：对应提升后4阶B树进行理解，关键在于双红修正算法。插入操作引起的结构性变化不超过O(1).

  <img src="./assets/26.png" style="zoom:80%;" />

* 删除：利用提升映射为B树反过来理解过程及原理。过程复杂。

##### 三、词典



###### 1. 原理：

​	利用散列函数实现映射hash()：$key \longrightarrow \&entry$，把关键码映射到桶地址，从而获得访问对象，提高空间利用率。

###### 2. 散列冲突：

​	k1 != k2 ，但hash(k1) == hash(k2)

* 设计散列函数，降低冲突概率
* 制定预案，发生冲突进行排解

###### 3. 散列函数：

* 除余法：hash(key) = key % M，当M取素数时，数据对散列表的覆盖最充分，分布最均匀

  缺陷：不动点，hash(0) == 0；相关性，相邻关键码的散列地址也必相邻。

  * MAD法改正缺陷：$hash(x) = (a * x + b) \% M, a>1, b>0, a\%M \neq 0 $

* 平方取中

* 折叠汇总

* 伪随机数

* 多项式

###### 4. 排解冲突

* 桶单元划分多槽位，问题是预先不知道要分配多少个槽位
* 独立链，对每个桶维护一个链表，链表空间不连续，缓存不友好
* 开放地址，任何散列桶可以接受任何词条。线性试探，懒惰删除。缺点：一次冲突可能引起一系列的冲突
* 改用平方试探，只要桶大小M是素数，保证装填因子小于0.5，那么前M/2(上整)次的平方试探的桶地址都是互异的，提高空间利用率。
* **双向试探，表长取素数M = 4 * k + 3，必然可以保证查找链的前M项均互异**。

##### 四、优先级队列

###### 0.下滤操作

堆最重要的操作是下滤算法：

``````c++
template <typename T> 
int Heap<T>::percolateDown(int posi){ // 大顶堆还是小顶堆
    int j;
    while( posi != ( j =  (is_big_heap) ? ProperParentBigHP(_heap, size, posi) : 							ProperParentSmallHP(_heap, size, posi) ) )
    {   
        swap(_heap[posi], _heap[j]); // 保证堆序性
        posi = j;
    }
    return posi;
}
``````

###### 1.完全二叉堆

​	满二叉树底部右边缺失了一段，每个节点的平衡因子为0或者1

<img src="./assets/27.png" style="zoom:60%;" />

每个节点编号对应在向量中的秩，上图展示了逻辑上的完全二叉堆和物理上的向量对应关系，层次遍历。根是优先级最高的元素。堆序性：父节点的数值（优先级而不是秩）大于子节点，对应向量`a[i]`要不小于`a[1 + 2*i]`和`a[(1 + i) * 2]`

###### 2.插入

只需要在物理向量尾部添加一个元素，如果违反了堆序性则进行上滤。

<img src="./assets/29.png" style="zoom:100%;" />



###### 3.删除	

删除最大元素，为了尽快恢复堆的结构性，用最后元素代替根节点元素，然后进行下滤。

<img src="./assets/30.png" style="zoom:100%;" />

**逻辑上交换完全二叉树父子节点，实际上式在向量中操作**

###### 4.完全二叉堆建堆

​		给一个数组，每个元素大小表示优先级，重构出完全二叉堆，即其秩满足一颗完全二叉树的层次遍历。自下而上的下滤：只考虑非内部节点，如果节点数为n，则最后一个内部节点秩为n/2(下整)-1。每个节点的调整时间，正比于其高度而非深度。O(N)。

<img src="./assets/31.png" style="zoom:100%;" />







###### 5.左式堆

* 动机：为了更快的把两个堆合并起来

* 结构：节点分布便于左边，合并操只涉及右侧。不一定式完全二叉树，但是堆序型仍然保持。

* 衡量左倾性：空结点路径长度

  <img src="./assets/33.png" style="zoom:90%;" />

  左式堆处处左倾，对于任何内部节点，都有$npl(lc(x)) >= npl(rc(x))$，即有$npl(x) = 1 + npl(rc(x))$。

* 左侧链条：左式堆并不意味着左子堆的高度和规模大于右子堆。需要考虑的是右侧链。

  <img src="./assets/34.png" style="zoom:90%;" />

* 合并：递归的合并两个左式堆，按照根节点数据域大小的降序记为a、b，先合并a的右子堆和b，结果记为c，把c接入a，判断a是否满足左倾性。

  <img src="./assets/35.png" style="zoom:80%;" />

  左式堆的插入和删除也可以利用合并来高效完成。

##### 五、串

###### 1.kmp匹配

* 充分利用模式串自匹配的性质：前缀和后缀相同。

​	考虑文本串T和模式串P，在对比过程中平凡的情况是:T的字串[i-j,i)和P的前缀[0,j)完全匹配，当前需要对比T[i]是否和P[i]相同，如果相同，则T和P的指针i和j自增1；如果不相等，我们想要在模式串P的字串[0,j)找到最长的k,使得前缀[0, k)和后缀[j-k,j)相同，这样，只需要让P中下次待对比的字符是P[k],T中待对比的字符不变。可以提前记录模式串自身的这种特性，**next(i)表示[0,i)中前后缀自匹配的最长长度**。

​	<img src="./assets/36.png" style="zoom:40%;" />

* **哨兵**：假象给模式串左端点加上通配符'*'可以匹配任何字符，同时记next[0] = -1。也就是说首字符比配失败情况下，下一个将要对比的字符对是T[i]和P[-1] = *，  必然匹配，则P和T的移动指针同时后移一个单位，相当于T的下一个字符再和P的首个字符进行对比，有利于简化代码和统一理解。

* **构建next数组：**和kmp主算法相似，可以认为是模式串的自身匹配。如果P的长度是n，我们的目标是计算出next[0] = -1 ... next[n - 2] 共n-1个值。想法是利用next(j)计算出next(j+1),利用性质：next(j+1) <= next(j)

  <img src="./assets/37.png" style="zoom:50%;" />

  ``````c++
  #include <iostream>	#include <vector>	#include <string.h>
  using namespace std;
  void buildNext(vector<int> &next, char *P){
      next[0] = -1;
      int j = 0, t = -1;  
     	// t是prefix长度，t = next[j-1]，想从[0, j-1)获得已有的自匹配获得next[j]  
      //j认为是文本串的指针， t认为是模式串
      while(j < next.size()){
          if(t < 0 || P[j] == P[t]){
              //next[++j] = ++t;
              //优化  如果下一次提供的位置的字符和上次位置的字符相同，则属于多次以卵击石的情况
              j++;t++; next[j] = (P[j] != P[t])?t:next[t];  
          }else{
              t = next[t];
          }
      }
  }
  int kmp(char *T, char *P){
      int m = strlen(T),i = 0;
      int n = strlen(P), j = 0;
      vector<int>nt(n-1);
      buildNext(nt, P);
      while(i < m && j < n){
          if(j < 0 || T[i] == P[j]){// j == -1，到哨兵端点，意味着需要下次需要从头重新对比
              i++;j++;
          }else{
              j = nt[j];
          }
      }
      return i-j;
  }
  int main(){
      char t[] = {'a', 'd', 'a', 'f' , 'g' ,'a', 'i', 'f', 'g', 'a', 'd', 's', 'd', 'f', 'd', 's', 'a','\0'};
      char p[] = {'f', 'g' ,'a', 'i', 'f', 'g', 'a', 'd', 's','\0'};
      int up = strlen(t) - strlen(p);
      cout<<"ret is "<<kmp(t,p)<<endl;
      return 0;
  }
  ``````

* 最坏情况下复杂度不超过O(n)。

###### 2.BM算法

* BC：坏字符策略

​	KMP算法挖掘模式串自身的特征，善于利用已有的经验。

​	但是再字符匹配的过程中，单个字符匹配成的概率往往很小，如果反过来考虑匹配失败的情况，利用失败的教训，效率会更高。不妨每次比对从模式串最后一个字符开始比对，发现一个坏字符(失配的字符)a，而期望的字符是b = T[i], 不妨把模式串中的b(存在且合理)的位置和文本串对齐，重新比对，如此就能跳过多个不必要的对齐情况。

* GS:	好后缀策略







##### 六、排序

###### 1. 冒泡排序

​		**有序向量相邻的两个元素是有序的，通过扫描交换来消除无须向量两个紧邻元素的逆序性。每趟扫描，都会有一个元素就位，k次扫描整个向量的前k大个元素必然就为与向量后部分。改进的版本是记录上一次最后一次扫描的位置，从而跳过对有序部分的无效扫描。整个向量后半部分是就位的，前半部分数值随机是真实需要交换的，改进版本就是准确定位需要真实有效交换的区间**。最坏情况下仍需要O(n*n),最好情况需要O(n)。

<img src="./assets/10.png" style="zoom:100%;" />

<img src="./assets/8.png" style="zoom:80%;" />

###### 2. 归并排序

​	**使得左右部分均有序，再合并之，O(n) = 2O(n/2) + O(n)可得时间复杂度为O(nlogn)**

<img src="./assets/9.png" style="zoom:100%;" />

代码关键部分merge()：

``````c++
void merge(vector<T>&v, int lo, int mid, int hi){
    int lenLeft = mid - lo;
    vector<T>B;
    B.assign(v.begin()+lo, v.begin()+lo+mid);
    for(int idx_a = lo,idx_b = 0, idx_c = mid; idx_b < lenLeft;){ //这里不能判断idx_b是否越界
        v[idx_a++] = (idx_c >= hi || B[idx_b] < v[idx_c]) ? B[idx_b++] : v[idx_c++]; 
        // 这里判断idx_b是否越界
    }
    /*  A:[lo,               hi)
        B:[lo,      mid)
                  C:[mid,    hi)  
        如果B已经遍历完了，C还未完成的部分本身就在A中，无需遍历C，归并结束
        如果C已经遍历完了，需要把B中剩余的元素拷贝到A中相应的部分。
        */
}
``````

###### 3. 选择排序

​	**省去了冒泡反复的紧邻节点的交换操作，因为需要遍历比较获得最大值，总体的复杂度为O(n*n)，利用高级数据结构可以达到O(nlogn)**。维护有序和无序两个部分，选择无序中最大节点插入有序头部。

<img src="./assets/11.png" style="zoom:70%;" />

###### 4. 插入排序

   **前半部分维护为有序，后半部分无序，每次取后半部分的首节点插入到前半部分合适的位置。最好情况O(n),最坏情况O(n*n)(全部逆序)**。输入序列的逆序对数是影响插入排序操作的主要因素，因此插入排序也是输入敏感型排序算法。

<img src="./assets/12.png" style="zoom:100%;" />

###### 5、桶排序/计数排序

​	使用于数量大，但是范围小的序列。比如字符串排序。建立26个字符的散列表，为每个字符分配一个计数，表示该序列中此序列的个数。然后按照从小到大顺序重构。O(n)。

###### **6、堆排序**

​	选择排序，由于在无序部分需要遍历每个元素，造成成本过大，如果把无序部分组织为堆，每次选出最大值（这个过程堆会调整）放入有序部分。需要明白堆在物理上是向量，其秩在逻辑上构成堆。可以用一个区间来表示一个堆，可以每次直接交换堆顶和最后一个元素，区间右端点减一，这样恰好把最大值选出来放在末尾，可以认为是置于后边有序的部分。O(nlogn)。

<img src="./assets/32.png" style="zoom:70%;" />

###### 7、快速排序

* 基本思想

  * 轴点：序列中某个轴点将整个序列分为三个部分，L：[0,i),  pivot: a[i],  G:[ i+1, hi)，并且L中的元素都不大于pivot，而G中的元素都不小于pivot。

  * 分而治之：L和G各自有序之后串接起来即可

    <img src="./assets/38.png" style="zoom:70%;" />

  * 培养轴点：归并排序的难点在于合，快排的难点在于分，需要找到轴点，轴点是序列中本身已经就位的元素，而有时候序列本身轴点并不存在，需要培养。从轴点来看，快排实际上是将每个元素转化为轴点的过程。

  * 快速划分：LUG版本，选取首元素作为培养轴点，从左和从右不断逐次把元素放入L、G中，U[lo,hi]两端交替空闲，长度递减为一时，把培养轴点移至空闲处即可。

    <img src="./assets/39.png" style="zoom:100%;" />

  * LUG版本性能分析：不稳定性，两个相同元素顺序可能颠倒。时间：如果每次划分接近平均，则性能能达到下限：O(logn)。最坏情况可达O(n*n)。可以采取随机选取轴点，减少不均衡划分。平均性能达到O(nlogn)。

  * LGU版本：

    <img src="./assets/40.png" style="zoom:80%;" />

    <img src="./assets/41.png" style="zoom:80%;" />

###### 8、希尔排序

* 原理：把序列按照给定的一个宽度d，重组为宽度为d的矩阵，前n*d个分别为矩阵的前0~n-1行，对矩阵按照**列**重排，列排序的算法应该使用**输入敏感**的排序算法(插入排序)，以保证有序性可持续改善，且成本足够低廉。

  <img src="./assets/42.png" style="zoom:80%;" />

###### 9、k-selection

* 选取问题：选取第k大的元素（k-selection），选取中位数（k-selection特例）。长度为n的序列，从小到大排序后位于中间的元素，a[mid],  mid = n/2(下整)。选取中位数是难度最大的一种k-selection问题。
* 从中位数到众数
  * 无序向量中**若有一半以上的元素同为m**，则称之为众数。众数的个数超过其他元素个数的总和。序列可能没有众数。
  * 必要性：**若众数存在，则其必然是中位数**。只要能找到中位数，遍历对其计数就可以判断其是否为众数。

* 求得中位数之前，如何解决众数问题？找到众数的候选者，判断之。

  **减而治之**

  <img src="./assets/43.png" style="zoom:80%;" />

  ``````c++
  #include <iostream>			#include <vector>		using namespace std;
  int majCandiate(vector<int>&v){
      int ret;
      for(int diff = 0, i = 0;i < v.size();i++){ // diff代表当前前缀中ret个数与其他元素总数差
          if(diff == 0){
              ret = v[i];  //前缀某元素恰好占一般，“剪切之“
          }else{
              (ret == v[i]) ? diff++ : diff--;
          }
      }
      return ret;
  }
  bool majCheck(vector<int>&v, int maj){ // 检查候选者maj是否为众数
      int num = v.size() / 2;  int c = 0;
      for(int i = 0; i < v.size(); i++){
          if(v[i] == maj)	c++;
      }
      return c > num;
  }
  bool majority(vector<int>&v, int &maj){
      return majCheck(v, maj = majCandiate(v));
  }
  int main(){
      vector<int>v;
      int maj = -1;
      for(int i = 0; i < 15;i++){
          v.push_back(rand() % 2 + 1);
      }
      for(auto e:v){
          cout<<e<<" ";
      }
      cout<<endl;
      bool ishavemaj = majority(v, maj);
      cout<<"Does it have majority ? "<<ishavemaj<<" maj = "<<maj<<endl;
      return 0;
  }
  ``````

* **使用堆来选出k位数**

  <img src="./assets/44.png" style="zoom:80%;" />

* **减而治之的方法，利用快排的轴点策略**

  <img src="./assets/45.png" style="zoom:80%;" />

##### 七、图

​	表示一个图，只需要结点集合，和邻接矩阵就可以，邻接矩阵存放边类型。

###### 1、bfs

​	从图的某个结点开始bfs搜索，类似树的层次遍历，采用队列装入将要访问的结点，访问当前结点时要把其所有未被访问过的邻居结点找出来放入队列，如此一层一层的访问。简化代码，以接口形式给出当前结点的第一个邻接结点，和其与某个邻接结点的下一个邻接结点。访问的边形成支撑树。两个结点之间的**最短路径**，就是对应以其某个结点开始进行bfs访问至另一个结点的路径。

<img src="./assets/46.png" style="zoom:80%;" />

###### 2、dfs

​	dfs搜索就是找到当前结点任意一个未被访问的邻接结点，对其访问，以它为当前结点再递归的进行dfs搜索，直到某个结点的邻接结点均被访问，递归返回，回溯到上一层再找上一层未被访问的邻接结点进行dfs搜索。从图的某个结点出发，找到该结点未被访问的邻接结点，再对其进行dfs搜索。

<img src="./assets/47.png" style="zoom:80%;" />

一道岛屿的题，把内部的z替换为x

``````c++
#include "./Graph.h"
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <list>
using namespace std;
int row,col;
enum state{M_UNVISITED,M_VISITED,M_CHANGE};
struct point{
    int x, y;
    state s;
    point():x(-1), y(-1), s(M_UNVISITED){}
};
using z_chain = vector<pair<int,int>>;
#define index_leg(i, j) (     ( (i > 0) && (i < row) && (j > 0) && (j < col) )   ? (true):(false))
 
#define inboundary(i, j)  (  (((i) == (row - 1))||((j) == (col - 1))) ? (true) : (false))

// 找一个未被访问过的符合条件 的邻接结点
pair<int, int> randAdj(vector<vector<char>>&v,vector<vector<point>>&flag, int i, int j){
    if(index_leg(i-1,j) && v[i-1][j] == 'z' && flag[i-1][j].s == M_UNVISITED){
        return {i-1,j};
    }
    if(index_leg(i+1,j) && v[i+1][j] == 'z' && flag[i+1][j].s == M_UNVISITED){
        return {i+1,j};
    }
    if(index_leg(i,j-1) && v[i][j-1] == 'z' && flag[i][j-1].s == M_UNVISITED){
        return {i,j-1};
    }
    if(index_leg(i,j+1) && v[i][j+1] == 'z' && flag[i][j+1].s == M_UNVISITED){
        return {i,j+1};
    }
    return {-1,-1};
}

void dfs(vector<vector<char>>&v, int r, int c, vector<vector<point>>&flag, z_chain &zc, bool &zc_okay){
    if(flag[r][c].s == M_VISITED)return ;
    //if(!index_leg(r,c))return ;
    flag[r][c].s = M_VISITED;  //当前结点标记为访问
    //cout<<r<<" "<<c<<endl;
    zc.push_back({r,c});
    if(inboundary(r,c)){  //在边界上
        zc_okay = false;
    }
    for(pair<int, int> adj_index = randAdj(v, flag, r,c);index_leg(adj_index.first, adj_index.second);adj_index = randAdj(v, flag, adj_index.first, adj_index.second)){
        dfs(v, adj_index.first, adj_index.second, flag, zc, zc_okay);
    }
    
}
int main(){
    // vector<char>v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    // vector<pair<int, int>>e = {{0,2},{0,4},{0,7},{2,1},{2,7},{3,7},{3,1},{4,5},{4,6},{5,6},{1,6}};
    // Graph test(v,e);
    // //test.BFS();
    // test.DFS(0);
    //替换z变为x，与边界连接的z不能被替换。岛屿问题。
    
    vector<vector<char>>v = {
                             {'x','x','x','x','x'}, 
                             {'x','z','z','z','x'},
                             {'x','x','z','x','x'},
                             {'x','z','x','z','x'},
                             {'x','x','z','z','x'},
                             {'x','z','z','z','x'},
                             {'x','z','x','z','x'},
                             {'x','z','x','x','x'}
                            };
    row = v.size();
    col = v[0].size();
    list<z_chain>res;
    vector<vector<point>>flags(row, vector<point>(col, point()));
    for(int i = 0; i < row;i++){
        for(int j = 0; j < col;j++){
            if(v[i][j] == 'x' )continue;
            z_chain t; // 以v[i][j]为起点进行dfs搜索 结点记录在t里面
            bool zc_is_ok = true;
            dfs(v, i, j, flags, t, zc_is_ok);
            if(zc_is_ok){
                res.push_back(t);
            }
        }
    }
    // 遍历res  获得结果
    for(auto e:res){
        for(auto ee: e){
            v[ee.first][ee.second] = 'x';
        }
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col;j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}


/*
a b c d e f g h
0 1 2 3 4 5 6 7

*/

``````

##### 八、二叉树的遍历

###### 1、先序

**先序遍历宏观结构：对于每个子树，沿着左侧链条依次访问结点，然后再反向访问各个结点的右子树**

<img src="./assets/48.png" style="zoom:80%;" />

所以整个算法可以认为是不断丢入子树，让其进行上述例程。因此，先写出上述例程的算法：

``````c++
void visitAlongLeftBranch(treeNode *node, stack<treeNode*>&s){//沿着左链访问
    treeNode *leftNode=node;
    while(leftNode != NULL){
        visit(leftNode);
        s.push(leftNode->right);//左链结点依次入栈 ，不必排除空右子树
        leftNode = leftNode->left;
    }
}
``````

那么主算法就是不断丢入子树的循环了：

``````c++
void preOder2(treeNode *root){
    stack<treeNode*>s;
    treeNode*childN = root; //整个树
    while(true){
        visitAlongLeftBranch(childN, s); //例程
        if(s.empty()) break;
        childN = s.top();  s.pop(); //子树
    }
}
``````

###### 2、中序

**中序遍历宏观理解：对于每一个子树，都是沿着左侧链依次谦让访问权，直到最左边结点获得访问权执访问，然后再将访问权交给其右子树，再进行上述谦让。**

<img src="./assets/49.png" style="zoom:100%;" />

每个子树进行的例程如下，不断谦让入栈，但无访问权：

```c++
void goAlongLeftBranck(treeNode* node, stack<treeNode*>&s){
    treeNode*curr = node; 
    while(curr != NULL){ s.push(curr); curr = curr->left;}
}
```

主算法，不断丢入子树，访问左侧链最左边结点：

``````c++
void midOder(treeNode*root){
    treeNode*childN = root; 
    stack<treeNode*>s;
    while(true){
        goAlongLeftBranck(childN, s);  //从当前结点出发 当前结点作为独立的一颗子树 批次入栈
        if(s.empty()) break;
        visit(s.top()); childN = (s.top())->right;//访问最左结点，递交访问控制权至右子树
        s.pop();
    }
}
``````

###### 3、后序

**后序遍历宏观理解，抽象模型和上述相似，先将访问权交给最左结点的右子树，右子树访问完毕，再访问最左结点。需要定义好什么叫右子树访问完毕？1.右子树为空2.右子树不为空，右子树根节点已经被访问。所以还需要维护另外一个栈，来标识左侧链结点的右子树是否访问完毕。如何来说明第二种情况？当前栈顶的元素和上次pop的元素呈现父-右孩子关系时，说明当前栈顶的结点右子树已经被访问结束了**

每个子树的例程如下，不断向左谦让入栈，并构造标识右子树是否访问完毕的栈：

``````c++
void goAlongLeftBranchDs(treeNode*node, stack<treeNode*>&lb_s, stack<bool>&rc_s){
    treeNode*curr = node;
    while(curr != NULL){
        lb_s.push(curr); 
        (curr->right == NULL ) ? rc_s.push(true) : rc_s.push(false);
        curr = curr->left;
    }
}
``````

主算法，不断丢入子树，针对栈顶的结点，只有其右子树访问完毕，其才获得访问权执行访问：

``````c++
void postOrder(treeNode*root){
    treeNode*childN = root;
    treeNode*topNode;
    stack<treeNode*>lb_s;
    stack<bool>rc_s;
    while(true){
        goAlongLeftBranchDs(childN, lb_s,rc_s);
        if(rc_s.top() == true){
            topNode = lb_s.top();
            visit(topNode);lb_s.pop();rc_s.pop();
            if(lb_s.empty() && rc_s.empty()) break;
            if(topNode == lb_s.top()->right) {rc_s.top()=true;childN=NULL;continue;}
        }
        childN = lb_s.top()->right;
    }
}
``````

**另外一种只是用一个栈的做法**：对于每个树，总体方向是往左走，找到最高左侧可见叶结点，迫不得已才转到右侧，此时再入栈右侧子树，当栈顶为空时，表明整个向左路线完毕。在入栈过程中，先放入当前栈顶的右子树（子树根结点），再放入左子树。

<img src="./assets/50.png" style="zoom:100%;" />

``````c++
#include <iostream>
#include <stack>
using namespace std;
struct TN{
    int val;
    TN *left;
    TN *right;
    TN(int x):val(x), left(NULL), right(NULL){}
};
// 判断两个结点是否为兄弟关系 是 返回true 否 返回false
#define rightBrother(a, b) ( ((b->left) == (a) || ((b->right) == (a)))  ? false  :  true   )
/*
             1
      3             4
    9   7         10
      6   8 
*/
void gotoLeftLeaf(stack<TN*>&s){  // 最高左侧可见叶结点
    TN *t;
    while(t = s.top()){  //终止条件是 压入NULL 栈顶为空
        /*尽量往左边走*/
        if(t->left != NULL){  // 左子树存在
            if(t->right != NULL)s.push(t->right);  // 先压入右子树
            s.push(t->left);  // 在压入左子树
        }else{
            s.push(t->right);  //如果左子树为空 简明的压入右子树
        }
    }
    s.pop();  //pop掉栈顶的NULL
}

void traversePost(TN *root){
    stack<TN*>s;  //辅助栈 模拟 后序遍历过程：入栈顺序：尽量往左侧链走， 子树根结点->其右子树->左子树
    s.push(root);
    TN *node = root;  // 栈上次弹出的结点  为了判断当前栈顶结点是父结点还是右子树
    while(!s.empty()){
        if(rightBrother(node, s.top())){  // 栈顶结点和之前弹出结点成右兄关系
            gotoLeftLeaf(s);
        }
        // 如果有右兄子树 已经把他入栈了
        node = s.top(); s.pop(); cout<<node->val<<" ";  // 弹出栈顶，简明的访问
    }
}
int main(){
    TN n1(1);
    TN n3(3);
    TN n4(4);
    TN n9(9);
    TN n7(7);
    TN n10(10);
    TN n6(6);
    TN n8(8);
    n1.left = &n3; n1.right = &n4;
    n3.left = &n9; n3.right = &n7;
    n4.left = &n10;
    //n9.right = &n6;
    n7.left = &n6; n7.right = &n8;
    TN *root = &n1;
    traversePost(&n1);

    return 0;
}
``````

###### 4、建树

输入{3,5,6,-1,-1,2,7,-1,-1,4,-1,-1,1,9,-1,-1,8,-1,-1}利用先序遍历重构一个树并找到某两个结点最近公共祖先。利用栈模拟先序过程。

``````c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    //TreeNode *parent;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


TreeNode *findLowestCommonAncestor(TreeNode *node, TreeNode *p, TreeNode *q){
    if(node == NULL || node == p || node == q)return node;
    TreeNode *left = findLowestCommonAncestor(node->left, p, q);  // 沿着左子树找这两个结点
    TreeNode *right = findLowestCommonAncestor(node->right, p, q);  // 沿着右子树找这两个结点
    if(left == NULL)return right;  // 两个结点在都在右子树
    if(right == NULL)return left;  // 两个结点都在左子树
    // 两个结点分布在node左右子树 返回即可；
    return node;
}

TreeNode *createTree(vector<int>&v, TreeNode * &p, TreeNode * &q){
    TreeNode *root = NULL;
    
    stack<TreeNode*>sk;
    for(int i = 0; i < v.size(); i++){
        if(sk.empty() && i==0){
            root = new TreeNode(v[i]);
            sk.push(root);
            continue;
        }

        if(v[i] != -1){
           
            TreeNode *t = new TreeNode(v[i]);
            if(v[i] == 7)p = t;
            if(v[i] == 8)q = t;
            TreeNode *parent = sk.top();
            if(parent -> left == NULL){
                parent -> left = t;  //前序遍历沿右侧链插入
                //cout<<"parent is "<<parent->val<<" left child is "<<parent->left->val<<endl;
            }else if(parent -> right == NULL){
                parent -> right = t;  // 往父结点 左边子树插入
                //cout<<"parent is "<<parent->val<<" left child is "<<parent->right->val<<endl;
            }
            sk.push(t);
        }else{
            i++;
            sk.pop();
            while(!sk.empty() && sk.top()->right != NULL){  // 找到应该插入的父结点
                sk.pop();
            }
        }
    }
    return root;
}
void free(TreeNode *node){
    if(node == NULL)
        return ;
    free(node -> left);
    free(node -> right);
    delete node;
}
void check(TreeNode *node){
    if(!node)return ;
    cout<<node->val<<" ";
    if(node->left != NULL){
        cout<<"left child is "<<node->left->val<<" ";
    }else
    {
        cout<<"left child is NULL"<<" ";
    }

    if(node->right != NULL){
        cout<<"right child is "<<node->right->val<<endl;
    }else
    {
        cout<<"right child is NULL"<<endl;
    }
    check(node->left);
    check(node->right);
}
int main()
{
    TreeNode *head = nullptr;
    vector<int>nums = {3,5,6,-1,-1,2,7,-1,-1,4,-1,-1,1,9,-1,-1,8,-1,-1};
    TreeNode *p = NULL;
    TreeNode *q = NULL;
    TreeNode *root = createTree(nums, p, q);
    //check(root);
    
    TreeNode *res = findLowestCommonAncestor(root, p,q);  // 最近公共祖先
    cout<<"res is "<<res->val<<endl;
    free(root);// 销毁
    return 0;
}
``````

