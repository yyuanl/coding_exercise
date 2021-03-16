### 一、数据库连接池

为了复用数据库连接对象

#### 1、C3P0

#### 2、Druid

### 二、JDBCtemplate

#### 1、JDBCTemplate的方法

* `update()`执行DML语句。增删改语句。
* `queryForMap()`查询结果将结果集封装为`map`集合，列作为key，值作为map。查询结果只能是一条。
* `queryForList()`查询结果将结果集封装为`list`集合
* `query()`查询结果，将结果封装为`JavaBean`对象。
* `queryForObject`查询结果，将结果封装为对象

