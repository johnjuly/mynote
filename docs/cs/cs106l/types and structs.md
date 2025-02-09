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