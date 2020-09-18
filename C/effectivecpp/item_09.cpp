#include<bits/stdc++.h>

using namespace std;

class A{
public:
    A(){
        printf("[line %d]: A::A() typeid:%s \n", __LINE__, typeid(this).name());
        f();
    }
    virtual void f(){ printf("[line %d]: A::f() \n", __LINE__); }
};

class B: public A{
public:
  B(){
      printf("[line %d]: B::B() typeid:%s \n", __LINE__, typeid(this).name());
        f();
  }
    virtual void f() { printf("[line %d]: B::f() \n", __LINE__); }
};


int main(){
    // A a1;
    B b1;
    return 0;
}


