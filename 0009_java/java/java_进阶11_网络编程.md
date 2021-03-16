### 一、TCP通信

#### 1、Socket类

客户端使用`Socket`类来建立一个socket

* 构造函数：

`Public Socket(String host, int port)`指定连接到服务器主机的ip地址和端口号

* 成员方法

`OutputStream getOutputStream()`返回此套接字的输出流

`InputStream getInputStream()`返回此套接字的输入流

`void close()`关闭此套接字

案例上传文件：

客户端

```java
import java.net.Socket;

public class TcpClient {
    public static void main(String[] args) throws IOException {
        FileInputStream fis = new FileInputStream("E:\\java_heima\\test_client\\1.PNG");
        Socket s = new Socket("127.0.0.1",8888);
        OutputStream os = s.getOutputStream();
        int len = 0;
        byte []buff = new byte[1024];
        while((len = fis.read(buff))!=-1){
            os.write(buff,0,len);
        }
        System.out.println("client读取文件结束");
        s.shutdownOutput();  //禁用此socket输出流，标志客户端数据写完。避免服务端read阻塞。
        InputStream is = s.getInputStream();
        while((len = is.read(buff))!=-1){
            System.out.println(new String(buff,0,len));
        }
        fis.close();
        s.close();
    }
}
```

服务端：

```java
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class TcpServer {
    public static void main(String[] args) throws IOException {
        String uploadPath = "E:\\java_heima\\test_server";
        File file = new File(uploadPath);
        if(!file.exists()){
            file.mkdirs();
        }
        ServerSocket ss = new ServerSocket(8888);
        Socket con = ss.accept();
        InputStream is = con.getInputStream();

        FileOutputStream fos = new FileOutputStream(uploadPath + "\\1.PNG");
        int len = 0;
        byte []bytes = new byte[1024];
        while((len = is.read(bytes)) != -1){
            fos.write(bytes,0,len);
        }
        OutputStream os = con.getOutputStream();
        os.write("上传成功".getBytes());
        ss.close();
        con.close();
        fos.close();

    }
}
```

服务端可以优化使用多线程完成任务。

```java
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Random;

public class TcpServer {
    public static void main(String[] args) throws IOException {
        String uploadPath = "E:\\java_heima\\test_server";
        ServerSocket ss = new ServerSocket(8888);
        while(true){
            //serverMethod(uploadPath,ss);
//            new Thread(new Runnable() {
//                @Override
//                public void run() {
//                    try {
//                        serverMethod(uploadPath,ss);
//                    } catch (IOException e) {
//                        e.printStackTrace();
//                    }
//                }
//            }).start();

            new Thread(()->{
                try {
                    serverMethod(uploadPath,ss);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }).start();
        }

    }
    public static  void serverMethod(String uploadPath,ServerSocket ss) throws IOException {
        File file = new File(uploadPath);
        if(!file.exists()){
            file.mkdirs();
        }
        //ServerSocket ss = new ServerSocket(8888);
        Socket con = ss.accept();
        InputStream is = con.getInputStream();
        String fileName = "yyl_" + System.currentTimeMillis() + new Random().nextInt() + ".png";
        FileOutputStream fos = new FileOutputStream(uploadPath + File.separator + fileName);
        int len = 0;
        byte []bytes = new byte[1024];
        while((len = is.read(bytes)) != -1){
            fos.write(bytes,0,len);
        }
        OutputStream os = con.getOutputStream();
        os.write("上传成功".getBytes());
        //ss.close();
        con.close();
        fos.close();

    }
}

```

