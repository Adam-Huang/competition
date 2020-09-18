# TX-25927 -后台开发工程师

**服务器性能优化相关**

> [服务器性能优化](<https://blog.csdn.net/zhangbijun1230/article/details/81607739>)
>
> 这篇文章写的很详细，可以用作参考指标。但目前：
>
> 1. 对应单机性能的分析，一般我们会将目光锁定在CPU和IO上，因为对于应用程序一般分为CPU bound型和IO bound型，即计算密集型或者读写密集型；至于内存，其性能因素往往也会反映到CPU或者IO上，因为内存的设计初衷就是提高内核指令和应用程序的读写性能。
>    - 当内存不足，系统可能进行大量的交换操作，这时候磁盘可能成为瓶颈；
>    - 而缺页、内存分配、释放、复制、内存地址空间映射等等问题又可能引起CPU的瓶颈；
>
> 性能优化并不是一个孤立的课题，除了响应时间的考虑，我们往往还需要综合功能性、完整性、安全性等等方面的问题。
>
> 以下针对服务器各个模块即相应工具进行具体阐述：CPU、内存、IO、文件系统。这是一个很系统的工程。慢慢来。

**内存泄漏的类型、表现、检测**

> [内存泄漏:百度百科](<https://baike.baidu.com/item/%E5%86%85%E5%AD%98%E6%B3%84%E6%BC%8F?fr=ala0_1_1#>)
>
> 类型大概就4类，比如常发性、偶发性、一次性、隐式。
>
> 换个角度有：
>
> 1. 堆内存泄漏 （Heap leak）
> 2. 系统资源泄露（Resource Leak）.主要指程序使用系统分配的资源比如 Bitmap,handle ,SOCKET等没有使用相应的函数释放掉，导致系统资源的浪费，严重可导致系统效能降低，系统运行不稳定。 
>
> 具体点，导致这样的行为有：
>
> 1. 不匹配使用new[] 和 delete[]
> 2. delete void * 的指针，导致没有调用到对象的析构函数，析构的所有清理工作都没有去执行从而导致内存的泄露；
> 3. 没有将基类的析构函数定义为虚函数
>
> 

`vargrind`的参数。

```shell
$ valgrind --tool=memcheck --leak-check=full ./test
```



**崩溃的原因**

1. 非法内存访问（空指针、数组越界等）
2. 栈上申请大空间、或递归用尽。

**程序在返回时崩溃？**

> 返回时崩溃通常意味着您的函数会覆盖堆栈(因此返回地址)，并且您的程序会跳转到无处。您可以通过在反汇编级别逐步指令来验证这一点。
>
> 调用此函数的某个析构函数导致的崩溃。

**设计高性能服务器**



**`gdb`调试多线程**

> [gdb调试多线程程序总结](https://www.cnblogs.com/lsgxeva/p/8078670.html)





**线程错乱线程锁**

CPU满了如何定位。进程->线程->之后呢？



**性能测试测什么**

测时间。响应时间、处理时间等。

负载。高并发的处理机制。

**解决复杂问题？**



# 特效图形图像工程师 — 抖音短视频

## C++11

[C++11中的std::bind](<https://blog.csdn.net/u013654125/article/details/100140328>) & [std::function](<https://blog.csdn.net/weixin_39554266/article/details/82855294?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param>)

```c++
#include <functional>
#include <iostream>

using namespace std;
 
int TestFunc(int a, char c, float f)
{
    cout << a << endl;
    cout << c << endl;
    cout << f << endl;
 
    return a;
}

struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_+i << '\n'; }
    int num_;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
 
int main()
{
    //bind 绑定一个函数和其中的参数
    auto bindFunc1 = bind(TestFunc, std::placeholders::_1, 'A', 100.1);
    bindFunc1(10);
 
    cout << "=================================\n";
 
    auto bindFunc2 = bind(TestFunc, std::placeholders::_2, std::placeholders::_1, 100.1);
    bindFunc2('B', 10);
 
    cout << "=================================\n";
 
    auto bindFunc3 = bind(TestFunc, std::placeholders::_2, std::placeholders::_3, std::placeholders::_1);
    bindFunc3(100.1, 30, 'C');

    /*       function      */
    cout << "\n==============function===================\n";
    // 存储自由函数
    std::function<void(int)> f_display = print_num;
    f_display(-9);
 
    // 存储 lambda
    std::function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();
 
    // 存储到 std::bind 调用的结果
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display_31337();
 
    // 存储到成员函数的调用
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo, 1);
    f_add_display(314159, 1);
 
    // 存储到数据成员访问器的调用
    std::function<int(Foo const&)> f_num = &Foo::num_;
    std::cout << "num_: " << f_num(foo) << '\n';
 
    // 存储到成员函数及对象的调用
    using std::placeholders::_1;
    std::function<void(int)> f_add_display2 = std::bind( &Foo::print_add, foo, _1 );
    f_add_display2(2);
 
    // 存储到成员函数和对象指针的调用
    std::function<void(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, _1 );
    f_add_display3(3);
 
    // 存储到函数对象的调用
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);
}

```

## 类的继承

```c++
#include <stdio.h>

class Base {
public:
    Base() {
        printf("Base::Base\n");
    }
    ~Base() {
        printf("Base::~Base\n");
    }
    void print1() {
        printf("Base::print1\n");
    }
    virtual void print2() {
        printf("Base::print2\n");
    }
};

class Child: public Base {
public:
    Child() {
        printf("Child::Child\n");
    }
    ~Child() {
        printf("Child::~Child\n");
    }
    void print1() {
        printf("Child::print1\n");
    }
    virtual void print2() {
        printf("Child::print2\n");
    }
};

int main() {
    Child* child = new Child;// Base::Base\n Child::Child\n
    Base* base = child; // 

    child->print1(); // Child::print1
    child->print2(); // Child::print2
    base->print1(); // Base::print1
    base->print2(); // Child::print2

    cout << sizeof(Base) << endl;
    
    delete base; // Base::~Base\n

    Child* child2 = nullptr;
    child2->print1(); // segment default 
    //child2->print2(); // 
} // 
```

## 单例模式





# `SDK`开发

**构造函数调用虚函数，调用的是谁的？**

是自己的呀。

**如何判断一个数据类型？**

1. `typeid(a) == tpyeid(int)?`

2. `std::is_same`

   > [C++11的模板类型判断——std::is_same和std::decay](<https://blog.csdn.net/czyt1988/article/details/52812797>)
   >
   > 在模板里可以通过std::is_same判断模板的类型，从而实现对不同类型的区别对待。

**详细说下哪些基础类？**

**兼容性，降低耦合度的手段？**

**并发、同步怎么做的？**

**生成者消费者模型说一下**

**设计上的考虑，可扩展性呀，灵活性呀，生命周期啊这些的？**

**多线程上，耗时不一样，如何优化。**

**数据一致性问题**

# Python C++开发工程师

## telephone

C++和OS常规

## 现场

1. 动态规划，一个数组，有正有负，找到最大的连续子数组。动态规划；如果可以允许有环，那么最大子数组是多少。我用的带`start`和`end`的动态规划。基于第一个问题。
2. 控制流（一个还有10W个数的数组，那大于50000一个逻辑，小于50000一个逻辑，那么数组有序效率高，还是数组无序效率高？）和寻址（M行N列的数组，怎么遍历效率高，先行在列？先列再行？）；一个数组，`0 < a[i] <= 10`那么如果有一个数是重复的，那么怎么找到那个数？如果有两个数重复呢？三个数重复呢？重复次数都是1；要求算法时间O(n)，空间O(1)；
3. 30个程序员，20个会C++，23个会python，25个会java，28个会PHP，那么数数，至少多少个人是会4种语言的？有一个数是`1838265625`他是某个数`A`的6次方，如何快速找到这个`A`；

