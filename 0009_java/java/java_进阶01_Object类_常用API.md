### 一、Object类

#### 1、toString

直接打印一个对象，实际就是调用了`toString()`方法。

```java
String str = "abc";
System.out.println(str);//等价于System.out.println(str.toString());
```

自己定义的类一般对其进行重写，方便打印查看。

`ArrayList`重写了`toString`方法

#### 2、equals

比较两个对象是否相等。`Object`类源码：

```java
public boolean equals(Object obj) {//多态
	return (this == obj);
}
```

默认比较两个对象的地址值。需要重写：

```java
public class Person{
    Private String name;
    @Override
    public boolean equals(Object obj) {//多态
        if(this == obj){ // 传入本身
            return ture;
        }
        if(obj == null){ // 传入NULL
            return false;
        }
    	if(obj instanceof Person){//向下转型
            Person temp = (Person)obj;
            return this.name.equals(temp.name);
        }
		return false;
	}
}
```

### 二、Objects类

`Objects`类中`equals`静态方法容忍空指针

### 三、时间类

#### 1、Date类

表示日期和时间类，表示特定的瞬间，精确到毫秒

#### 2、DateFormat类

`java.text.DateFormat`文本和日期的转换的抽象类。使用其子类`java.text.SimpleDateFormat extends DateFormat`，使用给定的模式字符串来初始化，比如：`yyyy-MM-dd HH:mm:ss`。

格式化、解析：

```java
Date d = new Date(); // 获取当前时间
SimpleDateFormat sd = new SimpleDateFormat("yyyy-MM-dd HH-mm-ss"); // 格式器
String s = sd.format(d);// 将Date对象格式化为我们方便使用的样子（字符串）
System.out.println(d);
System.out.println(s);
//解析。parse声明了一个异常。抛出了异常，就要处理。
Date dd = sd.parse("2021-01-26 13-24-41");//字符串与模式串匹配则正常
```

#### 3、java.util.Calendar类

抽象类，提供很多操作日历字段的方法。使用其静态方法`getInstance()`来创建其对象。内部维护一个日历字段表，可以通过静态成员作为key传入API来查看、修改字段对应的值。

### 四、System类

#### 1、currentTimeMillis();

获取当前毫秒值，测试程序运行时间

#### 2、arraycopy

数组复制

`````java
public static void arraycopy(
	Object src, //源数组
	int srcPos, // 源数组起始位置
	Object dest,//目的数组
	int destPos, //目的数组起始位置
	int length  //复制长度
);
`````

### 五、StringBuilder类

底层是字节数组，但没有被`final`修饰，可以改变长度。初始容量是16，超出容量会自动扩容。

#### 1、构造方法：

```java
StringBuilder b = new StringBuilder();
StringBuilder bb = new StringBuilder("dabaff");
```

#### 2、常用成员方法：

```java
StringBuilder bu = new StringBuilder();
bu.append("dac").append("jkk").append(1);
```

* append返回对象本身
* reverse反转内容
* toString返回String

### 六、包装类

把基本数据类型封装成一个类，可以利用成员方法来操作基本数据类型

#### 1、装箱与拆箱

* 装箱：基本类型数据转换成包装类

  * 使用构造方法：过时
  * 使用静态方法**valueof**

  ```java
  Integer i = Integer.valueof(100);
  Integer ii = Integer.valueof("123");
  ```

* 拆箱：包装类转换成基本数据类型

  ```java
  Integeri = Integer.valueof(100);
  int i_int = i.intValue();
  ```

#### 2、自动装箱与拆箱

jdk1.5之后特性

```java
Integer i = 1; // 自动装箱
i = i + 2;//自动拆箱进行计算再进行自动装箱变成包装类
ArrayList<Integer>list = new ArrayList<>();
list.add(2);//自动装箱
int x = list.get(0);//自动拆箱
```

### 七、字符串和基本类型的转化

#### 1、基本类型转字符串

`基本类型+""`即可

#### 2、字符串转基本类型

使用包装类的`parseXxx`静态方法