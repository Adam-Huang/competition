#include <iostream>
#include <stdio.h>

using namespace std;
 
class Base
{
public :
    int base_data;
    Base() { base_data = 1; }
    virtual void func1() { cout << "base_func1" << endl; }
    virtual void func2() { cout << "base_func2" << endl; }
    virtual void func3() { cout << "base_func3" << endl; }
};
 
class Derive : public Base
{
public :
    int derive_data;
    Derive() { derive_data = 2; }
    virtual void func1() { cout << "derive_func1" << endl; }
    virtual void func2() { cout << "derive_func2" << endl; }
};

class Second : public Base
{
public :
    int second_data;
    Second() { second_data = 3; }
    void func1() { cout << "second_func1" << endl; }
    virtual void func2() { cout << "second_func2" << endl; }
};

class Son : public Second, public Derive
{
public :
    int son_data;
    Son() { son_data = 4; }
    void func3() { cout << "son_func3" << endl; }
    //virtual void func2() { cout << "son_func2" << endl; }
};
 
typedef void (*func)();
 
int main()
{
    Base base;
	printf("[__LINE__:%d] &base: 0x%llX\n",__LINE__,&base); // 0x7FFCF7922F70
	printf("[__LINE__:%d] &base.base_data: 0x%llX\n",__LINE__,&base.base_data); // 0x7FFCF7922F78 
    cout << "\n------------------base above----------------------\n" << endl;
 
    Derive derive;
	printf("[__LINE__:%d] &derive: 0x%llX\n",__LINE__,&derive); //0x7FFCF7922F80
	printf("[__LINE__:%d] &derive.base_data: 0x%llX\n",__LINE__,&derive.base_data); // 0x7FFCF7922F88
	printf("[__LINE__:%d] &derive.derive_data: 0x%llX\n",__LINE__,&derive.derive_data); // 0x7FFCF7922F8C KEY 1
    cout << "\n------------------derive above----------------------\n" << endl;
 
	Second second;
	printf("[__LINE__:%d] &second: 0x%llX\n",__LINE__,&second); //0x7FFCF7922F90
	printf("[__LINE__:%d] &second.base_data: 0x%llX\n",__LINE__,&second.base_data); //0x7FFCF7922F98
	printf("[__LINE__:%d] &second.derive_data: 0x%llX\n",__LINE__,&second.second_data); //0x7FFCF7922F9C
    cout << "\n------------------second above----------------------\n" << endl;
 
	Son son;
	printf("[__LINE__:%d] &son: 0x%llX\n",__LINE__,&son); //0x7FFCF7922FA0
	printf("[__LINE__:%d] &son.second_data: 0x%llX\n",__LINE__,&son.second_data); //0x7FFCF7922FAC
	printf("[__LINE__:%d] &son.Derive::base_data: 0x%llX\n",__LINE__,&son.Derive::base_data);//0x7FFCF7922FB8 | son.base_data error 1
	printf("[__LINE__:%d] &son.derive_data: 0x%llX\n",__LINE__,&son.derive_data);//0x7FFCF7922FBC error 2
	printf("[__LINE__:%d] &son.son_data: 0x%llX\n",__LINE__,&son.son_data); //0x7FFCF7922FC0 KEY 2
    cout << "\n------------------son above----------------------\n" << endl;
 
    for(int i=0; i<3; i++)
    {
        // &base : base首地址
        // (unsigned long*)&base : base的首地址，vptr的地址
        // (*(unsigned long*)&base) : vptr的内容，即vtable的地址，指向第一个虚函数的slot的地址
        // (unsigned long*)(*(unsigned long*)&base) : vtable的地址，指向第一个虚函数的slot的地址
        // vtbl : 指向虚函数slot的地址
        // *vtbl : 虚函数的地址
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&base) + i;
		printf("[__LINE__:%d] &vtbl: 0x%llX\n",__LINE__,&vtbl); // KEY 3
		printf("[__LINE__:%d] *vtbl: 0x%llX\n",__LINE__,*vtbl); // 0x400FB0(base_func1) 0x400FDC(base_func2) 0x401008(base_func3) KEY4
        func pfunc = (func)*(vtbl);
        pfunc(); 
    }
    cout << "\n----------------------------------------\n" << endl;
 
    for(int i=0; i<3; i++)
    {
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&derive) + i;
        printf("[__LINE__:%d] &vtbl: 0x%llX\n",__LINE__,&vtbl); // 
		printf("[__LINE__:%d] *vtbl: 0x%llX\n",__LINE__,*vtbl); // 0x401066(derive_func1) 0x401092(derive_func2) 0x401008(base_func3) KEY4
        func pfunc = (func)*(vtbl); //
        pfunc(); //
    }
    cout << "\n----------------------------------------\n" << endl;
	
	for(int i=0; i<3; i++)
    {
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&second) + i;
        printf("[__LINE__:%d] &vtbl: 0x%llX\n",__LINE__,&vtbl); //
		printf("[__LINE__:%d] *vtbl: 0x%llX\n",__LINE__,*vtbl); // 0x4010F0(second_func1) 0x40111C(second_func2) 0x401008(base_func3) KEY4
        func pfunc = (func)*(vtbl); //
        pfunc(); //
    }
    cout << "\n----------------------------------------\n" << endl;
	
	for(int i=0; i<3; i++)
    {
        unsigned long* vtbl = (unsigned long*)(*(unsigned long*)&son) + i;
        printf("[__LINE__:%d] &vtbl: 0x%llX\n",__LINE__,&vtbl); //
		printf("[__LINE__:%d] *vtbl: 0x%llX\n",__LINE__,*vtbl); // 0x4010F0(second_func1) 0x40111C(second_func2) 0x401198(son_func3) KEY5
        func pfunc = (func)*(vtbl); //
        pfunc(); //
    }
    cout << "\n----------------------------------------\n" << endl;
    return 1;
}