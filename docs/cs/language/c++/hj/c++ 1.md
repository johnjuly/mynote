# 简介

以class 为一个单元
两种分类
有无pointer
基于对象与面向对象 对象之间有关联

## c++演化

c++98(1.0)
c++11(2.0)

语言+**标准库**

百科全书 c++primer
the c++ programming language(语言)
effective c++

the c++ standard library
stl源码剖析

* complex
* string 其实是一个指针
object based:
object oriented

## 3构造函数

inline 函数若在类定义自动成为inline函数 代码量少

访问级别：（access level）
public: 让外界调用函数 private:data&函数
protected:
可交错
构造函数

* 没有返回类型
* 默认实参
* 初始化列表（非赋值！不写在函数里）第一阶段，第二阶段才是赋值，放弃了初始化阶段
complex(double r=0,double i=0)
  : re(r)，im(i)
{}
* 不带指针的类可不用析构函数
* 构造函数可以有很多个 重载overloading很多种初值的设定 取决于编译器，在编译器眼里是不同的函数
* complex():re(0),im(0){}与上冲突

## 4参数传递与返回值

* 把构造函数放在singleton 一种设计模式
一份 

```c++
class A{
public:
  static A& getInstance();
  setup(){}
private:
  A();
  A(const A&rhs);

};
A& A::getInstance(){
  static A a;
  return a;
}
A::getInstance().setup();


```

创建对象

* complex c1(2,1)
* complex c2;
* complex*p=new complex(4);

* 常量成员函数
double real ()*const*{return re;}/不改变数据内容，例如拿数据，public 接口

* 参数传递 passby value vs.pass by reference(toconst)
三种 传压到函数栈上 要传的东西太大 引用
* 引用相当于指针 快，但是字符呢传value也可？尽量传引用加上const 

* 返回值传递  passby value vs.pass by reference(toconst)
* 友元 friend 函数声名，可取数据，打破封装
* 相同class的各个objects互为友元
* return by ref 传递者无需知道接收者是以ref形式接收，指针则相反
class complex:
{public:
  int func(const complex&param)
  {return param.rs+param.im;}
private:
  double re,im;
}
{c2.func(c1)}

### 总结

1. 数据在private里
2. 参数尽可能以引用形式传递，加不加const看情况
3. 返回值同2
4. body 里的函数要不要加const
5. 构造函数初始化列表

## 5 操作符重载

* 操作符是一个函数
* 复数相加 重载+操作符 可以用来加复数，石头，设计的人，设计该怎么加
* 两个方式，1.成员函数
* *所有成员函数带有隐藏参数，this*为调用者，谁调用函数，this就指向谁指针，二目操作符，作用到左边

```c++
inline complex&
__doapl(complex*ths,const complex& r)
{ //do assign plus 赋值加
  ths->re +=r.re;
  ths->im +=r.im;
  return *ths;//a value/object
}

inline complex&
complex ::operator +=(const complex& r)
{
  return __doapl(this,r)
}


```

* 2.非成员函数重载 无this pointer 全局函数

```c++
inline complex
//3 version
operator +(const complex&x,const complex&y)
{return complex(real(x)+real(y),imag(x)+imag(y));}
```

复+复，复+实，复+虚

* return by value 返回是local object .绝不可以是return by ref 两者相加后放在哪里去，在函数里创建的离开函数后就死掉了
* typename() int ()  *临时对象*，创建一个对象放加的结果然后马上返回，没有名字，下一行就死了
* << 全局写法

## 6 代码实例

```c++

#ifndef __COMPLEX__
#define __COMPLEX__
class complex{
public:
  complex(double r=0， double i=0)//构造函数无返回类型 传值与传引用一样
  :re(r),im(i)//初始化列表，设初值
  {//其他事情
  }
  complex& operator +=(const complex&);
  double real() const{return re;}
  double imag()const{return im;}
//无改动的函数加const
private:
  double re,im;
  friend complex&__doapl(complex*,const complex&)；

}；
inline complex&
__doapl(complex*this,const complex& r)
{
  this->re+=r.re;
  this->im+=r.im;
  return *this;
}


inline complex&
complex:: operator +=(const complex& r)
{
  return __doapl(this,r);
}

complex
operator +(const complex&x,const complex&y)
{ 
  return complex(real(x)+real(y),imag(x)+imag(y));//创建对象直接在类后的括号，临时对象


}

#include<iostream>

ostream&   //连串丢出
operator <<(ostream& os,const complex& x){
    os<<'('<<real(x)<<','<<imag(x)<<')';
}

#endif

```

## 7三大函数 拷贝构造 拷贝复制 析构 string class

copy assginment operator
拷贝构造一开始，而拷贝赋值为第二次
一位一位拷贝，带指针上使用编译器的拷贝构造和拷贝赋值，只是指针拷贝，

