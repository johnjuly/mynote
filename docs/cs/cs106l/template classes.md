#

## review

* a class bundles data and methods for an object together
* header file contains **interface** ,**declaritions**
* cpp contains **implementation**,**definitions**
* what is *this*? a **pointer** to the current class instance

## template classes

> how can we generalize across different types?

### 历史

之前使用宏定义

```cpp
#define GENERATE_VECTOR(MY_TYPE)//preprocessor macro runs before compile
class MY_TYPE##Vector{
    public:
        MY_TYPE& at(size_t index);
        void push_back(const MY_TYPE& elem);
    private:
        MY_TYPE*elems;
        size_t logical_size;
        size_t array_size;
}



#include"grandmas_template.h"
GENERATE_VECTOR(int)//code generation

intvector v1;
v1.push_back(5);

```

#### 宏的问题

* clunky syntax
* hard to type check
* 忘记叫宏了或者不止叫一次

## key idea:templates automate code generation

* a type is a template instantiation

* typename is interchangeable

```cpp
template<typename T>
class vector{};

template<size_t N>
class sizetemplate{};
sizetemplate<5> s;

template<bool B>
class booltemplate{};
booltemplate<true> b;

template<typename T,std::size_t N>
struct std::array{```};

//an array of exactly 5strings
std::array<std::string,5> arr;

//使用数组而不是向量的原因是避免堆分配，编译器会exactly知道一个数组array<string,5>需要多大的空间,成为栈分配
```

### 一些奇怪点

1. msutcopytemplate<…>syntax in.cpp
2. .h must include .cpp at bottom of file.与模板生成代码实现如何在编译器以及链接器中实现有关
(non-template classes :the .cpp file includes the .h file)when instantiating templates, the compiler must have full knowledge of both the declaration (this file)and the definitions (.cpp file) of the template
https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

3. typename is the same as class

## const correctness

* const 函数 不修改对象
* inside a const method,this has type const vector<\T>*

### the const interface

* objects marked as const can only make use of the const interface
* the const interface are the functions that are const in an object


### const overloading

two versions of *at* method
one version gets called for const instances,another gets called for non-const instances

```cpp
template<class T>
class vector{
public:
    const T& at(size_t index) const;
    T& at(size_t index);
};

return elems[index];
```

### implementing findelement

```cpp
T& findelement(const T& value);
const T& findelement(const T& value) const;

template<typename T>
T& vector<T>::findelement(const T& value){
    for(size_t i=0;i<logical_size;i++)
    {if(elems[i]==elem)return elems[i];}
    throw std::out_of_range("element not found")
}

const version thesame
```

* casting:the process of converting one type to another
* const_cast allows us to cast away the const-ness of a variable
  * usage:const_cast<target_type>(expression)

```cpp
template<typename T>
const T&vector<T>::findelement(const T&value) const{
    return const_cast<vector<T>&>(*this).findelemnt(value);
}
//不再冗余？
```

* const_cast casts away the const
* *this dereferences a **const vector<\T>\*** ,giving us a const-ref
* vector<\T>& is a non-const reference .the type we would like

#### when to use const_cast?

* never?
* const_cast makes an entire object mutable

### *mutable* keywords

* circumvents const protections

```cpp
struct mutablestruct{
    int donttouchthis;
    mutable double icanchange;
};

const mutablestruct cm;
//cm.donttouchthis=42;//notallowed,cm is const
cm.icanchange=3.14;


```

* mutable example:storing debug info

```cpp
struct cameraray{
    Point origin;
    Direction direction;
    mutable color debugcolor;
}

void renderray(const cameraray&ray){
    ray.debugcolor=color.yellow;
}

```

## recap

* template classes generalize logic across types
* const makes an entir object read-only
* mark methods const when they don't modify the object
* const_cast and mutable can circumvent compiler in rare cases

