### 一、线程等待与唤醒

包子铺生产包子，吃货吃包子：

```java
public class Main {
    public static void main(String[] args) {
        Baozi bz = new Baozi();  // 两个线程共享对象
        Runnable r1 = new Runnable() { // 包子铺
            int count = 0;
            @Override
            public void run() {
                while (true){
                    synchronized (bz){
                        if(bz.state == true){ // 有包子
                            try {
                                bz.wait();
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }

                        if(count % 2 == 0){
                            bz.pi = "a_pi";
                            bz.xian = "a_xian";
                        }else{
                            bz.pi = "b_pi";
                            bz.xian = "b_xian";
                        }
                        count++;
                        try {
                            Thread.sleep(3000); // 模拟生产包子
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        System.out.println("product a " + bz.pi + " "+bz.xian+" bao zi");
                        bz.state = true;
                        bz.notify();  // 通知吃货可以吃了
                        System.out.println("we have already prepared bao zi, 
                                           so you can eat");
                    }
                }
            }
        };
        Runnable r2 = new Runnable() { // 吃货
            @Override
            public void run() {
                while(true){
                    synchronized (bz){
                        if(bz.state == false){  // 没有包子就等待
                            try {
                                bz.wait();
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                        bz.state = false; // 吃包子
                        System.out.println("I have eat a "+
                                           bz.pi + " "+ bz.xian + " bao zi");
                        bz.notify();  // 告诉包子铺生产包子
                        System.out.println("-----------------");
                    }
                }
            }
        };
        new Thread(r1).start();
        new Thread(r2).start();
    }
}

class Baozi{
    public String pi;
    public String xian;
    public Boolean state = false;
}

```

### 二、线程池

使用`jdk`提供的线程池

* 使用线程池的工厂类`Executors`提供的静态方法`newFixedThreadPool`生产一个指定线程数量的线程池
* 创建一个类，实现`Runable`接口，重写`run`方法，设置线程任务
* 调用`ExecutorService`中的方法`submit`，传递线程任务（实现类），开启线程执行run方法
* 调用`ExecutorService`中的方法`hutdown`销毁线程

```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadPoolMain {
    public static void main(String[] args) {
        ExecutorService pool = Executors.newFixedThreadPool(3);
        pool.submit(new RunnableImpl());
        pool.submit(new RunnableImpl());
        pool.submit(new RunnableImpl());
        pool.shutdown();
    }
}
class RunnableImpl implements Runnable{
    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName());
    }
}
```

### 三、Lambda表达式

`(<参数>)->{<代码>}`

匿名对象的内部类重写方法这种实现自己的过程代码比较冗余，可以用Lambda表达式简化。接口只有一个抽象方法。

对一个自定义类型的数组进行排序时，传统做法需要传入一个`Comparator`比较器实现类的对象，要重写`compare`方法。

```java
import java.util.Arrays;
import java.util.Comparator;

public class LambadaMain {
    public static void main(String[] args) {
        Person [] arr = {
                new Person("zhangsan", 10),
                new Person("lisi", 8),
                new Person("wangwu", 20),
                new Person("zhaosi", 15)
        };
        Arrays.sort(arr, new Comparator<Person>() {
            @Override
            public int compare(Person o1, Person o2) {
                return o1.age - o2.age;
            }
        });
        System.out.println(Arrays.toString(arr));
    }
}
class Person{
    String name;
    int age;
    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
```

使用lambda表达式后：

```
Arrays.sort(arr,(Person o1,Person o2)->{
    return o1.age-o2.age;
});
```

可以理解为直接传入一个过程，sort内部可以使用这个过程。