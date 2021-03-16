##### 1、字符串的创建

使用双引号的字符串字面值来创建字符串时，会在堆的字符串常量池中new一个字符串对象，其引用底层的字节数组。使用“abc"两次创建字符串，这两个字符串变量（名字不同）的地址相同。使用字符数组来new一个字符串对象直接在堆区域创建一个新的字符串对象。

```java
String str1 = "abc";
String str2 = "abc";
char [] ch = {'a','b', 'c'};
String str3 = new String(ch);
String str4 = new String(ch);
System.out.println(str1==str2); //true
System.out.println(str1==str3); //false
System.out.println(str2==str3); //false
System.out.println(str3==str4); //false
```

##### 2、String常用API

* 判断内容是否相等

  * `public boolean equals(Object a)`此字符串与指定对象进行比较
  * `public boolean equalsIgnoreCase(String b)`忽略大小写

  推荐写法：`"abc".equals(str)`

* 访问字符串内部信息

  * `public int length()`返回此字符串的长度
  * `public String concat(String str)`拼接
  * `public char charAt(int index)`返回索引处的字符
  * `public int indexOf(String str)`返回子字符串第一次出现在该字符串内的索引
  
* 字符串截取

  * `public String substring(int low)`返回一个字符串，从索引low到结尾
  * `public String substring(int low,int hi)`返回一个子字符串，从索引low到hi-1

* 字符串转换
  * `public char[] toCharArray()`拆分为字符数组
  * `public byte[] getBytes()`获得字符串的底层字节数组
  * `public String replace(CharSequence oldString, CharSequence newString)`把字符串中所有的老的子串替换为新子串。
* 字符串分割
  
  * `public String[] splits(String regex)`按照规则切分字符串

##### 3、static

- 静态成员和静态方法属于类
- 静态方法不能访问非静态成员
- 静态成员存储在方法去的静态区内
- 当第一次使用到本类时，其静态代码块执行唯一一次。其典型用途：用来初始化静态变量。

##### 4、Arrays

- `Arrays.toString()`静态方法可以把数组元素变为字符串，方便打印
- `Arrays.sort()`对数组排序

##### 5、super

* 子类成员方法中访问父类成员变量、成员方法：`super.父类成员`、`super.父类方法`
* 子类构造方法中访问父类构造方法：`super()`,`super(参数)`。必须时第一个语句，且只能是一个

##### 6、this

- 本类的成员方法中调用本类的成员变量、成员方法
- 本类的构造方法中访问本类的另一个构造方法：`this(...)`,必须是第一个语句，且只能是一个。`this`和`super`不能同时使用。

##### 7、抽象类

* `public abstract`来修饰方法叫做抽象方法，没有方法体
* `public abstract`修饰类叫做抽象类，抽象类不必有抽象方法，但抽象方法的类必须是抽象类
* 抽象类不能实例化
* 抽象类可以有构造方法供其子类创建对象时使用，及new子类来初始化抽象类成员，利用`super()`
* 抽象类的子类必须重写所有抽象方法，除非本身也是抽象类

##### 8、接口

```java
public interface 接口名称{
	//抽象方法 public abstract void function();
	//默认方法 public default void function(){...}
	//静态方法 public static void function(){...}
	//私有方法
    public static final int NUM = 10; // 接口的常量，final修饰不可改变，三个关键字可省略不写
}
public class 接口实现类名称 implements 接口名称{  //接口实现类
    
}
```

* 抽象方法让接口实现类来实现

* `java8`开始使用默认方法进行接口升级，接口实现类可重写默认方法也可不重写。接口实现类继承了接口默认方法，重写则为自己的方法。

* 接口的静态方法只能用接口名称调用

* `java9`开始允许接口当中定义私有方法，供接口中默认方法调用，实现代码复用：

  * 普通私有方法，解决多个默认方法之间重复代码问题：

  ```java
  private 返回值类型 方法名称（参数列表）{
  	方法体
  }
  ```

  * 静态私有方法，解决多个静态方法之间重复代码问题：

  ```java
  private static 返回值类型 方法名称（参数列表）{
  	方法体
  }
  ```

* 接口常量必须初始化赋值

* 接口没有静态代码块，接口不能有构造方法

* 一个类只能继承一个父类，但是可以实现多个接口。如果两个接口中有重复的默认方法，那么实现类必须要覆盖重写。

* 父类中方法和接口中默认方法重复了，优先使用父类中方法。继承优先于接口实现。

##### 9、多态

**动态绑定**，父类的引用指向子类对象，运行时决定执行哪个方法。使用父类或者接口作为方法的参数。

父类引用指向子类对象：`父类名称 对象名 = new 子类名称()`

或者：`接口名称 对象名 = new 实现类名称()`

* 多态中访问成员变量：直接通过对象名称访问，以左边类型进行查找，找不到向上找；间接通过成员方法访问，子类覆盖则使用子类方法，否则使用父类。
* 多态中访问成员方法：new的是谁，就优先用谁，没有则向上找。多态就是让子类重写父类方法，父类的引用绑定子类的方法。
* 父类引用指向子类对象本身就是一种向上转型的写法
* 如果父类引用想要使用子类特有的方法需要进行向下转型，需要使用`instanceof `判断

##### 10、final

表示**不可改变**

* 修饰类：`public final class 类名称`。表示当前类**不能有任何子类**。
* 修饰方法：`修饰符 final返回值类型 方法名称（参数列表）{}`限制此方法**不能被子类重写**

**注意**：`abstract final`不能同时出现

* 修饰局部变量：常量，不可变。只能赋值一次。

**不可变的理解**：对于基本类型，表示变量的值（值）不能改变；低于引用类型，表示变量的值（引用的对象的地址值）不可改变，但对象的内容可变。

* 修饰成员变量：该成员变量不可变，**成员变量具有默认值**，如果不手动赋值初始化其实已经赋值了。

##### 11、权限修饰符

|                        | `public` | `protected` | `(default)` | `private` |
| :--------------------: | :------: | :---------: | :---------: | :-------: |
|   同一个类（我自己）   |   YES    |     YES     |     YES     |    YES    |
|   同一个包（我邻居）   |   YES    |     YES     |     YES     |    NO     |
|  不同包子类（我儿子）  |   YES    |     YES     |     NO      |    NO     |
| 不同包非子类（陌生人） |   YES    |     NO      |     NO      |    NO     |

##### 12、内部类

* 成员内部类

* 局部内部类：局部内部类访问成员方法的局部变量时，该局部变量必须时有效`final`的

* **匿名内部类**:

  ```java
  接口名称 对象名 = new 接口名称(){
  	@Override
  	//重写抽象方法
      method(){...}
  };
  //结合匿名对象
  new 接口名称(){
  	@Override
  	//重写抽象方法
  }.method();
  ```

  * new代表创建对象的动作
  * 接口名称表示匿名内部类要实现的接口
  * `{...}`才是匿名内部类

