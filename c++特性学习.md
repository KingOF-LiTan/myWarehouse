#C++ 新特性 （智能指针，lambda，等）

####auto 用法
在编程时常常要把表达式的值赋予给变量，我们在手动赋值的时候需要清楚知道表达式类型
c++11引入auto	让编译器来分析表达式所属类型

1.auto的推导规则
1.声明为auto（不是auto&）的变量，忽视掉初始化表达式的顶层const。即对有const的普通类型(int 、double等)忽视const，对常量指针（顶层const）变为普通指针，
对指向常量（底层const）的常量指针（顶层cosnt）变为指向常量的指针（底层const）。
2.声明为auto&的变量，保持初始化表达式的顶层const或volatile 属性
3.若希望auto推导的是顶层const，加上const，即const auto
问题来了，什么是底层，顶层const，这个说法和指针有很大的关系
对于指针本身是一个常量，即指针的指向是一个常量，也就说不能改变指针的指向，称其为顶层const属性

int* cosnt p1 = &a;即cosnt 修饰p1 指针const

对于指针指向的对象是一个常量，即指针指向的地址的值是一个常量，也就是说不能改变指针指向内存的值，称其为底层 const属性

cosnt int* p2 = &a;const修饰int*即p2的值

p1称为常量指针
p2称为指向常量指针
顶层const在赋值给其他变量时，可以忽略顶层属性；
底层const在赋值给其他变量时，不能忽略底层属性；
int*类型可以转换为顶层和底层const，所以它可以给顶层和底层的const赋值；
底层const无法转换为顶层const。

auto的真正用途其实就是为变量自动匹配类型

没用auto时，你可能可以看到
```
#include<string>
#include<vector>
int main()
{
    std::vector<std::string> vs;
    for (std::vector<std::string>::iterator i = vs.begin(); i != vs.end(); i++)
    {
        //...
    }
}

```
声明十分长
使用auto可以简化代码如下
```
#include<string>
#include<vector>
int main()
{
    std::vector<std::string> vs;
    for (auto i = vs.begin(); i != vs.end(); i++)
    {
        //..
    }
}

```
auto 为i自动匹配了std::vector<std::string>::iterator

除了在这里，auto还在函数模板中产生作用
```


template <typename _Tx,typename _Ty>
void Multiply(_Tx x, _Ty y)
{
    auto v = x*y;
    std::cout << v;
}


```
到编译时v的类型才被确定

先写这些，以后遇到别的用法再回头看看
####智能指针

智能指针，说是指针，更像是一个对象，能更方便的管理一个对象的生命周期
c++中，智能指针有4种auto_ptr,unique_ptr,shared_ptr,weak_ptr (auto_ptr在c++11中已经移除不可用)

普通的指针需要自己来声明，需要自己来delete，如果不能delete容易造成指针悬挂

指针指针可以自动管理一个对象的生命周期，什么时候生成什么时候析构不需要用户自己手动输入

unique_ptr  是一个强引用指针。可以拥有一个对象


```void runGame()
{　　
  std::unique_ptr<Monster> monster1(new Monster());//monster1 指向 一个怪物　　
  std::unique_ptr<Monster> monster2 = monster1;//Error!编译期出错，不允许复制指针指向同一个资源。　　   	std::unique_ptr<Monster> monster3 = std::move(monster1);//转移所有权给monster3.　　
  monster1->doSomething();//Oops!monster1指向nullptr，运行期崩溃 
}

```
要引用智能指针很像stl的容器
可以使用makeunique或new来创建uniqueptr
std::unique_ptr<int> uniqueInt = std::make_unique<int>(10); // 使用 make_unique
std::unique_ptr<Monster> monster1(new Monster()); new
最常用的用法就是用来代替原始指针，提高安全

shared ptr 
我们提到的智能指针，很大程度上就是指的shared_ptr，shared_ptr也在实际应用中广泛使用。它的原理是使用引用计数实现对同一块内存的多个引用。在最后一个引用被释放时，
指向的内存才释放，这也是和 unique_ptr 最大的区别。当对象的所有权需要共享(share)时，share_ptr可以进行赋值拷贝。
shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。每使用他一次，内部的引用计数加1，
每析构一次，内部的引用计数减1，减为0时，删除所指向的堆内存。

shared 指针的写法
void f2() {
    shared_ptr<int> p = make_shared<int>(1);
    shared_ptr<int> p2(p);
    shared_ptr<int> p3 = p;
}

我们该如何选择智能指针：

如果程序要使用多个指向同一个对象的指针，应选择 shared_ptr。这样的情况包括
1.有一个指针数组，并使用一些辅助指针来标示特定的元素，如最大的元素和最小的元素；
2.两个对象包含都指向第三个对象的指针；
3.STL 容器包含指针。很多 STL 算法都支持复制和赋值操作，这些操作可用于 shared_ptr，但不能用于 unique_ptr（编译器发出 warning）和 auto_ptr（行为不确定）。
如果你的编译器没有提供 shared_ptr，可使用 Boost 库提供的 shared_ptr。

如果程序不需要多个指向同一个对象的指针，则可使用 unique_ptr。如果函数使用 new 分配内存，并返还指向该内存的指针，
将其返回类型声明为 unique_ptr 是不错的选择。这样，所有权转让给接受返回值的 unique_ptr，而该智能指针将负责调用 delete。
