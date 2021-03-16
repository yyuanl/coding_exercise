#### 一、List

`java.util.List`接口extends Collection接口

**特点**：

* 有序的集合，存储元素和取出元素的顺序是一致的
* 有索引，包含一些带索引的方法
* 允许存储重复的元素

List接口中带索引的方法：

* `public void add(int index,E element)`将元素插入到指定位置上
* `public E get(int index)`返回集合中指定位置上的元素
* `public E remove(int index)`删除指定位置的元素，返回被删除的元素
* `public E set(int index)`用指定元素替换集合中指定位置的元素，返回更新前的元素

#### 二、List的实现类

##### 1、ArrayList

底层维护一个数组，增删慢，查询快。

##### 2、LinkedList

底层是由链表结构实现，增删快，查询慢。

特有的操作首尾节点的方法：

**增**

* `public void addFirst(E e)`列表头插入指定的元素
* `public void addLast(E e)`列表尾插入指定的元素
* `public void push(E e)`与`addLast`方法效果相同

**查**

* `public E getFirst()`返回列表首元素
* `public E getLast()`返回列表尾元素

**删**

* `public E removeFirst()`删除首元素，并返回该元素
* `public E removeLast()`删除末尾元素，并返回该元素
* `public E pop()`和`removeFirst()`效果一致

**判空**

* `public boolean isEmpty()`空列表返回`true`

##### 3、Vector

底层是可变长数组，线程同步的。

#### 三、Set接口

一个不包含重复元素的Collection，不带索引。

Set集合调用add方法时，会调用元素的`hashCode`方法和`equals`方法，判断元素是否重复。哈希值相同且`equals`返回`true`时则重复。

#### 四、Set的实现类

c++中的set底层数据结构是红黑树

##### 1、HashSet

**自身特点**：

* 无序集合
* 底层是哈希表结构实现

Object的`toString`方法默认是对象的哈希值，`hashCode`方法返回一个整数作为哈希值，作为其逻辑地址。String类重写了`hashCode`方法。

JDK8之后，如果哈希冲突的元素数量超过8个，则将其组织为红黑树结构。小于8个使用链表结构。

**使用HashSet来存储自定义元素，必须重写hashCode和equals方法**

##### 2、LinkedHashSet

**有序不重复**

底层维护一个哈希表和链表，多使用一个链表来保证元素有序。

#### 五、Collections集合工具类

##### 1、往集合添加一些元素

`public static <T>boolean addAll(Collection<T>,T...elements)`

##### 2、打乱集合顺序

`public static void shuffle(List<?>list)`

##### 3、对集合（List）元素排序

* `public static <T> void sort(List<T>list)`默认升序

  被排序的集合，其元素必须实现Comparable,重写compareTo方法

* 指定规则排序

  `public static <T> void sort(List<T>list, Comparator<? super T>)`

  

