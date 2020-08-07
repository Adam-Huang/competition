- [linux C++后台开发面试题](<https://zhuanlan.zhihu.com/p/103027724>)
- [知乎：程序员面试，面试官更注重代码量、项目经验还是操作系统、数据结构这种基础课程？两者比例是五五开还是多少？](https://www.zhihu.com/question/264198516)
- [c/c++ (cn)](https://interview.huihut.com/#/) 这篇文章已经总结的相当全面了。
- [C/C++复习指北](<https://blog.csdn.net/qq_40840459/category_7280598.html>)



# C/C++

## const

`const & constexpr`

[C++11/14 constexpr 用法](<https://www.jianshu.com/p/34a2a79ea947>) 写的不错，有例子但是还是不太明白。

### 存储位置

对于局部对象，常量存放在栈区；对于全局对象，常量存放在全局/静态存储区；对于字面值常量，常量存放在常量存储区。

> [C++：const常量的存储位置](<https://blog.csdn.net/qq_43152052/article/details/99306967>)
>
> const修饰的量不是常量，仅仅是个只读量。在编译的时候全部替换const变量被赋予的值（这点和C语言的宏相似），在运行的时候该const变量可通过内存进行修改。
>
> - 通过内存(指针)可以修改位于栈区的const变量，语法合乎规定，编译运行不会报错，但是在编译的时候所有用到该常量的地方全部被替换成了定义时所赋予的值，然后再运行的时候无法使用通过指针修改后的值。
> - 通过内存(指针)修改位于静态存储区的的const变量，语法上没有报错，编译不会出错，一旦运行就会报告异常。
>
> ```c++
> const int a = 1;
> void test1()
> {
>  const int c = 3;
>  int* p = (int*)& c; /*用c++的const_cast呢？*/
>  *p = 4;
>  //在编译的时候c被替换成了3，无法使用通过内存修改后的值
>  //*p表示c被修改后的值
>  cout << c << " " << *p << endl; // 3 4
>  
>  p = (int*)& a;
>  //在编译的时候a被替换成了1，p指向a的地址
>  cout << a << " " << *p << endl;
>  //修改位于静态存储区的const变量，编译无错，运行就会报异常
>  *p = 4;
>  //a的值还是1，因为在编译的时候字母a就被替换成1了，运行时会报异常
>  cout << a << endl;
> }
> ```
>
> 



## 多态

多态的实现主要分为静态多态和动态多态，静态多态主要是重载，在编译的时候就已经确定；动态多态是用虚函数机制实现的，在运行期间动态绑定。

### 虚函数

- 为什么析构函数必须是虚函数

> [C/C++基类的析构函数为什么必须定义为虚函数？](<https://blog.csdn.net/komtao520/article/details/82424468>) 有例子
>
> 简单来说，在表现出多态时，如果析构函数不是虚函数，系统（也就是`delete`）只会调用当时指针表现的类名的析构函数，不会调用派生类的析构函数（就是没有表现出多态性）

- 为什么C++默认的析构函数不是虚函数

  C++默认的析构函数不是虚函数是因为虚函数需要额外的虚函数表和虚表指针，占用额外的内存。而对于不会被继承的类来说，其析构函数如果是虚函数，就会浪费内存。因此C++默认的析构函数不是虚函数，而是只有当需要当作父类时，设置为虚函数。

  

- 虚函数表具体是怎样实现运行时多态的

  在有虚函数的类中，类的最开始部分是一个虚函数表的指针，这个指针指向一个虚函数表，表中放了虚函数的地址，实际的虚函数在代码段(.text)中。当子类继承了父类的时候也会继承其虚函数表，当子类重写父类中虚函数时候，会将其继承到的虚函数表中的地址替换为重新写的函数地址。使用了虚函数，会增加访问内存开销，降低效率。

#### 虚表分布

问的最多的就是虚表的布局，尤其是菱形继承(B 和 C 继承 A，D 继承 B 和 C)时每个对象的空间结构分布，比如问 D 有几份虚表，D 中 B 和 C 的成员空间排布

```c++
/*虚函数表相关*/
class Base {
public:
	int num;
	virtual void f() { std::cout << "base::f" << std::endl; }
	virtual void g() { std::cout << "base::g" << std::endl; }
	virtual void h() { std::cout << "base::h" << std::endl; }
};

class Base1
{
public:
	virtual void o() { std::cout << "Base1::o()" << std::endl; };
private:

};

class Derive : public Base {
public:
	int num;
	void g() { std::cout << "derive::g" << std::endl; }
};

class Derive2 : public Base {
public:
	int num;
	void h() { std::cout << "derive::h" << std::endl; }
};

class C :public Base, public Base1 {
public:
	void o(){ std::cout << "C::o()" << std::endl; }
};

int unittest_virtualtable()
{
	Base ba;
	printf("sizeof Base:%llu  obj:%llu\n addest ba:0x%llX ,addest first member:0x%llX\n",sizeof(Base),sizeof(ba),&ba,&ba.num);
	/*运行下发现：
	1. ba.num的地址比ba高8；表明是虚函数表指针_vfptr的大小
	2. sizeof(Base) == sizeof(ba) == 16，可见统计出来的数值是字节对齐后的值
	0x00007ff78680cd58 {testFuc.exe!const Base::`vftable'} {
		0x00007ff7867375f8 {testFuc.exe!Base::f(void)}, 
		0x00007ff7867391c3 {testFuc.exe!Base::g(void)},
		0x00007ff786736de7 {testFuc.exe!Base::h(void)}
	} KEY1
	*/
	
	TestStatic tb;
	printf("sizeof Base:%llu  obj:%llu\n addest ba:0x%llX ,addest first member:0x%llX\n", sizeof(TestStatic), sizeof(tb), &tb, &tb.s_dwCount);
	/*运行下可知：
	1. 只有包含虚函数的类才会有虚函数表
	2. sizeof(TestStatic), sizeof(tb), &tb, &tb.s_dwCount
	*/

	Base *bc = new Derive;
	ba.g();
	bc->g();
	/*运行结果：调用的是子类的函数，因为虚函数表被覆盖了
	0x00007ff78680ce00 {testFuc.exe!const Derive::`vftable'} {
		0x00007ff7867375f8 {testFuc.exe!Base::f(void)}, 
		0x00007ff78673785a {testFuc.exe!Derive::g(void)},
		0x00007ff786736de7 {testFuc.exe!Base::h(void)}}
	}
	*/

	Base *bd = new Base;
	Derive de;
	/*
	小结：
	1. 同一个类创建的对象，他们的虚函数表的地址是一样，当然虚函数的指针也是一样的；
	2. 继承的类虚函数表的地址就不一样了，但表中存放的地址只有被覆盖的才不一样，不覆盖的还是一样的；
	*/
	Base1 bf;
	C cg;
	/*考察多继承的过程中的虚函数表指针的问题：KEY2
	bf.__vfptr = 0x00007ff786825548 {testFuc.exe!const Base1::`vftable'} {
		0x00007ff786735820 {testFuc.exe!Base1::o(void)}
	}
	
	cg.__vfptr = 0x00007ff78680cef0 {testFuc.exe!const C::`vftable'{for `Base'}} {
		0x00007ff7867375f8 {testFuc.exe!Base::f(void)}, ...
	}
	cg.__vfptr = 0x00007ff786825638 {testFuc.exe!const C::`vftable'{for `Base1'}} {
		0x00007ff7867359e2 {testFuc.exe!C::o(void)}
	}
	小结：
	1. 两个虚函数表是真的
	2. 表指针的地址差的有点多 Base(8+8) +8+8+8(Base1)
	*/
	return 0;
}
```

- `KEY1`：有虚函数就一定有虚函数表，表内存放的应该是函数地址，即使是继承的子类也会有新的表，当然了，如果子类没有重载的函数，表内地址还是原来函数的地址。
- `KEY2`：此处可以解释菱形继承时的现象。首先如果哦继承子多个父类，就会有多个虚函数表，表的地址各不相同，但是，如果重载了哪个函数，那么对应表内的函数地址也就修改了。
- `windows`平台的函数地址怎么这么高，还是都很高？用`linux`跑一下试试。

**Linux**

```c++
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
```

1. `error 1`: error: request for member ‘base_data’ is ambiguous 菱形继承时访问最基类的成员变量出现的。参考访问方法：[stack overflow](<https://stackoverflow.com/questions/1313063/request-for-member-is-ambiguous-in-g>)。菱形继承的其他说明可见[C++菱形继承问题和虚继承分析](<https://blog.csdn.net/c_base_jin/article/details/86036185>)。
2. `error 2`: ‘int Derive::derive_data’ is inaccessible 继承多个的时候每个类名后面都要加`public`。

- `Key 1`:继承之后的类虚表还是在最开始的位置，占`8 Bytes`，子类的数据结构在父类的后面，此处对齐了。目前的内存分布大概如下：

  ```shell
  +==============Base===============+ # 0x7FFCF7922F70
  |           Base.__vrtpr          |
  -----------------------------------
  |Base.base_data |     空闲对齐     | # 0x7FFCF7922F78
  +==============Derive=============+
  |         Derive.__vrtpr          | # 0x7FFCF7922F80
  -----------------------------------
  |Base.base_data |Derive.derive_dat| # 0x7FFCF7922F88 0x7FFCF7922F8C
  ```

- `Key 2`: 从这个打印看，我猜他是有两个虚表的，而且应该是有两个`Base`类的空间，有两个`base_data`才会出现`error1`，我理解的内存分布如下：

  ```shell
  +==============Son================+ 
  |         Second.__vrtpr          | # 0x7FFCF7922FA0
  -----------------------------------
  |Base.base_data |Second.second_dat| # 0x7FFCF7922FA8 0x7FFCF7922FAC
  -----------------------------------
  |         Derive.__vrtpr          | # 此处应该还有一个虚表，但是有两个base_data
  -----------------------------------
  |Base.base_data |Derive.derive_dat| # 0x7FFCF7922FB8 0x7FFCF7922FBC
  -----------------------------------
  |  Son.son_data |     空闲对齐     | # 0x7FFCF7922FC0
  ```

- `Key 3`: 这里打印的是临时变量`vtbl`在栈的地址，其实没多大意义。
- `Key 4`: 首先父类是虚的，子类一定是虚的，加不加`virtual`都一样；其次，表的地址不一样但是未重载的函数地址是一样的，且函数地址空间很低（和windows下的不一样，可能是因为windows下给的进程内存不一样？）。
- `Key 5`: 虽然打印来打是输出了`Second`类的函数和函数地址，但是不能保证所有的`Son::func1`都是这个输出，之所以这样输出函数因为`Son`首先继承了`Second`类，`Second`的虚表位置低。



#### 虚函数与纯虚函数的区别

> [虚函数与纯虚函数的区别](<https://blog.csdn.net/qq_40840459/article/details/82351726>)
>
> 

## 类 

### 不能被继承

1. 什么类不能被继承（这个题目非常经典，我当时答出了private但是他说不好，我就没想到final我以为那个是java的）

> [用C++实现一个不能被继承的类](<https://blog.csdn.net/qq_40840459/article/details/80078999>)
>
> 因为子类继承父类，子类的构造函数和析构函数会调用父类的构造，解决问题的方法就是，不允许子类的构造函数调用父类的构造与析构。
>
> ```c++
> class SealedClass
> {
> public:
>     static SealedClass* getInstance()
>     {
>         return new SealedClass();
>     }
>     static void Delete(SealedClass* p)
>     {
>         delete p;
>     }
>     
> private:
>     SealedClass()       //将构造函数和析构函数设为私有
>     {}
>     ~SealedClass()
>     {}
> };
> ```
>
> 
>
> [在使用C++编写程序时,如果有一种需求为实现一个类不能被继承](<https://www.csdn.net/gather_29/MtzacgwsODMtYmxvZwO0O0OO0O0O.html>) 
>
> 最好使用`final`关键字实现目的,虚继承实现的方式是以性能为代价的

> [C++11 新特性：显式 override 和 final](<https://www.devbean.net/2012/05/cpp11-override-final/>)
>
> ```c++
> struct B1 final { };
> 
> struct D1 : B1 { }; // 错误！不能从 final 类继承！
> ```
>
> 值得注意的是，这些并不是一些语法糖，而是能确确实实地避免很多程序错误，并且暗示编译器可以作出一些优化。调用标记了`final`的`virtual`函数，例如上面的`B2::f`，GNU C++ 前端会识别出，这个函数不能被覆盖，因此会将其从类的虚表中删除。而标记为`final`的类，例如上面的 B1，编译器则根本不会生成虚表。这样的代码显然更有效率。
>
> 好像还有一个将构造和析构函数定义为`private`也可以。



## Static

## Hash

1. 哈希表，对哈希表的细节要求很高，比如哈希表的冲突检测、哈希函数常用实现、算法复杂度；比如百度二面就让我写一个哈希表插入元素算法，元素类型是任意类型。

>  [C++ STL中哈希表 hash_map从头到尾详细介绍](<https://blog.csdn.net/yousss/article/details/79541543>)
>
> hash_map，首先分配一大片内存，形成许多桶。是利用hash函数，对key进行映射到不同区域（桶）进行保存。
>
> 桶不止一个，很多桶，桶的长度是质数。

**函数对象**

> [C++函数对象operator()](<https://blog.csdn.net/xgf415/article/details/52966475>)
>
> 定义了调用操作符`()`的类对象。
>
> ```c++
> class A 
> {  
> public:  
>     int operator() ( int val )  {  return val > 0 ? val : -val; }  
> }; 
> 
> // call
> int i = -1;
> A func;
> cout << func(i);
> ```
>
> 

**SGI** SGI（Silicon Graphics Computer Systems, Inc.）



## AVL树，红黑树，B树与B+树

1. AVL 树和 B 树的概念、细节，比如会问mysql数据库的索引的实现原理，基本上就等于问你B树了。
2. 红黑树，这个基本上必问的一个数据结构，包括红黑树的概念、平均算法复杂度、最好最坏情况下的算法复杂度、、左右旋转、颜色变换。

### 总体对比

> [浅谈AVL树,红黑树,B树,B+树原理及应用](<https://blog.csdn.net/whoamiyang/article/details/51926985>)

### AVL树

> [AVL树(一)之 图文解析 和 C语言的实现](https://www.cnblogs.com/skywang12345/p/3576969.html)

### 红黑树

> [红黑树(一)之 原理和算法详细介绍](https://www.cnblogs.com/skywang12345/p/3245399.html)

### B树，B+树 & MySQL

> [B树与B+树](<https://blog.csdn.net/guoziqing506/article/details/64122287>) 
>
> [MySQL索引底层实现原理](https://www.cnblogs.com/boothsun/p/8970952.html)
>
> 在MySQL中，索引属于存储引擎级别的概念，不同存储引擎对索引的实现方式是不同的，本文主要讨论`MyISAM`和`InnoDB`两个存储引擎的索引实现方式。
>
> **MyISAM索引实现**
>
> MyISAM引擎使用B+Tree作为索引结构，叶节点的data域存放的是数据记录的地址。下图是MyISAM索引的原理图：
>
> ![MyISAM](https://images2017.cnblogs.com/blog/758447/201801/758447-20180127161009725-1788644003.png)
>
> **nnoDB索引实现**
>
> 虽然InnoDB也使用B+Tree作为索引结构，但具体实现方式却与MyISAM截然不同。
>
> 第一个重大区别是InnoDB的数据文件本身就是索引文件。从上文知道，MyISAM索引文件和数据文件是分离的，索引文件仅保存数据记录的地址。而在InnoDB中，表数据文件本身就是按B+Tree组织的一个索引结构，这棵树的叶节点data域保存了完整的数据记录。这个索引的key是数据表的主键，因此InnoDB表数据文件本身就是主索引。
>
> ![InnoDB](https://images2017.cnblogs.com/blog/758447/201801/758447-20180127161454428-323630182.png)
>
> 上图是InnoDB主索引（同时也是数据文件）的示意图，可以看到叶节点包含了完整的数据记录。这种索引叫做聚集索引。因为InnoDB的数据文件本身要按主键聚集，所以InnoDB要求表必须有主键（MyISAM可以没有），如果没有显式指定，则MySQL系统会自动选择一个可以唯一标识数据记录的列作为主键，如果不存在这种列，则MySQL自动为InnoDB表生成一个隐含字段作为主键，这个字段长度为6个字节，类型为长整型。
>
> 





1. 在涉及到父子类时构造与析构函数的执行顺序、多重继承时类的成员列表在地址空间的排列

2. 会问你一些 C++11的东西（或者问boost 库，基本上都一样），这个你用过就用过，没有用过就说没用过不要装X，常见的 C++11 需要掌握的一些技术库我也列举一下auto 关键字、for-each 循环、右值及移动构造函数 + std::forward + std::move + stl 容器新增的 emplace_back() 方法、std::thread 库、std::chrono 库、智能指针系列（std::shared_ptr/std::unique_ptr/std::weak_ptr）(智能指针的实现原理一定要知道，最好是自己实现过)、线程库 std::thread + 线程同步技术库std::mutex/std::condition_variable/std::lock_guard 等、lamda表达式（JAVA 中现在也常常考察 lamda 表达式的作用）、std::bind/std::function 库、

   其他的就是一些关键字的用法(override、final、delete)，还有就是一些细节如可以像 JAVA 一样在类成员变量定义处给出初始化值。

   

## 类和结构体

### 默认拷贝函数

```c++
#include<bits/stdc++.h>

using namespace std;

int main(){
    vector<int> t(10);
    struct temp{
     vector<int> ls;
    };
    
    class ctp{
        public:
        vector<int> ls;
    };
    struct temp t1;
    t1.ls.push_back(1);
    cout << t1.ls.capacity() << " | ";
    t1.ls.push_back(2);
    cout << t1.ls.capacity() << " | ";
    t1.ls.push_back(3);
    cout << t1.ls.capacity() << " | ";
    t1.ls.push_back(4);
    cout << t1.ls.capacity() << " | ";
    t1.ls.push_back(4);
    cout << t1.ls.capacity() << " | ";// KEY 1 容量成本提升
    cout << endl;
    struct temp t2 = t1;
    for(auto it = t2.ls.begin(); it != t2.ls.end(); ++it) cout << *it << " | ";
    struct temp t3(t1);
    for(auto it = t3.ls.begin(); it != t3.ls.end(); ++it) cout << *it << " | ";
    cout <<"\n----------------------------"<< endl;
    
    t1.ls[4] = 5;
    for(auto it = t2.ls.begin(); it != t2.ls.end(); ++it) cout << *it << " | ";
    for(auto it = t3.ls.begin(); it != t3.ls.end(); ++it) cout << *it << " | ";
    cout <<"\n----------------------------"<< endl;
    
    class ctp c1;
    c1.ls = t;// vector 拷贝是深拷贝 ， struct & class 拷贝都是深拷贝
    t[5] = 1;
    c1.ls[5] = 2;
    class ctp c2(c1);
    class ctp c3 = c1;
    t[4] = 5;
    c1.ls[4] = 7;
    for(auto it = t.begin(); it != t.end(); ++it) cout << *it << " | ";
    cout << endl;
    for(auto it = c1.ls.begin(); it != c1.ls.end(); ++it) cout << *it << " | ";
    cout << endl;
    for(auto it = c2.ls.begin(); it != c2.ls.end(); ++it) cout << *it << " | ";
    cout << endl;
    for(auto it = c3.ls.begin(); it != c3.ls.end(); ++it) cout << *it << " | ";
    cout << endl;
    return 0;
}
/*
vector.capacity(): 1 | 2 | 4 | 4 | 8 | 
struct copy: 
1 | 2 | 3 | 4 | 4 | 1 | 2 | 3 | 4 | 4 | 
----------------------------
1 | 2 | 3 | 4 | 4 | 1 | 2 | 3 | 4 | 4 | 
----------------------------

vecotr modified:  0 | 0 | 0 | 0 | 5 | 1 | 0 | 0 | 0 | 0 | 
class 1 modified: 0 | 0 | 0 | 0 | 7 | 2 | 0 | 0 | 0 | 0 | 
class 2 unchange: 0 | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 
class 3 unchange: 0 | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 0 | 0 |
*/
```





## 模板

### 模板类的单例模式

```c++
template<typename T>
class Single
{
public:
    static T* getinstance(void);
    static void destory(void);
private:
    Single(){}
    ~Single(){}
    Single(const Single&){}
    Single& operator=(const Single&){}
    static T* instance;
};

template<typename T>
T* Single<T>:: instance = nullptr;

template<typename T>
Single<T>::getinstance(){
    lock();
    if(instance == nullptr){
        instance = new T;
    }
    unlock();
    return instance;
}

template<typename T>
void Single<T>::destory(){
    lock();
    if(instance != nullptr){
        delete instance;
        instance = nullptr;
    }
    unlock();
}
```



## C++和C的区别

- 设计思想：C++是面向对象的语言，而C是面向过程的结构化编程语言
- 语法：C++具有封装、继承和多态三种特性；C++相比C，增加多许多类型安全的功能，比如强制类型转换；C++支持范式编程，比如模板类、函数模板等

## [nullptr & NULL](<https://blog.csdn.net/u011068702/article/details/64906864>)

> C里面的null和C++里面的`nullptr`、NULL介绍
>
> ```c++
> /* Define NULL pointer value */
> #ifndef NULL
>     #ifdef __cplusplus
>         #define NULL    0
>     #else  /* __cplusplus */
>         #define NULL    ((void *)0)
>     #endif  /* __cplusplus */
> #endif  /* NULL */
> ```
>
> C++中 NULL在C++中被明确定义为整数0
> NULL在C中的定义
>
> ```c++
> #define NULL    ((void *)0)
> ```
>
> C中NULL实质上是一个void *指针
>
> **NULL只是一个宏定义，而nullptr是一个C++关键字** `nullptr`关键字用于标识空指针，是`std::nullptr_t`类型的（`constexpr`）变量。它可以转换成任何指针类型和`bool`布尔类型，**但是不能被转换为整数**.

## cast

1. `const_cast`: 用于将`const`变量转为非`const`

2. `static_cast`: 用于各种隐式转换，比如非`const`转`const`，`void*`转指针等, `static_cast`能用于多态向上转化，如果向下转能成功但是不安全

3. `dynamic_cast`: 用于动态类型转换。只能用于含有虚函数的类，用于类层次间的向上和向下转化。只能转指针或引用。向下转化时，如果是非法的对于指针返回NULL，对于引用抛异常。要深入了解内部转换的原理。

4. `reinterpret_cast`: 几乎什么都可以转，比如将int转指针，可能会出问题

5. C的强制转换表面上看起来功能强大什么都能转，但是转化不够明确，不能进行错误检查，容易出错。

   > [c 风格的类型转换有不少的缺点](https://blog.csdn.net/qq_40421919/article/details/90677220)
   >
   > 有的时候用 c 风格的转换是不合适的,因为它可以在任意类型之间转换,比如你可以把一个指向 `const` 对象的指针转换 成指向非 `const` 对象的指针,把一个指向基类对象的指针转换成指向一个派生类对象的 指针,这两种转换之间的差别是巨大的,但是传统的 c 语言风格的类型转换没有区分这 些。还有一个缺点就是,c 风格的转换不容易查找,他由一个括号加上一个标识符组成, 而这样的东西在 c++程序里一大堆。所以 c++为了克服这些缺点,引进了 4 新的类型转换操作符。
   > ————————————————
   > 此文还有一些`cast`的例子可以参考



## 指针

### 指针和引用

1. 指针有自己的一块空间，而引用只是一个别名；
2. 使用`sizeof`看一个指针的大小是4，而引用则是被引用对象的大小；
3. 指针可以被初始化为NULL，而引用必须被初始化且必须是一个已有对象 的引用；
4. 作为参数传递时，指针需要被解引用才可以对对象进行操作，而直接对引 用的修改都会改变引用所指向的对象；
5. 可以有`const`指针，但是没有`const`引用；
6. 指针在使用中可以指向其它对象，但是引用只能是一个对象的引用，不能 被改变；
7. 指针可以有多级指针（**p），而引用至于一级；
8. 指针和引用使用++运算符的意义不一样；
9. 如果返回动态内存分配的对象或者内存，必须使用指针，引用可能引起内存泄露。

### 数组和指针



### 智能指针

1. `auto_ptr`（c++98的方案，c++11已经抛弃）采用所有权模式。

   ```c++
   auto_ptr< string> p1 (new string ("I reigned lonely as a cloud.”));
   auto_ptr<string> p2;
   p2 = p1; //auto_ptr不会报错.p2剥夺了p1的所有权，但是当程序运行时访问p1将会报错。所以auto_ptr的缺点是：存在潜在的内存崩溃问题！
   ```

2. `unique_ptr`

   `unique_ptr`实现独占式拥有或严格拥有概念，保证同一时间内只有一个智能指针可以指向该对象。它对于避免资源泄露（例如“以new创建对象后因为发生异常而忘记调用delete”）特别有用。

   ```c++
   unique_ptr<string> p3 (new string ("auto"));   // #4
   unique_ptr<string> p4；                       // #5
   p4 = p3;//此时会报错！！
   ```

   另外unique_ptr还有更聪明的地方：当程序试图将一个 unique_ptr 赋值给另一个时，如果源 unique_ptr 是个临时右值，编译器允许这么做；如果源 unique_ptr 将存在一段时间，编译器将禁止这么做，比如：

   ```c++
   unique_ptr<string> pu1(new string ("hello world"));
   unique_ptr<string> pu2;
   pu2 = pu1;                                      // #1 not allowed
   unique_ptr<string> pu3;
   pu3 = unique_ptr<string>(new string ("You"));   // #2 allowed
   ```

   如果确实想执行类似与#1的操作，要安全的重用这种指针，可给它赋新值。C++有一个标准库函数std::move()，让你能够将一个unique_ptr赋给另一个。例如

   ```c++
   unique_ptr<string> ps1, ps2;
   ps1 = demo("hello");
   ps2 = move(ps1);
   ps1 = demo("alexia");
   cout << *ps2 << *ps1 << endl;
   ```

`std::move()`

> [c++ 之 std::move 原理实现与用法总结](<https://blog.csdn.net/p942005405/article/details/84644069>)
>
> 在C++11中，标准库在`<utility>`中提供了一个有用的函数`std::move`，`std::move`并不能移动任何东西，**它唯一的功能是将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义**。从实现上讲，`std::move`基本等同于一个类型转换：
>
> ```c++
> static_cast<T&&>(lvalue);
> ```

`左值、左值引用、右值、右值引用`

> [C++ 11 左值，右值，左值引用，右值引用，std::move, std::foward](<https://blog.csdn.net/xiaolewennofollow/article/details/52559306>) 有例子
>
> 左值的声明符号为`&`， 为了和左值区分，右值的声明符号为`&&`
>
> **转移语义是和拷贝语义相对的**，可以类比文件的剪切与拷贝，当我们将文件从一个目录拷贝到另一个目录时，速度比剪切慢很多。
>
> ————————————————
>
> 这篇文章还说了右值引用的意义，真是对效率要求比较极致了。

3. `shared_ptr`

   `shared_ptr`实现共享式拥有概念。多个智能指针可以指向相同对象，该对象和其相关资源会在*最后一个引用被销毁*时候释放。从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。可以通过成员函数`use_count()`来查看资源的所有者个数。除了可以通过`new`来构造，还可以通过传入`auto_ptr, unique_ptr,weak_ptr`来构造。当我们调用`release()`时，当前指针会释放资源所有权，计数减一。当计数等于0时，资源会被释放。

4. `weak_ptr`

   `weak_ptr` 是一种不控制对象生命周期的智能指针, 它指向一个 `shared_ptr `管理的对象。 它只可以从一个 `shared_ptr` 或另一个 `weak_ptr` 对象构造, **它的构造和析构不会引起引用记数的增加或减少**。`weak_ptr`是用来解决`shared_ptr`相互引用时的死锁问题，它和`shared_ptr`之间可以相互转化，`shared_ptr`可以直接赋值给它，它可以通过调用`lock`函数来获得`shared_ptr`。

   ```c++
   #include <memory>
   #include <iostream>
   using namespace std;
   class B;
   class A
   {
   public:
   	// std::shared_ptr<B> pb_; 内存泄漏
   	std::weak_ptr<B> pb_;
   	~A()
   	{
   		cout<<"A delete\n";
   	}
   };
   class B
   {
   public:
   	// shared_ptr<A> pa_; 内存泄漏
   	std::weak_ptr<A> pa_;
   	~B()
   	{
   		cout<<"B delete\n";
   	}
   };
   int main()
   {
   	weak_ptr<B> wpb;
   	weak_ptr<A> wpa;
   	{
   		shared_ptr<B> pb(new B());
   		shared_ptr<A> pa(new A());
   		pb->pa_ = pa;
   		pa->pb_ = pb;
   		wpa = pa;
   		wpb = pb;
   		cout <<"pb.use_count() " << pb.use_count() <<" | _pb.use_count() " << pa->pb_.use_count() << endl;
   		cout <<"pa.use_count() " << pa.use_count() <<" | _pa.use_count() " << pb->pa_.use_count()<< endl;
   	}
   	cout <<"wpb.use_count() " << wpb.use_count() <<" | wpa.use_count() " << wpa.use_count() << endl;
   	return 0;
   }
   ```

   Output:

   ```shel
   pb.use_count() 2 | _pb.use_count() 2
   pa.use_count() 2 | _pa.use_count() 2
   wpb.use_count() 1 | wpa.use_count() 1 # 内存泄漏了
   
   pb.use_count() 1 | _pb.use_count() 1 # 内存不泄漏
   pa.use_count() 1 | _pa.use_count() 1
   A delete
   B delete
   wpb.use_count() 0 | wpa.use_count() 0
   ```

`error shared_ptr’ does not name a typ`

   >[error: ‘shared_ptr’ in namespace ‘std’ does not name a type](https://www.cnblogs.com/foohack/p/3997771.html)
   >
   >原因是，这是c++ 11标准的。在给g++传递命令行的时候加上`-std=c++0x`就行了。
   >
   >还需要在源码中`#include<memory>`
   >
   >[Error: ‘shared_ptr’ in namespace ‘std’ does not name a type](<https://www.linuxidc.com/Linux/2017-03/141510.htm>)
   >
   >出现这种问题的原因是C++ 11 在各种平台下的兼容问题
   >
   >```shell
   >sudo g++ -std=gnu++0x smart_ptr.cpp -o smart_ptr
   >```
   >

#### Implement

> [C++11中智能指针的原理、使用、实现](https://www.cnblogs.com/wxquare/p/4759020.html)
>
> ```c++
> #include <iostream>
> #include <memory>
> #include <assert.h>
> 
> template<typename T>
> class SmartPointer {
> private:
>     T* _ptr;
>     size_t* _count;
> public:
>     SmartPointer(T* ptr = nullptr) { //构造函数
>         _ptr = ptr;
>         
> 		if (_ptr) {
>             _count = new size_t(1);
>         } else {
>             _count = new size_t(0);
>         }
>     }
> 
>     SmartPointer(const SmartPointer& ptr) { //拷贝构造函数
>         if (this != &ptr) {
>             this->_ptr = ptr._ptr;
>             this->_count = ptr._count;
>             (*this->_count)++;
>         }
>     }
> 
>     SmartPointer& operator=(const SmartPointer& ptr) {
>         if (this->_ptr == ptr._ptr) {
>             return *this;
>         }
> 
>         if (this->_ptr) {
>             (*this->_count)--;//原值引用减1
>             if (this->_count == 0) {
>                 delete this->_ptr;
>                 delete this->_count;
>             }
>         }
> /*Q:此时原指针不是整体被覆盖，而仅仅只是计数减1？A:见output*/
>         this->_ptr = ptr._ptr;
>         this->_count = ptr._count;
>         (*this->_count)++;//新引用指针计数加1
>         return *this;
>     }
> 
>     T& operator*() {//返回值是引用
>         assert(this->_ptr);
>         return *(this->_ptr);
> 
>     }
> 
>     T* operator->() {/*Q:指示符返回指针本身还有效果嘛？*/
>         assert(this->_ptr == nullptr);
>         return this->_ptr;
>     }
> 
>     ~SmartPointer() {
>         (*this->_count)--;
>         if (*this->_count == 0) {
>             delete this->_ptr;
>             delete this->_count;
>         }
>     }
> 
>     size_t use_count(){
>         return *this->_count;
>     }
> };
> 
> int main() {
>     {
>         SmartPointer<int> sp(new int(10));
>         SmartPointer<int> sp2(sp);
>         std::cout <<"sp:  &" << &sp <<" count: " << sp.use_count() << " val: " << *sp << std::endl;
>         std::cout <<"sp2: &" << &sp2 <<" count: " << sp2.use_count() << " val: " << *sp2 << std::endl;
>         
>         SmartPointer<int> sp3(new int(20));
>         sp2 = sp3;
>         std::cout <<"sp3: &" << &sp3 <<" count: " << sp3.use_count() << " val: " << *sp3 << std::endl;
>         std::cout <<"sp2: &" << &sp2 <<" count: " << sp2.use_count() << " val: " << *sp2 << std::endl;
> 		std::cout <<"sp:  &" << &sp <<" count: " << sp.use_count() << " val: " << *sp << std::endl;
>     }
>     //delete operator
> 	std::cout << std::endl;
> 	
>     {
>         std::shared_ptr<int> sp(new int(10));
>         std::shared_ptr<int> sp2(sp);
>         std::cout <<"sp: &" << &sp <<" count: " << sp.use_count() << " val: " << *sp << std::endl;
>         std::cout <<"sp2: &" << &sp2 <<" count: " << sp2.use_count() << " val: " << *sp2 << std::endl;
>         
>         std::shared_ptr<int> sp3(new int(20));
>         sp2 = sp3;
>         std::cout <<"sp3: &" << &sp3 <<" count: " << sp3.use_count() << " val: " << *sp3 << std::endl;
>         std::cout <<"sp2: &" << &sp2 <<" count: " << sp2.use_count() << " val: " << *sp2 << std::endl;
> 		std::cout <<"sp:  &" << &sp <<" count: " << sp.use_count() << " val: " << *sp << std::endl;
>     }
>     return 0;
> }
> ```
>
> output:
>
> ```shell
> sp:  &0x7ffc8e45fba0 count: 2 val: 10 # 1. 两次执行的输出完全相同，说明内存被正确释放了
> sp2: &0x7ffc8e45fbb0 count: 2 val: 10 # 2. 虽然指向的是同一块内存，但是sp2和sp是两个不同对象
> sp3: &0x7ffc8e45fbc0 count: 2 val: 20
> sp2: &0x7ffc8e45fbb0 count: 2 val: 20
> sp:  &0x7ffc8e45fba0 count: 1 val: 10
> ```
>
> 

- 智能指针有没有内存泄露的情况
- 智能指针的内存泄漏如何解决

### 函数指针

函数指针本身首先是一个指针变量，该指针变量指向一个具体的函数。C在编译时，每一个函数都有一个入口地址，该入口地址就是函数指针所指向的地址。

```c++
char * fun(char * p)  {…}        // 函数fun
char * (*pf)(char * p);          // 函数指针pf
pf = fun;                        // 函数指针pf指向函数fun
pf(p);                           // 通过函数指针pf调用函数fun
```









- 重载和覆盖

  重载：两个函数名相同，但是参数列表不同（个数，类型），返回值类型没有要求，在同一作用域中
  覆盖：子类继承了父类，父类中的函数是虚函数，在子类中重新定义了这个虚函数，这种情况是重写

## ++i和i++

> [知乎：在程序开发中，++i 与 i++的区别在哪里？](https://www.zhihu.com/question/19811087/answer/80210083)
>
> ```c++
> int i = 0;
> int *p1 = &(++i); //正确
> int *p2 = &(i++); //错误
> 
> ++i = 1; //正确
> i++ = 5; //错误
> ```
>
> 注意这里++i的实现：
>
> ```c++
> // 前缀形式：
> int& int::operator++() //这里返回的是一个引用形式，就是说函数返回值也可以作为一个左值使用
> {	//函数本身无参，意味着是在自身空间内增加1的
>       *this += 1;  // 增加
>       return *this;  // 取回值
> }
> 
> //后缀形式:
> const int int::operator++(int) //函数返回值是一个非左值型的，与前缀形式的差别所在。
> {	//函数带参，说明有另外的空间开辟
>       int oldValue = *this;  // 取回值
>       ++(*this);  // 增加
>       return oldValue;  // 返回被取回的值
> }
> ```
>
> i++ 最后返回的是一个临时变量，而**临时变量是右值**。
>
> 效率方面，知乎有回答：若`i`是内置类型，就没差别，但若是自定义类型，如`iterator`那就是`++i`比较快了。

## `extern“C”`

**加上extern "C"后，会指示编译器这部分代码按C语言（而不是C++）的方式进行编译。由于C++支持函数重载，因此编译器编译函数的过程中会将函数的参数类型也加到编译后的代码中，而不仅仅是函数名；而C语言并不支持函数重载，因此编译C语言代码的函数时不会带上函数的参数类型，一般只包括函数名。**

### 重载原理

> [函数重载写法与实现原理](<https://blog.csdn.net/a15929748502/article/details/80748747>)
>
> ![](https://img-blog.csdn.net/20180621145840901?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExNTkyOTc0ODUwMg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
>
> ![](https://img-blog.csdn.net/20180621151638209?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExNTkyOTc0ODUwMg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
>
> ![](https://img-blog.csdn.net/20180621151715674?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExNTkyOTc0ODUwMg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
>
> C++代码在编译时会对函数进行重命名，从这个角度讲函数重载本质上还是不同的函数

## `new/delete`与`malloc/free`

> [动态内存分配、malloc与new的区别](<https://blog.csdn.net/qq_40840459/article/details/81268252>)
>
> 

## 运行空间分布

```c++
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int g_var;         //bss
int data_var0 = 1; //初始化数据

static int s_gvar;

const int cdw_var = 10;
constexpr int cdw_var2 = 20;

class TestStatic
{
public:
	int fuc();
	int p;
	static int s_dwCount;
	void addfuc();
};

int TestStatic::s_dwCount = 30;

void TestStatic::addfuc()
{
	printf("s_dwCount addr: %llX, value: %d \n", &s_dwCount, s_dwCount);// s_dwCount addr: 601050, value: 30 KEY1
	s_dwCount++;
}

int TestStatic::fuc() {
	void (TestStatic::*paf)() = &TestStatic::addfuc;
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,paf);//0x4006F6
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,&paf);// 0x7FFF4CA0F900 KEY4
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,(void *&) paf);//0x4006F6
	printf("[__LINE__:%d] 0x%p\n",__LINE__,&TestStatic::addfuc); //0x4006F6 %p -> 指针的值 
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,&TestStatic::addfuc);//0x4006F6 KEY3
	return 0;
}

int main(){
	printf("[__LINE__:%d] Address of main(Code Segment):%p\n",__LINE__,main);// 0x400871
	
	printf("[__LINE__:%d] Data Location: Address of data_var(Data Segment):%p\n",__LINE__,&data_var0); // 0x602058
	static int data_var1=4;
	printf("[__LINE__:%d] Local static variable: Address of data_var(Data Segment):%p\n",__LINE__,&data_var1); // 0x602060
	
	printf("[__LINE__:%d] BSS Location: g_var: 0x%llX, value:%d\n",__LINE__,&g_var,g_var); //   g_var: 0x602068, value:0
	printf("[__LINE__:%d] s_gvar: 0x%llX, value:%d\n",__LINE__,&s_gvar,s_gvar);//s_gvar: 0x60206C, value:0 KEY1
	
	int* p1 = (int*)&cdw_var;
	int* p2 = (int*)&cdw_var2;
	printf("[__LINE__:%d] p1: 0x%llX, value:0x%llX\n",__LINE__,&p1,p1); //p1: 0x7FFF4CA0F950, value:400A18
	printf("[__LINE__:%d] p2: 0x%llX, value:0x%llX\n",__LINE__,&p2,p2); //p2: 0x7FFF4CA0F958, value:400A1C KEY2
	
	char *b = (char *)sbrk((ptrdiff_t)0);
	printf("[__LINE__:%d] Heap Location: Initial end of heap:%p\n",__LINE__,b); // 0x259d000 KEY7
	
	TestStatic* t = new TestStatic;
	t->addfuc();
	t->fuc();
	printf("[__LINE__:%d]: the object address:0x%llX\n", __LINE__,t);//1777030 
	printf("[__LINE__:%d]: the object variable address:0x%llX\n", __LINE__,&t); // 7FFF4CA0F960 stack address
	
	printf("[__LINE__:%d]: the first variable address:0x%llX\n", __LINE__,&(t->p));//1777030 KEY5
	delete t; t = nullptr;
	
	return 0;
}
```

`error 1`: 'constexpr' does not name a type

> [error: 'constexpr' does not name a type m- arduino ide](https://stackoverflow.com/questions/24845127/error-constexpr-does-not-name-a-type-m-arduino-ide)
>
> To use C++11 Features like constexpr you need to update your IDE to the currently beta version . And then enable C++11 support via compiler flag `-std=c++11`.

- `KEY1`: 未初始化全局变量和静态变量会被初始化为0；存放位置都在一起`.bss 0x601058`，地址空间较小。同时类中的静态成员（其实全部的初始化成员）也说存放在静态区域的`0x601050`（数据区）。从后续补充的例子上也看得出来，是有数据段合并的，具体可参考《操作系统》
- `KEY2`: `p1`和`p2`本身的地址`0x7FFF4CA0F950`是栈的地址，较高，而存放原常量的地址是`p1`的值，可以看出`0x400A18`还是毕竟低的，是常量区，但是也可以看出来`const`和`constexpr`修饰的值位置差不多。
- `KEY3`:打印成员函数地址是`0x4006F6`可以看出，地址比全局变量的地址还低，是代码段的地址；而且用`%p`可以直接按16进制打印指针的值，还自带`0x`，不错。还有的话就参考[C/C++ %s %d %u 基本概念与用法](<https://blog.csdn.net/myyllove/article/details/79574582>)，但基本都是常用的了，最多不熟的还差一个`%e`了。
- `KEY4`: 打印调用类的成员函数中的变量的地址，是栈的`0x7FFF4CA0F900`，但是值得强调的是该地址比`KEY2`中的`p1/p2`地址要低，这就是因为栈的地址是从上到下生长的。
- `KEY5`: 在类中的函数后新建了一个非静态成员变量，地址和类对象的地址一模一样`0x1777030`表面了函数只有一个地址，无论多少对象都是公用一个地址。而成员变量不同，每个对象都不一样。并且此时没有虚函数表。
- `KEY6`: 从这个简单的例子中也能窥探这个栈的地址好像很大。

某次完整的output如下：

```shell
(base) ejior@ejior-XPS-8930:~/huangyue/linuxcode$ ./exe
[__LINE__:41] Address of main(Code Segment):0x400871
[__LINE__:43] Data Location: Address of data_var(Data Segment):0x602058
[__LINE__:45] Local static variable: Address of data_var(Data Segment):0x602060
[__LINE__:47] BSS Location: g_var: 0x602068, value:0
[__LINE__:48] s_gvar: 0x60206C, value:0
[__LINE__:52] p1: 0x7FFD9B58C038, value:0x400AC8
[__LINE__:53] p2: 0x7FFD9B58C040, value:0x400ACC
[__LINE__:56] Heap Location: Initial end of heap:0x105d000
s_dwCount addr: 60205C, value: 30 
[__LINE__:32] 0x400736
[__LINE__:33] 0x7FFD9B58BFE0
[__LINE__:34] 0x400736
[__LINE__:35] 0x0x400736
[__LINE__:36] 0x400736
[__LINE__:61]: the object address:0x103D030
[__LINE__:62]: the object variable address:0x7FFD9B58C048
[__LINE__:64]: the first variable address:0x103D030
```

### 字符常量

```c++
int unittest_char() {
	/*剑指offer P49:
	为了节省内存，c/C++把常量字符串放到同一内存中，几个指针赋值相同string时，会指向相同的内存；数组不同*/
	char st1[] = "test"; //0x00000025d031fa04 "test"
	char st2[] = "test"; //0x00000025d031fa24 "test"
	char* st3 = "test";  //0x00007ff6279b5e18 "test"
	char *st4 = "test";  //0x00007ff6279b5e18 "test"
	return 0;
}
```

上述是在`vs2015`下调试的结果，但是可以看出来`str1`和`str2`是按照`new`指针对待的，而`str3`和`str4`就是栈上的常量了。

## `Lambda`

**值捕获**

**引用捕获**

**隐式捕获**有两种方式，分别是[=]和[&]。[=]表示以值捕获的方式捕获外部变量，[&]表示以引用捕获的方式捕获外部变量。

# STL

## erase

- `vector deque`都是erase之后给下一个迭代器是有返回值的
- `set map`删除之后后面的还有效，但是需要在删除之前保留一下下一个迭代器
- `list`兼顾上两者的特性。

## `deque`

![](http://c.biancheng.net/uploads/allimg/191213/2-19121316430U40.gif)