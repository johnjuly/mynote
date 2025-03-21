#

## functions and lambdas(how can we represent functions as variables in cpp)

* def: a predicate is a boolean-valued function
* use of predicates:how can we use **isvowel**to find the first vowel in a string or isprime to find a prime number in a `vector<int>`or isdivisible to find a number divisible by 5?

* key idea: pass a predicate to a function

* modify **find** function

```c++
template<typename it,typename T>
it find_if(it first,it last,const T& value){
  for(auto it=first;it!=last;++it){
    if(*it==value)//太具体了如何修改去处理更一般的情形? 传入pred而不是值，就变成了 
    if(pred(*it))
    return it;
  }
  return last;
}

** answer:templates+predicates

template<typename it,typename Pred>//the type of our predicate compiler will figure this out for us using implicit instantiation!
it find_if(it first,it last,Pred pred)/*our predicate,passed as a parameter*/{
  for(auto it=first;it!=last;++it){
    
    if(pred(*it))//calling predication on each element
    return it;
  }
  return last;
}


```

!!! note "using **find_if** function"

    ```cpp
    bool isvowel(char c){
      c=::toupper(c);
      return c=='A'||c=='E'
    }
    std::string corlys="lord of the Tides";
    auto it =find_if(corlys.begin(),corlys.end(),isvowel);
    *it='0';




    bool isprime(size_t n){
      if(n<2>)return false;
      for(size_t i=3;i<=std::sqrt(n);i++)
        if(n%i==0)return false;
      return true;
    }

    std::vector<int> ints={1,0,6};
    auto it=find_if(ints.begin(),ints.end(),isprime);
    assert(it==ints.end());

    ```

* passing functions allows us to generalize an algorithm with user defined behaviour

* pred is a function pointer，可以传入一个函数中的参数而已

  * *pred=bool(\*)(char)返回值 说明是函数指针 参数类型


### funtion pointers generalize poorly

consider that 在一个向量中找到一个比N大的数字
不可以将布尔函数多增加一个参数bool islessthan(int elem,int n){
  return elem<n;
}因为我们只传一个参数给pred,pred(*it)
所以我们想做的是给函数多加一个状态而不去添加另一个参数
于是

--- --- ---


### lambda functions

* they are functions that capture state from an enclosing scope


```cpp
int n;
std::cin>>n;

auto lessthann=[n](int x){return x<n;};
find_if(begin,end,leesthann);

```

#### lambda syntax

类型 **capture clause**:use outside variables 函数的参数 函数主体：与普通函数一样，只是parameters and captures are in-scope

!!! note "captures"

    ```cpp
    auto lambda =[capture-values](arguments){
    return expression
    }

    [x](args)//captures x by value(make a copy)
    [x&](args)//by ref
    [x,y](args)
    [&](arg)//captures **everything **by reference
    [&,x](args)//captures **everything **except x by reference
    [=](args)//everything  by value

    ```

#### 可以不用captures

  ```cpp
  std::string corlys="lord of the tides"
  auto it =find_if(corlys.begin(),corlys.end(),[](auto c){
    c=toupper(c);
    return c=='A'||
  });


  ```

#### auto parameters are shorthand for templates

```cpp
//可以改成两个表格
auto lessthann=[n](auto x){
  return x<n;
};

template<typename T>
auto lessthann=[n](T x){
  return x<n;
}

//use implicit instantiation let compiler figure out types when function is called

```

### how do lambdas work?

* a functor is any object that defines an operator() aka an object that acts like a function


!!! note "example std::greater"

    ```cpp
    template<typename T>
    struct std::greater{
      bool operator()(const T& a,const T& b) const {
        return a>b;
      }
    };

    std::greater<int>g;
    g(1,2)

    ```



!!! note "example `std::hash<T>`"

    ```cpp
    template<>
    struct std::hash<MyType>{
    //this syntax is called a template specialization for type mytype
    size_t operation()(const MyType& v) const{
      //
    }
    };
    MyType m;
    std::hash<MyType>hash_fn;
    hash_fn(m);
    ```

* since functor is an object it can have state

```cpp
struct my_functor{
  bool operator()(int a)const{
    return a*value;
  }
  int value;
};

my_functor f;
f.value=5;
f(10);
```

* 当你使用lambda时，a functor type is generated

```cpp
int n=10
auto lessthann =[n](int x){return x<n;};
find_if(begin,end,lessthann);

equal

class __lambda_6_18//random name
  {
    public: 
    inline /*constexpr */ bool operator()(int x) const
    {
      return x < n;
    }//functor call operator

     __lambda_6_18(int & _n)
    : n{_n}
    {}//class constructor
    private: 
    int n;//captures became fields in the class
  };


  int n=10;
  auto lessthann =lambda_6_18{n};//capturing variable from outer scope by passin to constructor
  find_if(begin,end,lessthann);




```

### recap

!!! note "functions lambdas recap"

    * use functions/lambdas to pass around behaviour as variables
    * aside: std::functions is an overarching type for functions/lambdas
      * any functor/lambda pointer canbe cast to it
      * a bit slower
      * use auto/template


## algorithms(revising an old algorithm )

> a collection of template functions

* algo let us inspect and transfer data,all of the llm tools and libraries are written in c++ with extensive use of stl


## ranges and views(a brand new cpp26,functional approach to cpp algorithms)

> a new version of the stl

a range is anything with a begin  and end

inculde:
  vector ,unordered_set,set,map

* use concepts,better error messages 
* can pass entire containers

* operate on ranges

```cpp
int main(){
  std::vector<char> v ={'a' *};
  auto it =std::ranges::find(v,'c');
}

```

* concept
  view: a way to compose algorithms,a view is a range that lazily adapts another range
  like python generators

```cpp
auto view = letters
|std



```
