### 一、File类

`java.io.File`文件和目录路径的抽象。File类与系统无关。

#### 创建一个文件/文件夹

#### 删除文件/文件夹

#### 获取文件/文件夹

#### 判断一个文件/文件夹是否存在

#### 判断一个文件/文件夹是否存在

#### 对文件夹进行遍历

#### 获取文件的大小



file文件

directory文件夹/目录

path路径

File静态成员：

* `pathSeparator`路径分隔符，windows是;  Linux是:
* `separator`文件名称分隔符.

输出路径下的所有`.java`文件

```java
import java.io.File;

public class Main {
    public static void main(String[] args) {
        String dir = "E:\\java_heima";
        getAllfile(new File(dir));
    }
    public static void getAllfile(File dir){
        for(File e:dir.listFiles()){
            if(e.isDirectory()){
                getAllfile(e);
            }else{
                String pathName = e.getName();
                if(pathName.endsWith(".java")){
                    System.out.println(e.getPath());
                }
            }
        }
    }
}
```

#### Filter、FilternameFilter过滤器

`FileFilter`接口用于File对象的过滤器。

`File[] listFiles(Filter filter)`过滤文件的重载方法

`File[] listFiles(FilenameFilter filter)`过滤文件名的重载方法

需要重写过滤器的`accept`抽象方法

```java
import java.io.File;
import java.io.FileFilter;

public class Main {
    public static void main(String[] args) {
        String dir = "E:\\java_heima";
        getAllfile(new File(dir));
    }
    public static void getAllfile(File dir){
//        File [] list = dir.listFiles(new FileFilter() {
//            @Override
//            public boolean accept(File pathname) { //保留文件夹和.java文件
//                return pathname.isDirectory() || pathname.getName().endsWith(".java");
//            }
//        });
        File [] list = dir.listFiles(
                (File pathname)->pathname.isDirectory() || 					                         					  pathname.getName().endsWith(".java")
        );
        for(File e:list){
            if(e.isDirectory()){
                getAllfile(e);
            }else{
                System.out.println(e.getPath());
            }
        }
    }
}
```

