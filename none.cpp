# include <iostream>
using namespace std;

int main() {
    int *p, *q,*h;
    int a,b;
    cin>>a>>b;
    p=&a;
    q=&b;
    h=p;
    p=q;
    q=h;
    cout<<*p<<*q<<endl;
    

    return 0;
}