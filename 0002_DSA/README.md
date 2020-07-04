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

##### 三、排序





###### 1.冒泡排序

​		**有序向量相邻的两个元素是有序的，通过扫描交换来消除无须向量两个紧邻元素的逆序性。每趟扫描，都会有一个元素就为，k次扫描整个向量的前k大个元素必然就为与向量后部分。改进的版本是记录上一次最后一次扫描的位置，从而跳过对有序部分的无效扫描。整个向量后半部分是就位的，前半部分数值随机是真实需要交换的，改进版本就是准确定位需要真实有效交换的区间**。最坏情况下仍需要O(n*n),最好情况需要O(n)。

<img src="./assets/10.png" style="zoom:100%;" />

<img src="./assets/8.png" style="zoom:80%;" />

###### 2.归并排序

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

###### 3.选择排序

​	**省去了冒泡反复的紧邻节点的交换操作，因为需要遍历比较获得最大值，总体的复杂度为O(n*n)，利用高级数据结构可以达到O(nlogn)**。维护有序和无序两个部分，选择无序中最大节点插入有序头部。

<img src="./assets/11.png" style="zoom:70%;" />

###### 3.插入排序

   **前半部分维护为有序，后半部分无序，每次取后半部分的首节点插入到前半部分合适的位置。最好情况O(n),最坏情况O(n*n)(全部逆序)**。输入序列的逆序对数是影响插入排序操作的主要因素，因此插入排序也是输入敏感型排序算法。

<img src="./assets/12.png" style="zoom:100%;" />

