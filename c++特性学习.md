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

####lambda 

在python和c++中可以见到lambda表达式，一脸懵逼啊
先介绍c++中的lambda表达式
格式：
[捕获列表](参数列表) -> 返回类型 { 函数体 }
实例
```
auto add = [](int a, int b) -> int { return a + b; };
int result = add(2, 3);  // result为5

```
lambda表达式，也称为lambda函数是在调用或作为函数参数传递的位置处定义匿名函数对象的便捷方法

实例2
```
#include <algorithm>
#include <cmath>

void abssort(float* x, unsigned n) {
    std::sort(x, x + n,
        // Lambda expression begins
        [](float a, float b) {
            return (std::abs(a) < std::abs(b));
        } // end of lambda expression
    );
}

```
这个例子中，sort的第三个参数应该是排序函数，但是通过lambda表达式，直接将排序函数的函数体定义在里面，对于不需要复用且比较小的函数，这种写法很好
在python中 lambda更简单 
例如
add = lambda a,b: a+ b 前面是参数名，后面是表达式

Lambda表达式的优点
可以直接在需要调用函数的位置定义短小精悍的函数，而不需要预先定义好函数
std::find_if(v.begin(), v.end(), [](int& item){return item > 2});
1
使用Lamdba表达式变得更加紧凑，结构层次更加明显、代码可读性更好
Lambda表达式的缺点
Lamdba表达式语法比较灵活，增加了阅读代码的难度
对于函数复用无能为力

Lambda表达式工作原理
编译器会把一个Lambda表达式生成一个匿名类的匿名对象，并在类中重载函数调用运算符，实现了一个operator()方法。

auto print = []{cout << "Hello World!" << endl; };
1
编译器会把上面这一句翻译为下面的代码：

class print_class
{
public:
	void operator()(void) const
	{
		cout << "Hello World!" << endl;
	}
};
// 用构造的类创建对象，print此时就是一个函数对象
auto print = print_class();



####std::function and std::bind 结构化

function和bind 在c++中对于回调函数进行统一的调用和封装
首先，c++中的可调用函数有自定义函数，lambda表达式， 函数指针，bind对象，函数对象

函数指针是由函数参数和返回类型决定的
关于函数指针的例子
```
# include <iostream>

int fun(int x, int y) {                         //被调用的函数
    std::cout << x + y << std::endl;
	return x + y;
}

int fun1(int (*fp)(int, int), int x, int y) {   //形参为函数指针
	return fp(x, y);
}

typedef int (*Ftype)(int, int);                 //定义一个函数指针类型Ftype
int fun2(Ftype fp, int x, int y) { 
	return fp(x, y);
}

int main(){
	fun1(fun, 100, 100);                          //函数fun1调用函数fun
	fun2(fun, 200, 200);                          //函数fun2调用函数fun
}


```
可以看出函数可以作为一个参数传入另一个函数的参数

lambda表达式。。略，总之就是产生了一个匿名对象的调用，可以保证安全性

函数对象：重载了函数调用运算符（）的对象就是函数对象

可调用对象的定义方式很多但是函数的调用都很相似，需要一个统一的方式来保存可调用对象
于是std::function就出现了
std::function是一个可调用对象包装器，是一个类模板，可以容纳除了类成员函数指针之外的所有可调用对象，
它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟它们的执行。
定义std：：function
```
#include <functional>
std::function<type>

```
例如
```
# include <iostream>
# include <functional>

typedef std::function<int(int, int)> comfun;//定义了一个类型为 int（int，int）的comfun 模板

// 普通函数
int add(int a, int b) { return a + b; }

// lambda表达式
auto mod = [](int a, int b){ return a % b; };

// 函数对象类
struct divide{
    int operator()(int denominator, int divisor){
        return denominator/divisor;
    }
};

int main(){
	comfun a = add;
	comfun b = mod;
	comfun c = divide();
    std::cout << a(5, 3) << std::endl;
    std::cout << b(5, 3) << std::endl;
    std::cout << c(5, 3) << std::endl;
}


```
//comfun 被定义为模板类 相当于创建了一个a对象，将add函数和divide类寄存进去
简化了函数的调用


