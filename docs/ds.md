# 第一章 枚举

## 枚举的基本思想

逐个尝试答案，数学，公式定理规律

* 例子:求小于n的最大素数
  数学公式
  从大到小？
  判断n-i是否为素数的问题
* 例子：完美立方,寻找所有的四元组（a,b,c,d）满足，按照从小到大顺序
* 技巧

$$
a^3=b^3+c^3+d^3
$$

思路：四重循环枚举a,b,c,d
a最外层从小到大，合理设计枚举方式。[2.n]，**枚举范围缩小,设置枚举顺序**枚举组合
b[2,a-1]，b比a小，c[b,a-1]

## 例题 生理周期

![alt text](image-6.png)

### 解题思路

* 从d+1天开始，一直试到第21252天，对其中每个日子k,看是否满足
（k-p）%23==0&&(k-e)%28==0&&(k-i)%33==
* 如何试得更快
**跳着试**

```c++
#include<iostream>
using namespace std;
#define N 21252
int main(){
int p,e,i,d,caseno=0;
while(cin>>p>>e>>i>>d&&p!=-1){//不停地读入数据直到p=-1
    ++caseno;//casenumber
    int k;//枚举日子
    for(k=d+1;(k-p)%23;++k);//d之后找第一个体力高峰
    for(;(k-e)%28;k+=23);//最小公倍数寻找双高峰非体力高峰不考虑
    for(;(k-i)%33;k+=23*28);
    cout<<"case"<<caseno<<":the next triple peak occurs in"<<k-d<<"days."<<endl;//n好像没有用
}

return 0;
}
```

减少尝试的次数

![alt text](image-7.png)

## 例题 称硬币

![alt text](image-8.png)

### 解题思路2

对于每一枚硬币先假设它是轻的，看这样是否符合称量结果。如果符合，问题即解决。如果不符合，就假设它是重的，看是否符合称量结果。把所有的硬币都试一遍，一定能找到特殊硬币。

```c++
#include<iostream>
#include<cstring>
using namespace std;
char Left[3][7];//天平左边硬币a-l
char Right[3][7];//天平右边硬币
char result[3][7];
bool isfake(char c,bool light);
//light为真表示假设假币为轻，否则表示假币为重
int main(){
int t;
cin>>t;
while(t--){
    for(int i=0;i<3;i++) cin>>Left[i]>>Right[i]>>result[i];
    for(char c='A';c<='L';c++)//枚举，分两种情况轻还是重
    if(isfake(c,1)){
        cout<<c<<"is the counterfait coin and it is light.\n";
        break;
    }
    else if(isfake(c,0)){cout<<c<<"is the counterfait coin and it is heavey.\n";
        break;}

}



return 0;
}

bool isfake(char c,bool light)
{
    for(int i=0;i<3;i++){//带入到三次测量结果
        char *pleft,*pright;//指向天平两端的字符串
        if(light){
            pleft=Left[i];
           pright=Right[i];
        }
        else{
            pleft=Right[i];
            pright=Left[i];//c是重的情况，左右对调
        }

        switch(result[i][0])
        {
        //天平右边的情况,c是轻的情况
    case'u':
        if(strchr(pright,c)==NULL)
            return false;
        break;
    case 'e':
        if(strchr(pleft,c)||strchr(pright,c))
        return false;
        break;//感谢chat,少了一个break
    case'd':
        if(strchr(pleft,c)==NULL)
            return false;
        }

    }
     return true;
}
```

![alt text](image-9.png)

## 例题熄灯
