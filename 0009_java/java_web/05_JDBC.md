### 一、基本概念

官方定义的一套操作关系型数据库的接口。各个数据库厂商取实现这套接口，提供数据库驱动jar包。

### 二、快速入门

* 导入驱动jar包：复制到项目目录，add as library

#### 1、`DriverManager`

驱动管理对象

* 注册驱动

  写代码使用`Class.forName("com.mysql.jdbc.Driver");`内部调用`static void registerDriver(Driver driver)`

* 获取数据库连接

  `static Connection getConnection(String url, String user, String password)`

  url:`jdbc:mysql://<ip>：<端口号>/<数据库名称>`

#### 2、`Connection`

* 获取执行sql执行对象
  * `Statement createStatement()`
  * `PreparedStatement PreparedStatement()`
* 管理事务
  * 开启事务：`void setAutoCommit(boolean autoCommit)`参数设置，开启事务。**执行sql之前开启**
  * 提交事务：`commit()`。**所有操作结束时提交事务**
  * 回滚事务:`rollback()`。**出现异常时进行事务回滚**

#### 3、`Statement`

一个接口

执行静态sql语句并返回生成结果的对象

* 执行sql

  * `boolean execute(String sql)`

  * `int executeUpdate(String sql)`执行DML（insert、update、delete）语句、DDL（

    create、alter、drop）语句。返回值是**影响的行数**。返回值大于0则执行成功。

  * `ResultSet executeQuery(String sql)`执行DQL（select）语句。

#### 4、`ResultSet`

* `next()`游标向下移动一行
* `getXxx(<参数>)`获取数据，`Xxx`代表数据类型，如`getInt()`、`getString()`
  * <参数>:如果参数是`int`则代表列的编号，从1开始；如果是`String`则代表列的名称
* **使用步骤**：
  * 游标向下移动一行
  * 判断是否有数据
  * 获取数据

案例

```java
import java.sql.*;

public class JDBCMain {
    public static void main(String[] args) {
        Connection conn = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            String sql = "SELECT last_name, employee_id,salary " +
                    "FROM employees " +
                    "WHERE employee_id BETWEEN 100 AND 150";
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/myemployees", "root", "123456");
            statement = conn.createStatement();
            resultSet = statement.executeQuery(sql);
            while(resultSet.next()){
                System.out.println(
                        resultSet.getString(1) + " "
                        + resultSet.getString(2) + " "
                        + resultSet.getString(3));
            }

        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }finally {
            if(resultSet != null){
                try {
                    resultSet.close();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
            if(statement != null){
                try {
                    statement.close();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
            if(conn != null){
                try {
                    conn.close();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
        }
    }
}
```

使用JDBC工具类简化代码

```java
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.sql.*;
import java.util.Properties;

class JDBCUtils{
    static String url;
    static String user;
    static String passWord;
    static String driver;
    static {
        Properties pro = new Properties();
        // 获取src路径下文件的方式：ClassLoader类加载器
        ClassLoader classLoader = JDBCUtils.class.getClassLoader();
        URL res = classLoader.getResource("pro.properties");
        String path = res.getPath();
        try {
            pro.load(new FileReader(path));
            url = pro.getProperty("url");
            user = pro.getProperty("user");
            passWord = pro.getProperty("passWord");
            driver = pro.getProperty("driver");
            Class.forName(driver);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection(){
        try {
            return DriverManager.getConnection(url,user,passWord);
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return null;
    }

    public static void close(ResultSet resultSet,Statement statement,Connection conn){
        if(resultSet != null){
            try {
                resultSet.close();
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        if(statement != null){
            try {
                statement.close();
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        if(conn != null){
            try {
                conn.close();
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
    }
}

public class JDBCMain {
    public static void main(String[] args) {
        Connection conn = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            String sql = "SELECT last_name, employee_id,salary " +
                    "FROM employees " +
                    "WHERE employee_id BETWEEN 100 AND 150";
            conn = JDBCUtils.getConnection();
            statement = conn.createStatement();
            resultSet = statement.executeQuery(sql);
            while(resultSet.next()){
                System.out.println(
                        resultSet.getString(1) + " "
                        + resultSet.getString(2) + " "
                        + resultSet.getString(3));
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }finally {
            JDBCUtils.close(resultSet,statement,conn);
        }
    }
}
```

#### 5、`PreparedStatement`

**解决sql注入问题**

预编译SQL：参数使用？占位符

```java
public boolean Logon2(String name, String password){
        if(name == null || password == null){
            return false;
        }
        Connection conn = null;
        PreparedStatement statement = null;
        ResultSet res = null;
        String sql = "SELECT * FROM yylUser WHERE username= ? AND PASSWORD=?";
        try {
            conn = JDBCUtils.getConnection();
            statement = conn.prepareStatement(sql);
            statement.setString(1,name);
            statement.setString(2,password);
            res = statement.executeQuery();
            return res.next();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return false;
    }
```