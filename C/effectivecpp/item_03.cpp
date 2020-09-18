#include<bits/stdc++.h>

using namespace std;

class CTextBase{
    int* size;
    char* p;
public:
    CTextBase(const char* other);
    int& getsize() const;
    char& operator[](int pos) const;
};

CTextBase::CTextBase(const char* other){
    // printf("[line %d]: value of size: %d \n", __LINE__, size);//默认初始值在这之前就已经初始化了
    size = new int(strlen(other) + 1);
    p = new char[*size];
    strcpy(p,other);
}

int& CTextBase::getsize() const{
    printf("[line %d]: address of size: %p \n", __LINE__, size);
    return *size;
}

char& CTextBase::operator[](int pos) const{
    printf("[line %d]: address of size: %p \n", __LINE__, &p[pos]);
    return p[pos];
}

int main(){
    /*
    char greeting[] = "Hello";
    const char *p = greeting;
    greeting[0] = 'J';
    // *p = 'H'; 只是不能通过这个变量修改
    printf("[line %d]: value of greeting: %s, value of p: %s \n", __LINE__, greeting, p);
    */
    
    const CTextBase T("Hello");
    int* a = &T.getsize(); // 返回值是右值，要用常量引用才可以。
    printf("[line %d]: address of size: %p \n", __LINE__, a);
    
    char* p = &T[0];
    printf("[line %d]: value of p: %p \n", __LINE__, p);
    return 0;
}
/*
[line 20]: value of size: 10 
[line 27]: address of size: 0x7ffe07257a60 
[line 47]: address of size: 0x7ffe07257a60 
[line 32]: address of size: 0x602000000010 
[line 50]: value of p: 0x602000000010 

1. 行号全部减5
2. 声明左值引用，引用不了T.getsize()，需要声明常量引用。但是[]符号返回值也是右值呀，为啥可以取地址
参考：https://www.runoob.com/cplusplus/returning-values-by-reference.html
被引用的对象不能超出作用域。所以返回一个对局部变量的引用是不合法的
*/