```c++
class String{
public:
String(const char*cstr=0);//构造函数

String(const String& str);//拷贝构造，没有返回类型
String & operator=(const String&str);//拷贝赋值，来源端 目的端
~String();//big three

char*get_c_str() const {return m_data};//inline，不改变data，cout


private:
  char* m_data;//动态分配的方式，若用编译器的构造函数来赋值，指针指向同一个位置？
};

inline
String::String(const char* cstr=0)
{
  if(cstr){
    m_data=new char[strlen(cstr)+1];
    strcpy(m_data,cstr);
  }
  else{
    //未指定初值
    m_data=new char[1];
    *m_data='\0';//空字符串
  }
}

inline
String::String~String(){
  delete[] m_data;//释放内存,清理
}

inline
String::String(const String & str){
  m_data=new char[strlen(str.m_data)+1]；
  strcpy(m_data,str.m_data);
}

inline
String& String::operator=(const String& str)
{
  if(this== &str)//两个指针指的是否为同一东西，效率高，正确性
  //*一定要有*！！a=a,第一个动作就把自己给杀掉了
  return *this;//自我检测self assignment自我赋值检测来源端和目的端

delete[] m_data;//1
m_data = new char[strlen(str.m_data)+1];//2
strcpy(m_data,str.m_data);//3
//* 拷贝复制函数 1左边先清空2再重新分配和右边一样大小的内存3再赋值
return *this;
}
ostream& operator<<(ostream& os,const String& str)
{
  os<<str.get_c_str();//把指针丢给cout
  return os;
}
```

浅拷贝a=b,指针指向同一内容,会造成b内存泄漏，没有指针指向了他，alias
深拷贝 copy ctor

## 8 栈和内存管理

* **stack**,存在于某作用域的一块内存空间例如调用函数函数本身会形成一个栈来放置它所接收的参数以及返回地址
在函数本体body内声名的任何变量其所使用的内存块都取自栈,stactic object 生命周期在作用域结束后仍然存在
global local objct ;
heap objexct 
内存泄漏：失去控制

* **heap**由操作系统提供的一块global内存空间，程序可动态分配从某中获得若干区块

```c++
class Complex{...};
...
{
  Complex c1(1,2);//stack
  Complex* p = new Complex(3);//heap

}
```

* new 被分解为三个动作 先分配内存再调用ctor

```c++
Comlex* pc= new Complex(1,2);
编译器转化为
Complex* pc;
void* mem =operator new(size of(Complex));//分配内存,内部调用malloc(n)
pc=static_cast<Complex*>(mem);//转型,指针
pc->Complex::Complex(1,2);//构造函数，通过指针调用

```

* delete :先调用dtor再释放memory

```c++
delete pc;
编译器转化为两个动作
Complex::~Complex(pc);//析构函数，删除动态分配的内存
operator delete(pc);//释放内存,字符串本身删除指针内部调用free(ps)

```

* 动态分配所得到的内存块，上下饼干 记住位置大小，借，最后一个bit记1，00000011,16字节10
* array new 一定要搭配array delete,delete[]p,唤起三次dtor,把指针所指的内存删除，内存泄露是指针所指的地方而非指针

## 9 模板

### 补充：static

在函数或数据前加，与对象脱离了，单独一个内存，
银行账户，多个户头，利率为同一份，设计为静态数据，只有一份
静态函数，没有thispointer，一般存取方法不可，只能处理静态数据

```c++
class Account{
public:
  static double m_rate;//只是声名，属于类，脱离对象
  static void set_rate(const double& x){};
 
};
double Account::m_rate=8.0;
int main(){
  Account::set_rate(5.0);

  Account a;
  a.set_rate(7.0)//两种调用静态函数的方式不会有a的地址调用
}

```

### 补充 把ctors 放在private区

```c++
class A{
public:
  satatic A& getInstance(return a;)//唯一窗口
  setup(){}
private:
A();
A(const A& rhs);
static A a;
}
//只有唯一的一个对象，设计模式
singleton

A::getInstance().setup();
//更好的做法
/*把static A a放在函数里

只有有人用一次才出现且只有一份*/

```

### 补充 cout

为什么cout可以接受各种各样的类型，操作符重载

### 补充 模板

* class template类模板

```c++
template<typename T>

complex<double> c1(2.5,1.5)
//代码的膨胀 不是缺点？

```

* function template//算法

```c++
template <class T>
inline
const T& min(const T& a,const T&b)
{return b<a?b:a;}

```

类模板需要明确指出来，而函数模板不需要，编译器会进行 arguement deduction
< 操作符重载

### 补充 namespace

namespace std{
  …
}
被包装在名字空间//单元里

* using directive
  using namespace std;//全部打开

* using declaration 一条一条声名
    using std::cout;
    cout<<……；
    std::cin<<;


## 单一class该怎么写 是否有指针

## 10组合与继承

### 类与类之间的关系

* composition,表示 has a
一个对象里有另一个对象，like c 里stru
用图来表现
调用它拥有的c来完成功能,a的所有功能让c来做,改装一下变成另一个类。已有一个功能强大的类，换了一个面貌出现
//设计模式adapter 变压器 适配配接，只是名称接口不同

