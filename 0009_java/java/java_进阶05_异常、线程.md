####  一、异常的处理

##### 1、throw关键字

可以使用throw关键字在指定的方法中抛出指定的异常

**运行期异常**

```java
throw new xxxException("异常原因描述")
```

```java
public class ThrowsMain {
    public static void main(String[] args) {
        int []arr1 = null;
        int []arr2 = {1,2,3};
        //getElement(arr1,1);
        getElement(arr2,4);
    }
    public static int getElement(int [] arr, int index){
        //数组如果是空，则抛出空指针异常，告知调用者相关信息。运行期的异常可以交给jvm处理
        if(arr == null){
            throw new NullPointerException("pass a null array...");
        }
        //索引越界，则抛出索引越界异常，告知调用者相关信息。运行期的异常可以交给jvm处理
        if(index < 0 || index > arr.length-1){
            throw new ArrayIndexOutOfBoundsException("pass a illegal index...");
        }
        return arr[index];
    }
}
```

可以利用`Objects`的`requireNonNull`静态方法判断对象是否为空：

```java
Objects.requireNonNull(<obj>,<"描述信息的字符串">);
```

##### 2、throws

**编译期异常**

编译期异常必须处理，要么在方法声明处继续使用`throws`抛出异常，要么使用`try...catch`处理

```java
import java.io.FileNotFoundException;

public class Demo02ThrowMain {
    public static void main(String[] args)throws FileNotFoundException {
        readFile("c:\\a.txt");
    }
    public static void readFile(String filePath) throws FileNotFoundException{
        if("c:\\a.txt".equals(filePath)){
            throw new FileNotFoundException("the passed file is not c:a.txt");
        }
        System.out.println("passed correct file path");
    }
}
```

可以同时`throws`多个异常，如果多个异常之间是父子类关系，只需声明父类异常即可。

##### 3、try catch

自己处理异常

```java
try{
	//可能产生异常的代码
}catch(/*定义异常变量，接受try中抛出的异常对象*/){
	//异常处理逻辑
}
```

`Throwable`三个异常处理方法

```java
import java.io.IOException;

public class Demo02TryCatchMain {
    public static void main(String[] args) {
        try{
            readFile("c:\\a.tx");
        }catch(IOException ioex){
            System.out.println("捕获了异常");
            /*Throwable三个异常处理的方法
            String getMessage() 返回此throwable的简短描述
            String toString() 返回此throwable的详细消息字符串
            void printStackTrace() jvm打印异常对象，默认此方法，打印的异常信息是最全面的
            */
            System.out.println("--------------");
            System.out.println(ioex.getMessage());
            System.out.println("--------------");
            System.out.println(ioex.toString());
            System.out.println("--------------");
            System.out.println(ioex);
            System.out.println("--------------");
            ioex.printStackTrace();
        }finally{
            System.out.println("资源释放");
        }
        System.out.println("后续代码");
    }
    public static void readFile(String str)throws IOException{
        if(!str.endsWith(".txt")){
            throw new IOException("文件的后缀名不是.txt");
        }
    }
}

```

##### 4、finally

`finally`中的代码无论是否出现异常都会执行，必须搭配`try`一起使用。一般用于资源释放。

##### 5、异常处理事项

多个异常可以使用一个try多个catch来捕获处理，子类异常变量应该写在父类异常变量的上边。

也可以多个异常使用一个`catch`来捕获处理，catch后的异常变量应该是父类类型以满足接受不同异常对象。

**父类异常是什么样，子类异常就什么样（可以是父类异常的子类）。父类方法无异常，子类重写的方法内部抛出异常时，需要使用try...catch捕获**

##### 6、自定义异常类





