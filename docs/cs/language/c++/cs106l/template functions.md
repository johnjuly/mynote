#

## template functions

### writing a min function

```cpp
template<typename T>
T min(T a,T b)
//template

min<std::string>
//a function,a template instantiation

template<typename T>
T min(const T& a,const T& b){
    //使用引用避免复制一份
    return a<b?a:b;
}

```

### 如何调用模板函数

#### a:explicit instantiation

* passes the types directly,just like template classes min<int>(106,107);min<double>(1.2,3.4),template functions cause the compiletr to generate code for us

```cpp
int min(int a,int b){
    return a<b?a:b;
};
double min(double a,double b){
    return a<b?a:b
};
//compiler generated
```

* **key idea**:templates automate code generation

#### b:implicit instantiation

* lets the compiler infer the types for us,min(106,107);min(1.2,3.4);
* like auto,auto number=106;
* can be finicky
  * ex.1:min("jacob","fabio");
    type:const char*,指针比较？
    解决方法：

    ```cpp
    template<typename T>
    T min(const T& a,const T&b){
        return a<b?a:b;
    }

    min<std::string>("jacob","fabio");

    //const char* converts to std::string!!!

    ```

  * ex.2:参数类型不严格匹配
   解决方法1： 显示实例化,`min<double>(106,3.14)`
   解决方法2：让模板更加灵活，

    ```cpp
    template<typename T,typename U>
    auto min(const T& a,const U&b){
        return a<b?a:b;
    }

    min(106,3.14);

    //让编译器来思考auto是什么……

    ```

### write a find function templated

* find function in the stl ,part of `<algorithm>`header

## concepts

> a name set of constraints，greatly improve compiler errors

* compiler only finds the error ***after*** instantiation,min函数 模板类T必须要有操作符<。

* put constrains on templates,compiler should not instantiate a template unless all constraints are met

```cpp
template<typename T>
T min(const T& a,const T &b)
//T must have operator <
template<typename T>
struct set;

template<typename It,typename T>
It find(It begin,It end,const T&value)
//it must be an iterator type

```

### a **comparable** concept

```cpp
template<typename T>
concept Comparable =requires(const T a,const T b){
    {a<b}->std::convertible_to<bool>;
};
//using

template<typename T> requires Comparable<T>
T min(const T& a，const T& b);
//更简洁的版本

template<Comparable T>
T min(const T& a，const T& b);


//iterator concepts
template<std::input_iterator It,typename T>
It find(It begin,It end,const T& value);

int idx=find(1,5,3);
//编译器报错：int does not satisfy input_iterator

```

### recap

* 使用concepts 原因
  * better compiler error messages
  * better ide support (intelisense/autocomplete)
* concepts are still a new feature
  * stl does not yet support them fully

## variadic templates

> build functions that accept a variable number of argument

* templates + recursion

### 使用vector来写比小函数

```cpp
template<Comparable T>
T min(const std::vector<T>& values){
    if(values.size()==1)return values[0];
    //base case

    const auto& first =value[0];
    std::vector<T> rest(++values.begin(),values.end());
    auto m= min(rest);
    return first<m?first:m;
    //recursive case
}

```

* 一些问题
  * it recursively copies the vector(can avoid with wrapper function)
  * must allocate a vector for every call(unavoidable overhead)
* 其他方法：函数重载

### variadictemplates

```cpp
template<Comparable T>
T min(const T& v){return v;}
//base case,needed to stop recursion

template<Comparable T,Comparable...Args>
//vataiadic template:matches 0 or more types
T min(const T& v,const Args&...args){
    //parameter pack:0 or more parameters
    auto m=min(args...);
    //pack expansion:replaces ...args with actual parameters
    return v<m?v:m;
}



```

!!! example
    a single call to min(2,7,5,1)generated the following functions
    ```cpp
    min<int,int,int,int>   //T=int,Args=[int,int,int]
    min<int,int,int>       //T=int,Args=[int,int]
    min<int,int>           //T=int,Args=[int]
    min<int>               //T=int
    ```

### variadic types don't have to be the same

!!! example
    a **printf**-style function :
    `format("Queen{},Protector of the { } Kingdoms", "Rhaenyra" ,7)`;//string,int
    the {}'s get filled in with arbitary number/type of arguments

* format 实施

```cpp
void format (const std::string& fmt){
    std::cout<<fmt<<std::endl;

}

template<typename T, typename...Args>
void format(const std:: string& fmt,T value,Args...args){
    auto pos =fmt.find("{}");
    if(pos==std::string ::npos) throw std:: runtime_error("Extra arg");
    std::cout<<fmt.substr(0,pos);
    std::cout<<value;
    format(fmt.substr(pos+2),args...);
}



```

!!! example "instantiate format "
    ```cpp
    format("Lecture {}: {} (Week {})", 9, "Templates", 5);//T=int,Args=[std::string, int]
    format<int, std::string, int>()
    //T=std::string,Args=[int]
    format<int>()
    //T=int,Args=[]
    format()
    //base case
    ```

### vtrecap

* compiler generates any number of overloads using recursion,which allows us to support any number of function parameters.instantiation happens at compile time

## template metaprogramming

> run code at compile time,turing complete

!!! example "TMP Basics:Factorial"
    ```cpp
    template<>//base case:a template specialization for N=0
    struct Factorial<0>{
        enum{value =1};
        //enum: a way to store a compile-time constant
    };

    template<size_t N>
    struct Factorial{enum {value=N*Factorial<N-1>::value};};//complie -time recursion
    std::cout<<Factorial<7>::value<<std::endl;

    ```

!!! example "fibonacci"
    ```cpp
    template<>
    struct fibonacci<0>{
        enum{value=0};
    };
    template<>
    struct fibonacci<1>{
        enum{value=1};
    };
    template<size_t N>
    struct fibonacci{
        enum{value=fibonacci<N-1>::value+fibonacci<N-2>}::value
    };

    ```

### how is tmp used in the real world

* baking results into an executable at compile time(e.g.factorial)
* optimizing matrices/trees.other mathmatics structures
* policy-based design:passing around behaviour through templates
* boost MPL library

### TPL allows programming for types

```cpp
using namespace boost;

using Move =mpl::vector<MoveUp,MoveRight>;//vector of types
using MoveRotate = mpl::push_back<Move,Rotate45>::type;

template<typename Transformation>
void apply(Objects&)；

apply<Move>(object);
apply<MoveRotate>(object);



```

### readlable code  using **consexpr**/**consteval**

```cpp
constexpr size_t factorial(size_t n){
    if(n==0) return 1;
    return n*factorial(n-1);
}
//可在运行时计算

consteval size_t factorial(size_t n){
    if(n==0) return 1;
    return n*factorial(n-1);
}
//必须在编译时计算



```

## 什么时候使用模板

* want the compiler to automate a repetitve coding task:template functions,variadic templates
* want better error messages:concepts
* don't want to run until runtime:tpl,constexpr/consteval