####std::bind
bind 是一个通用函数的适配器，通过接受一个可调用的函数对象，生成一个新的可调用对象来适应原参数列表
bind顾名思义是绑定的意思，可以将函数和参数列表绑定，然后再用function保存

bind的调用

auto newfuntion = bind(function,argc_list)
//该表达式意为 调用newfunction时，会调用function并且传递argc_list中的参数

具体使用代码
```
#include <iostream>
#include <functional>

class A {
public:
    void fun_3(int k,int m) {
        std::cout << "print: k = "<< k << ", m = " << m << std::endl;
    }
};

void fun_1(int x,int y,int z) {
    std::cout << "print: x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

void fun_2(int &a,int &b) {
    ++a;
    ++b;
    std::cout << "print: a = " << a << ", b = " << b << std::endl;
}

int main(int argc, char * argv[]) {
    //f1的类型为 function<void(int, int, int)>
    auto f1 = std::bind(fun_1, 1, 2, 3); 					//表示绑定函数 fun 的第一，二，三个参数值为： 1 2 3
    f1(); 													//print: x=1,y=2,z=3

    auto f2 = std::bind(fun_1, std::placeholders::_1, std::placeholders::_2, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
    f2(1, 2);												//print: x=1,y=2,z=3
 
    auto f3 = std::bind(fun_1, std::placeholders::_2, std::placeholders::_1, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f3 的第二，一个参数指定
    //注意： f2  和  f3 的区别。
    f3(1, 2);												//print: x=2,y=1,z=3

    int m = 2;
    int n = 3;
    auto f4 = std::bind(fun_2, std::placeholders::_1, n); //表示绑定fun_2的第一个参数为n, fun_2的第二个参数由调用f4的第一个参数（_1）指定。
    f4(m); 													//print: a=3,b=4
    std::cout << "m = " << m << std::endl;					//m=3  说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的,如m
    std::cout << "n = " << n << std::endl;					//n=3  说明：bind对于预先绑定的函数参数是通过值传递的，如n
    
    A a;
    //f5的类型为 function<void(int, int)>
    auto f5 = std::bind(&A::fun_3, &a, std::placeholders::_1, std::placeholders::_2); //使用auto关键字
    f5(10, 20);												//调用a.fun_3(10,20),print: k=10,m=20

    std::function<void(int,int)> fc = std::bind(&A::fun_3, a,std::placeholders::_1,std::placeholders::_2);
    fc(10, 20);   											//调用a.fun_3(10,20) print: k=10,m=20 

    return 0; 
}
std::placeholders::_1 是 C++ 标准库中的一个占位符（placeholder），用于 std::bind 函数模板。占位符允许你在绑定一个函数或成员函数时，延迟指定某些参数，直到实际调用时再传递这些参数。
 auto f2 = std::bind(fun_1, std::placeholders::_1, std::placeholders::_2, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
    f2(1, 2);												//print: x=1,y=2,z=3
std::placehoulders是一个对象，允许你在调用时延时传入参数，这里就可以在调用时使用f2(1,2),而不是f2()
    auto f3 = std::bind(fun_1, std::placeholders::_2, std::placeholders::_1, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f3 的第二，一个参数指定
    //注意： f2  和  f3 的区别。
    f3(1, 2);												//print: x=2,y=1,z=3
中 std::placeholder::1和2是不一样的
```
 int m = 2;
    int n = 3;
    auto f4 = std::bind(fun_2, std::placeholders::_1, n); //表示绑定fun_2的第一个参数为n, fun_2的第二个参数由调用f4的第一个参数（_1）指定。
    f4(m); 													//print: a=3,b=4
    std::cout << "m = " << m << std::endl;					//m=3  说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的,如m
    std::cout << "n = " << n << std::endl;					//n=3  说明：bind对于预先绑定的函数参数是通过值传递的，如n

    bind对于placeholder：：采用引用传递，对于a，bc之类的是通过值传递的


    为什么 auto f5 = std::bind(&A::fun_3, &a, std::placeholders::_1, std::placeholders::_2);要有&a？
    在C++中，当你使用 std::bind 绑定一个成员函数时，需要传递一个对象的指针或引用，因为成员函数必须通过对象调用。成员函数和普通函数不同，它们依赖于特定的对象实例，这样才能访问对象的成员数据和其他成员函数
    所以在使用bind需要实例化