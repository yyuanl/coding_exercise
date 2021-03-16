### 一、字节流

#### 1、字节输出流OutputStream

输出字节流的超类（抽象类）。定义了共性的成员方法。

成员方法：

`write`写字节

`close`关闭流

`java.io.FileOutputStream`文件字节输出流：把内存数据写入到文件中。

构造方法：

`FileOutputStream(String name)`

`FileOutputStream(File file)`

#### 2、字节输入流InputStream

字节输入的超类（抽象类）。读取字节信息到内存。

成员方法：

`read`读取字节

`close`

`java.io.FileInputStream extends InputStream`

构造方法：

`FileInputStream (String name)`

`FileInputStream (File file)`

### 二、字符流

#### 1、Reader字符输入流

字符输入流顶层抽象方法

#### 2、FileReader

文件字符输入流，以字符的方式读取数据

构造方法：

`FileReader(String fileName)`

`FileReader(File file)`

#### 3、Writer字符输出流

所有字符输出流的顶层抽象方法

#### 4、FileWriter

文件字符输出流，把内存中的字符数据写入到文件

### 三、属性集

`Properties`可以将`key vlue`对持久化到文件或者从文件读取。

### 四、缓冲流

基本的输入、输出流基础上加一个缓冲区，减少字节流、字符流的IO次数。