#

## motivation

why should we use operators at all?

> operators allow you to convey meaning about types that functions don't


* what must be true of a type T for us to be able to use min?
    * T should have an **ordering relationship** that makes sense.
    * T should represent something comparable,ordered concept,where a **minimum can be logically determined**


* how do operators work with classes>?
  * like declare a fun in a class,declare an ooperator's functionality
  * 使用时就像常规的函数或者操作
  * 与函数重载一样。if we give the same name,it will override the operator's behavior

## 不可以重载的操作符

* scop resolution : ::
* ternary : ?
* member access: .
* pointer to member access: .*
* object size ,type,and casting:sizeof(),typeid(),cast()


## 两种重载方式

1. member overloading
  * declares the overloaded operator within the scope of your class

2. non-member overloading
  * declare outside
  * define both the left and right hand objects as parameters


### non-member overloading

preferred by stl,more idiomatic c++
**reasons**
* allows for the left hand side to be a non class type
* allows us to overload operators with classes we donot own

`bool operator < (const stanfordid& lhs,const stanfordid &rhs);`
对比
`bool stanfordid::operator < (const stanfordid &rhs) cosnt {};`
!!! note
    左右操作数都作为参数传进了函数里

### 关于成员变量

成员操作符重载可以访问this->and 类中的变量

**freind**keywoed 可以让非成员函数/类访问另一个类的private information
* 如何使用？
在头文件中声明重载函数为freind

## rules and philosophies

* because operators are intended to convey meaning about a type,the meaning should be obvious
* the operators that we can define are oftentimes arithmetic optors.the functionality should be reasonably similar to their corresponding operations
* if the meaning is not obvious,define a func
**known as the Principle of Least Astonishment(PoLA)**

## in general

* good practices like the rule of contrariety
* define ==  != `return !(*this==other)`

## <<

* a lot of flexibility 