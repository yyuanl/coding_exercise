### 一、线程

#### 1、Thread

创建一个线程

```java
public class MyThread extends Thread{
    @Override
    public void run() {
        for(int i = 0; i < 20;i++){
            System.out.println("mythread");
        }
    }
}
public class Demo03Main {
    public static void main(String[] args) {
        MyThread myThread = new MyThread();
        myThread.start();
    }
}
```

* 获取线程名称

`Thread`中`getName`方法

```java
public final String getName();
```

或者使用`Thread.currentThread()`获取当前正在执行的线程对象的引用，在通过引用获取线程名称

* `public static void sleep(long millis)`

#### 2、实现`Runnable`接口创建线程

```java
public class Demo03Runnable implements Runnable {
    @Override
    public void run() {
        for(int i = 0; i < 20;i++){
            System.out.println("mythrad " + i);
        }
    }
}
public class Demo03Main {
    public static void main(String[] args) {
        Demo03Runnable myRunalbe = new Demo03Runnable();
        Thread t = new Thread(myRunalbe);
        t.start();
        for(int i = 0; i < 20; i++){
            System.out.println("main thread "+i);
        }
    }
}
```

* 该方法避免了单继承的局限性，实现`Runnable`接口可以继承其他的类
* 增强了程序的扩展性。任务的设计和线程的开启分离。

以上创建线程都可以协程匿名内部类方式改写

### 二、线程同步

#### 1、同步代码块

**同步锁/对象锁**，只有某个线程持有对象锁，才能执行同步代码块，执行完成之后释放对象锁，多个线程再次竞争该锁获取同步代码块的执行权。

```java
synchronized(/*锁对象，多个线程共享*/){
	//访问共享数据的代码块
}
```

代码实例

```java
public class Demo05ThreadSyn {
    public static void main(String[] args) {
        Runnable r = new Runnable() {
            private int shared_data = 100;
            Object obj = new Object();
            @Override
            public void run() {
                while(true){
                    synchronized (obj){
                        if(shared_data > 0){
                            try {
                                Thread.sleep(100);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                            System.out.println(Thread.currentThread().getName() 
                                               + " visit "+shared_data);
                            shared_data--;
                        }
                    }
                }

            }
        };
        new Thread(r).start();
        new Thread(r).start();
    }
}
```

#### 2、同步方法

​	把访问共享数据的代码放到一个方法中，用`synchronized`修饰该方法。锁对象就是实现类对象`new Runnable()`，也就是`this`

```java
public class Main {
    public static void main(String[] args) {
        Runnable r = new Runnable() {
            private int shared_data = 100;
            Object obj = new Object();
            @Override
            public void run() {
                while(true){
                    synMethod();
                }
            }
            private synchronized void synMethod(){
                if(shared_data > 0){
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(Thread.currentThread().getName() + 
                    					" visit "+shared_data);
                    shared_data--;
                }

            }
        };
        new Thread(r).start();
        new Thread(r).start();
    }
}
```

**如果同步方法时静态的，此时锁对象时本类的class属性-->class文件对象（反射）**

```java
public class RunnableImpl implements Runnable{
    private static int sharedDate = 100;
    @Override
    public void run() {
        while(true){
            synMethod();
        }
    }
    private static synchronized void synMethod(){
        if(sharedDate > 0){
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(Thread.currentThread().getName() + " visit "+sharedDate);
            sharedDate--;
        }
    }
}
public class Main {
    public static void main(String[] args) {
        RunnableImpl r = new RunnableImpl();
        new Thread(r).start();
        new Thread(r).start();
    }
}
```

#### 3、锁机制

在需要同步的地方上锁和释放锁

```java
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    public static void main(String[] args) {
        Runnable r = new Runnable() {
            private int shared_data = 100;
            Object obj = new Object();
            Lock l = new ReentrantLock();
            @Override
            public void run() {
                while(true){
                    synMethod();
                }
            }
            private  void synMethod(){
                l.lock();
                if(shared_data > 0){
                    try {
                        Thread.sleep(100);
                        System.out.println(Thread.currentThread().getName() 
                                       + " visit "+shared_data);
                    	shared_data--;
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }finally{
                        l.unlock();//放在finally中。无论是否异常都释放锁对象
                    }
                }
            }
        };
        new Thread(r).start();
        new Thread(r).start();
    }
}
```

### 三、线程状态

共有六种状态

* Timed Waiting

* Blocked
* Waiting

无限等待状态。等待另外一个线程唤醒。线程之间的通信。等待线程和通知线程要保证同步。

等待与唤醒案例

```java
public class Main {
    public static void main(String[] args) {
        Object obj = new Object(); // 锁对象
        new Thread(){ // 等待线程
            @Override
            public void run() {
                synchronized (obj){ // 同步
                    try {
                        obj.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(Thread.currentThread().getName() 
                                       + "被唤醒了，执行wait后代码");
                }
            }
        }.start();
        new Thread(){  //发起唤醒线程
            @Override
            public void run() {
                try {
                    Thread.sleep(5000);  // 模拟生产
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                synchronized (obj){
                    System.out.println("5秒之后 " + Thread.currentThread().getName() 
                                       + " 线程开启通知");
                    obj.notify();
                }
            }
        }.start();
    }
}
```

`wait`可以传入一个毫秒的参数，表示线程在一定毫秒后自动进入runable状态。

`nofityAll`可以唤醒在此监听器上的所有线程

