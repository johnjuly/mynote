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

#### a:explicit instantiation:

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

## concepts

## variadic templates

> build functions that accept a variable number of arguments

## template metaprogramming

> run code at compile time
