# 介绍

## 第一部分 基础

* sql是一门 十分高级的语言：做什么 而不是 怎么做；
* 数据库管理系统figures out 最好的执行查询的方法？ *查询优化*
* useage:
  * **define** database structure
  * **query** a database;
  * **update** ;
* 包括：
  * **ddl**:定义数据库结构
  * **dml**： 查询与更新
* ； 结束

### ddl :data define language

* **create**:
  1. **table**:define table name attributes,attributes'type
  2. **view**: user view of data;
  3. **index**: 指定的属性上建索引

* **drop**:

  1.
  **table**:delete table,attributes and values
  2. **view**
  3. **index**

* alter :改变属性值（一些）

### dml :data manipulation language

!!! note

    insert ;delete;update;select from where;增删改查

### 定义一个关系模式

* 建表create table name(list of elements);
  **elements**:
    1. 属性和他们的类型
    2. 键的声明
    3. 约束

### 基本类型

  char(n);varchar(n);int;smallint;numeric(p,d);real,double precision

### 删除数据库对象

* `drop` : database,table,view,index,trigger;

* `delete from`

### 改变列

> 增加或者删除关系的一个属性

* 使用 `alter table r add/drop <column>`
* 栗子：

    ```sql
    alter table bars add phone char(16) default 'unlisted'
    

    alter table bars drop column license;

    ```

### 一些习题：

![alt text](image-2.png)
b
![alt text](image-3.png)
a 男是字符，引号，故不选b


## 实体完整性

### 键的声明

|键名|区别1|2  |
|---|---|---|
| **`primary key`**|只能有一个|不可为空值|
 **`unique`**|可有多个|可为空|

> 一些dbms有制造自己的区别，例如会为主键建索引（加快查询），而不是unique

两者的声明分为两类：
  
  * 单值：放在属性类别声明的后边 `name char(20) unique`

  * 多个值： **只能如此**another element放在后边;单值也适用`unique(bar,beer)`


### 一些题


![alt text](image-9.png)
c

注意不同
![alt text](image-10.png)
abc

### 外键

#### 表达
  
  同样两种方式：

  1. 一个：在属性定义时，`references <relation>(<attribute>)`
  2. 作为模式的一个元素：
  `foreign key (<list of attributes>) references <relation> (<attributes>)
  `

```sql
create table beers{
    name char(20) primary key,
    manf char(20)
};
create table sells(
    bar char(20),
    beer char(20),
    price real,
    foreign key (beer) references beers(name)
);

```

得到
![alt text](image-4.png)


  !!! note

    参照的属性必须被声明为主键或者unique(唯一性)





![alt text](image-11.png)
bc

![alt text](image-12.png)
ac

![alt text](image-13.png)
acd

#### 维护引用完整性

> 当数据库被更新时，三个方式

##### 1. Default 缺省

  拒绝更新，当违反引用完整性时

#### 2. cascade级联 

  直观上，**引用属性**（**源**）的改变 被仿造 到**外键**（**目的**） 上
  
  删除：
  ![alt text](image-5.png)
  更新：
  ![alt text](image-6.png)





#### 3.set NULL

  删除：
  ![alt text](image-7.png)
  更新：
  ![alt text](image-8.png)

### 其他对属性的声明



* not null 
* default 
* check 
  * 属性
  ```sql
  create table sells(
    bar char(20),
    beer char(20) check (beer in (select name from beers)),
    price real check (price <=5.00)
  );
  
  ```
  check on beer 像 外键约束，只是： **更新****插入**时才会调用，**删除** **更新** 不会调用


  * 元组


  ```sql
  %只有joe的酒吧可售超过5美元的啤酒
  create table sells(
    bar char(20),
    beer char(20),
    price real,
    check(bar='Joe"s Bar' OR price <= 5.00>)
  );

  alter table sells add check(bar='Joe's Bar or beer<>'Miller'');



  ```


## 第三部分 

