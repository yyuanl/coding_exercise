#### 一、MySQL的使用

* 启动：`net start 服务名`
* 停止：`net start 服务名`
* 客户端登录：
  * 自带的客户端（只能以root身份进入）输入密码即可
  * 连接本机服务器命令行：`mysql -u<用户名> -p<密码>`
  * 连接远程数据库命令行：`mysql -h<ip地址> -P<端口号> -u<用户名> -p<密码>`

#### 二、SQL语句

##### 1、分类

* DDL：定义数据库对象：库、表、列。`create/drop/alter`
* DML：数据操作语言。增删改：`insert/update/delete`
* DCL：数据控制语言。定义访问权限和安全级别。
* DQL：数据查询语言。`select`

##### 2、查询

###### （1）基础查询

基础查询：`select 查询列表 from 表名`
* 查询的结果表， 是一个虚拟表
* 执行顺序：先`from 子句`，后`select`
* `concat()`来拼接字段：`SELECT CONCAT(first_name,last_name) AS "xingming" FROM employees`
* `distinct`关键字去重：`SELECT DISTINCT department_id FROM employees`
* desc查看表结构
* `ifnull`函数判断自读值是否为`NULL`：`ifnull(commission_pct, '空')`表示如果`commission_pct`为空则显示为‘空’，否则显示其本身值

###### （2）条件查询

```mysql
select 查询列表
from 表明
where 筛选条件;
```

* 执行顺序：from子句、where子句、select子句

* 按照关系表达式筛选：>、<、>=、<=、=、<>、!=

* 按逻辑表达式筛选：and、or、not

* 模糊查询：like、in、between and、is null

  * `like`：一般和通配符搭配使用，对字符型数据进行部分匹配查询。

    `_`代表任意单个字符

    `%`代表任意多个字符

    **转义字符**：`select * from employees where last_name like '_$_%' escape '$'`

  * `in`:用于查询某字段的值是否属于指定的列表元素

  * `between and`：判断某个字段的值是否介于xx之间

  * `is null/is not null`判断是否为NULL

  * `<=>`安全等于，即能判断普通内容，又能判断NULL

一些例子：

查询工资不在5000到12000的员工姓名和薪资：

```mysql
SELECT `last_name`,`salary`
FROM `employees`
WHERE NOT(`salary` BETWEEN 5000 AND 12000);
```

###### （3）排序查询

```mysql
select 查询列表
from 表名
【where 筛选条件】
order by 排序列表
```

执行顺序：from-where-select-order by。因此可以再order by后面使用别名，而不能再where中使用别名。

* 排序列表可以是单个字段、多个字段、表达式、函数、列表、以及以上组合

* 升序：`asc`，降序`desc`

  ```mysql
  select *
  from employees
  where employee_id > 100
  order by salary asc
  ```

###### （4）常见函数

* 字符函数

  * `concat`拼接字符

  * `length`获取**字节**长度

  * `char_length`获取**字符**长度

  * `substring(str,<起始索引>,<截取长度>)`截取字串。起始索引从1开始。截取长度可以不写，默认到结尾。

  * `instr`获取字符第一次出现的索引：`instr("gfdafdfdf","daf")`

  * `trim`去前后指定的字符，默认去空格

    ```sql
    select trim(" abc ");
    select trim('x' from "xxxxab cxxxx"); // ab c
    ```

  * `lpad/rpad`左右填充字符：`select lap("xxx", 3, 'a')  //aaaxxx`

  * `upper/lower(<str>)`

  * `strcmp(<str1>,<str2>)`比较两个字符串大小

  * `left/right(<str1>,<n>)`左/右截取n个字符的字串

* 数学函数

  * `ABS`求绝对值
  * `CEIL`向上取整，返回大于等于参数的最小整数
  * `FLOOR`向下取整，返回小于等于参数的最大整数
  * `ROUND`四舍五入
  * `TRUNCATE(<n1>,<n2>)`保留小数点后n2
  * `MOD`取余

* 日期函数

  * `NOW()`获取当前时间
  * `CURDATE()`获取当前日期
  * `CURTIME()`获取当前日期
  * `DATEDIFF(<date1>,<date2>)`date1 - date2之差，天数
  * `DATE_FORMAT("1998-7-16","%Y年%m月%d日 %H小时%i分钟%s秒")`格式化日期
  * `STR_TO_DATE("3/15 1998","%m/%d %Y")`按照格式取解析字符串，返回一个日期

* 流程控制函数

  * IF函数

    ```sql
    select if(commission_pct is NULL, 0, salary*12*commission_pct) as 奖金
    from employees;
    ```

  * CASE函数

    情况1，类似switch语句

    ```
    CASE 表达式
    WHEN 值1 THEN 结果1
    WHEN 值2 THEN 结果2
    ...
    ELSE 结果n
    END
    ```

    情况2，类似多重IF语句

    ```sql
    CASE
    WHEN 条件1 THEN 结果1 
    WHEN 条件2 THEN 结果2
    ELSE 结果2
    ...
    END
    ```

###### （5）分组（聚合）函数

统计一组数据，得到一个值

* `sum()`求和
* `avg()`求平均值
* `max()`求最大值
* `min()`求最小值
* `count()`求非空字段的个数
  * `select count(*) from employees`查询行数
  * `select count(1) from employees`也是查询行数。给表新添加一列，没条记录的数据就是1
  * 常搭配`distinct`去重统计

###### （6）分组查询

语法

```sql
select <查询列表>
from <表明>
where <筛选条件>
group by <分组字段>
```

* 查询列表往往时分组函数，和分组字段

```sql
select sum(salary), department_id
from employees
group by department_id
```

* **分组后筛选用`having`关键字**（`group by`后面），基表是分组后的结果集。

```sql
#查询哪些部门员工个数大于5
SELECT COUNT(*) , department_id
FROM employees
GROUP BY department_id
HAVING COUNT(*)>5;
```

**分组函数只能放在`having `后面**

**分组、筛选后还能进行排序**

执行顺序：from-where-group by-having-select-order by

###### （7）连接查询

* 内连接
  * 等值连接

    ```sql
    SELECT COUNT(department_name), city
    FROM locations l, departments d
    WHERE d.`location_id`=l.`location_id`
    GROUP BY city;
    ```

  * 非等值连接

  * 自链接

* 外连接

  ​	主表每条记录去匹配从表，从表中有符合条件的则显示，没有则显示NULL。一般用于查询主表中有，从表中没有的记录。左连接，左边为主表。有连接，右边为主表。

  ```sql
  select 查询列表
  from 表1 别名
  left(right) outer join 表2 别名
  on 连接条件
  where 筛选条件
  ```

  

  