#

## the type system

### c++is a **statically typed**language：

* 在源代码中每一个变量必须声名自己的类型
* 声明之后类型不可以改变

```c++
void foo(std::string c){
    int d=106;
    d="hello world";//编译错误
}//每个变量，参数，返回类型需要指明

对比 python a dynamically typed language

···py
def foo(c):
  d=106
  d="hello world"

```

### 静态类型的原因

* 给编译器更多额外的有关变量的信息，分配内存给他们时更有效
* 编译器 额外的性能优化在机器码中；消除推断类型运行时间

## structs

* extend the type system

### 声名加初始化

uniform initialization

```c++

IDCard printIDCard() {
    IDCard id { "Miguel de Cervantes", 1605, "miguel@quijote.edu" };
    return id;
}

IDCard printIDCard() {
    return { "Miguel de Cervantes", 1605, "miguel@quijote.edu" };
}//简化版本


```

### std::pair

不用重新建一个结构体 使用一次的情况
一个模板 需要列出类型尖括号里std::pair<std::string, size_t>

设计一个函数 找到一个字符串中某个字符的第一个和最后一个索引
无pair

```c++
struct characterindices{
  size_t first;
  size_t last;
};

characterindices find(std::string str.char c){
  size_t first,last=std::string::npos;
  return {first,last};
}
//std::string::npos,特殊值 指字符串中不存在的位置
```

有pair

```c++
​std::pair<size_t, size_t>‍ find(std::string str, char c) {
  size_t first, last = std::string::npos;
  /* Code to find the first and last indices */
  return { first, last };
}

```

```c++
std::string marquez ="Colonel Aureliano Buendia was to remember that distant afternoon";

std::pair<size_t,size_t> result=find(marquez,"a");
std::cout<<result.first<<std::endl;
std::cout<<result.second<<std::endl;
```

## modern typing

### type aliases with *using*

避免麻烦 别名 类似于typedef

using QuadraticSolution=std::pair<bool,std::pair<double,double>>

### type deduction with *auto*