```c++
class queue{
protected:
deque<T> c;//两端队列
public:
//以下完全用 c的操作函数完成
bool empty()const {return c.empty();}
size

}

```

#### 复合下的构造和析构

container-> component

* 构造由内而外
  container::container(…):*component()*{…};//不用写，编译器加上去
* 析构由外而内
  container::~container(…){…*~componet*()};


#### delegation 委托.composition by reference

private:
  stringrep* rep;//把任务委托给他人，生命创建时间不同步
这种叫做pimpl,pointer to implemention  handle+body,对外与实现类
共享 ,指向同一个hello节省内存,若要改,copy on write

#### inheritance,表示is a

struct _list_node_base{
……
}

template<typename _Tp>
struct _list_node
: public _list_node_base//语法
{
……
};
界门纲目科属种
子类的对象有父类的成分
构造由内而外，析构由外而内，内存，子类对象较大
base class 的dor必须是virtual

## 11虚函数与多态

inheritance with virtual function,继承搭配虚函数
函数的继承继承的是调用权

* non-virtual:你不希望派生类重新定义(override)
* virtual:你希望override,且你有默认定义
* pure virtual: 你希望一定要重新定义。且没有默认设定

```c++
class Shape{
public:
  virtual void draw()const=0;
  virtual void error{const std::string& msg}
  inr objectID()const;
};

class Rectangle:public Shape{};

class Ellipse:public Shape{};
```

* template method

application framework,一般性的动作

```c++

class CDocument{
public:

void  OnFileOpen(){
…//这是个算法，每个cout输出代表一个实际动作
cout<<"dialog……"<<endl;
cout<<"check files status……"<<endl;
cout<<"open file……"<<endl;

Serialize()//虚函数，让子类定义
cout<<"close file……"endl;
cout<<"update all views……"<<endl;>
}//MFC

virtual void Serialize(){};//空函数
};
application
class CMyDoc:
{}
  public CDocument
  {//买来的
  public:
    virtual void Serialize(){…
    //只有应用程序本身才知道如何读取自己的文件（格式）
    cout<<"cMyDoc::Serialize()"<<endl;
    }
  };


  int main(){
    CMyDoc myDoc;
    ……
    myDoc.OnFileOpen();//CDocument::OnFileOpen(&myDoc);Serilize通过this来调用

  }

```

### 继承加复合关系下的构造和析构

base
^
|
derived -> component

* derived object
  * base part
  * component part

base -> component
^
|
derived

* derived object
  * base part
    * component part

### delegation+inheritance 委托加继承

文件一份窗口四份officeppt,如何表现这种行为。存储与表现数据的类

```c++
class Subject{

int m_value;
vector<Observer*>m_views;//上下类的关系，观察者放在容器里
public:
void attach(Observer* obs){
//注册与注销（未呈现），谁要来观察，注册
m_views.push>back(obs);//放在容器里
}
void set_val(int value){
  m_value=value;
  notify();
}
void notify(){
  //遍历观察者，通知
  for(int i=0;i<m_views.size();i++)
  m_views[i]->update(this,m_value);
}

}

class Observer{//父类，可被继承，派生
public:
  virtual void update(Subject*sub，int value)=0;
};


```

ood,例子：23个设计模式

## 12 委托相关设计模式

如何写窗口系统 文件系统 窗口里有窗口 目录里有目录

### composite

容器里想要既放左边也放右边，父类，让参数为父类。两者都可了

图

```c++
class Component{

  int value;
  public:
  Component(int val){value=val;}
  virtual void  add (Component*){}//空函数，不做事情/动作
};
class Composite:public Component{

  vetor<Component*>c;
  public:
  Composite(int val):Component(val){}

  void add(Component* elem){
    c.push_back(elem)
  }
}

class Primitive:public Component{

  public:
  Primitive(int val):Component(val){}
};


```

### Prototype

设计一个框架，创建未来的子类

子类创建一个静态的自己类图与写代码相反先写对象
把原型放到上面，父类，构造函数设为私有的，自己人调用，可在构造函数中把自己挂上去
还有一个clone函数，做的事情new自己

```c++
#include<iostream>
enum  imageType
{
  LAST,SPOT
};

class Image
{
  public:
    virtual void draw()=0;
    static Image *findAndClone(imageType)
  
  protected:
    virtual imageType  returnType()=0;
    virtual Image*clone()=0;//pure virtual,要求子类一定要写出clone这一个函数
  //as each subclass of Image is declared,it registers its prototype
  static void addPrototype(Image* image){
    _prototypes[_nextSlot++]=image;

  }
  private:
  //addPrototype()saves each registed prototype here
  static Image*_prototype[10];//容器放所有的原型
  static int_nextSlot;

};
//静态函数要在类外给定义
Image*Image::_prototype[];
int Image::_nextSlot;//给内存


Image*Image::findAndClone(imageType type){

  for(int i=0;i<_nextSlot;i++){
    if(_prototype[i]->returnType()==type)
    return _prototype[i]->clone();
  }
}


class LandSatImage



```