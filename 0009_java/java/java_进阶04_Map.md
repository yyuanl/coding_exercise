#### 一、Map接口

`public interface Map<k,v>`

`Map`是双列集合，key和value成对，key不能重复，value可以重复

实现类

##### 1、HashMap

底层是哈希表，无序集合。c++中的`unordered_map`。

##### 2、LinkedHashMap

继承了HashMap，底层是哈希表和链表构成。保证了迭代顺序。

##### 3、Map常用方法

* 添加键值对（k,v）。如果k不存在，返回null；否则重置k对应的v，然后返回v

  ```java
  public V put(V key, V value)
  ```

* 给定key，删除键值对。key存在，返回value；不存在返回null。

  ```
  public V remove(Object key)
  ```

* 通过key获取value。存在，返回value。否则返回null。

  ```java
  public V get(Object key)
  ```

* 集合中是否包含指定的key，包含返回true。

  ```java
  public boolean containsKey(Object key)
  ```

##### 4、利用key遍历Map

使用Map的keySet()方法获得key构成的一个Set，然后使用Set集合的遍历方法先遍历出key，间接地遍历出value。

##### 5、利用Map.Entry<K,V>遍历Map

是Map接口中的内部接口Entry。一个Map集合创建，内部就创建一个Entry对象，用来记录**键值对**这个整体对象，保存key和value的映射。

Map中的`entrySet`方法返回一个Set集合，其中存储Entry对象。可以遍历这个Set集合，然后再使用Entry对象中的`getkey`和`getValue`方法来获取键、值。

##### 6、利用HashMap存储自定义类型键

作为key的元素，必须唯一，因此需要重写hashCode和equals方法

