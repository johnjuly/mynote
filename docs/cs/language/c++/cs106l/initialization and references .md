#

## 对象的初始化

三个方法

### direct initialization c++98

* 依赖 *=* 或 *()*
* 适用于built in typed
* 如 int foo=2.0 缺点：导致 narrowing conversion  :编译器隐式转换


### uniform initialization (C++11)

* 使用于所有类型 包括自己定义的
* consistent type-safe
* using {}
* 按顺序

### strutured binding c++17

* initialing variables from data structure with size known at compile-time

```c++
std::tuple<std::string,std::string,std::string> getclassinfo(){
    std::string classname="cs106l";
    std::string location="online";
    std::string language="c++";
    return{classname,location,language};

}

int main(){

    auto [classname,location,language]=getclassinfo();
    std::cout<<"join us"<<location<<;
    return 0;
}

```

* 语法：auto [var1,var2,···，varn]=expression;
* the expression =a data structure whose size is always known at compile time
* vector 的大小不确定（动态分配）故不可以用，the std::vector data structure does not have a known size at compile time



### example usage with c++ data structure

#### vector

#### map

* 获得map元素
std::map<std::string,int>ages{
    {"alice",25},
    {"bob",30},
    {"charlie",35}
};

ages["alice"];
ages.at("bob");


* 优点：
  * ubiquitous,works for all objects in c++
  * enforces type-safey disallowing narrowing-conversions
* 缺点：
  * 与uniform initialization重载冲突

## 引用

rich memory semantics core: the idea of reference

definition:
an alias to something that already exists in memory
using &

