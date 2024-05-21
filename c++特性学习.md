#C++ ������ ������ָ�룬lambda���ȣ�

####auto �÷�
�ڱ��ʱ����Ҫ�ѱ��ʽ��ֵ������������������ֶ���ֵ��ʱ����Ҫ���֪�����ʽ����
c++11����auto	�ñ��������������ʽ��������

1.auto���Ƶ�����
1.����Ϊauto������auto&���ı��������ӵ���ʼ�����ʽ�Ķ���const��������const����ͨ����(int ��double��)����const���Գ���ָ�루����const����Ϊ��ָͨ�룬
��ָ�������ײ�const���ĳ���ָ�루����cosnt����Ϊָ������ָ�루�ײ�const����
2.����Ϊauto&�ı��������ֳ�ʼ�����ʽ�Ķ���const��volatile ����
3.��ϣ��auto�Ƶ����Ƕ���const������const����const auto
�������ˣ�ʲô�ǵײ㣬����const�����˵����ָ���кܴ�Ĺ�ϵ
����ָ�뱾����һ����������ָ���ָ����һ��������Ҳ��˵���ܸı�ָ���ָ�򣬳���Ϊ����const����

int* cosnt p1 = &a;��cosnt ����p1 ָ��const

����ָ��ָ��Ķ�����һ����������ָ��ָ��ĵ�ַ��ֵ��һ��������Ҳ����˵���ܸı�ָ��ָ���ڴ��ֵ������Ϊ�ײ� const����

cosnt int* p2 = &a;const����int*��p2��ֵ

p1��Ϊ����ָ��
p2��Ϊָ����ָ��
����const�ڸ�ֵ����������ʱ�����Ժ��Զ������ԣ�
�ײ�const�ڸ�ֵ����������ʱ�����ܺ��Եײ����ԣ�
int*���Ϳ���ת��Ϊ����͵ײ�const�����������Ը�����͵ײ��const��ֵ��
�ײ�const�޷�ת��Ϊ����const��

auto��������;��ʵ����Ϊ�����Զ�ƥ������

û��autoʱ������ܿ��Կ���
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
����ʮ�ֳ�
ʹ��auto���Լ򻯴�������
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
auto Ϊi�Զ�ƥ����std::vector<std::string>::iterator

���������auto���ں���ģ���в�������
```


template <typename _Tx,typename _Ty>
void Multiply(_Tx x, _Ty y)
{
    auto v = x*y;
    std::cout << v;
}


```
������ʱv�����Ͳű�ȷ��

��д��Щ���Ժ���������÷��ٻ�ͷ����
####����ָ��

����ָ�룬˵��ָ�룬������һ�������ܸ�����Ĺ���һ���������������
c++�У�����ָ����4��auto_ptr,unique_ptr,shared_ptr,weak_ptr (auto_ptr��c++11���Ѿ��Ƴ�������)

��ͨ��ָ����Ҫ�Լ�����������Ҫ�Լ���delete���������delete�������ָ������

ָ��ָ������Զ�����һ��������������ڣ�ʲôʱ������ʲôʱ����������Ҫ�û��Լ��ֶ�����

unique_ptr  ��һ��ǿ����ָ�롣����ӵ��һ������


```void runGame()
{����
  std::unique_ptr<Monster> monster1(new Monster());//monster1 ָ�� һ�������
  std::unique_ptr<Monster> monster2 = monster1;//Error!�����ڳ�����������ָ��ָ��ͬһ����Դ������   	std::unique_ptr<Monster> monster3 = std::move(monster1);//ת������Ȩ��monster3.����
  monster1->doSomething();//Oops!monster1ָ��nullptr�������ڱ��� 
}

```
Ҫ��������ָ�����stl������
����ʹ��makeunique��new������uniqueptr
std::unique_ptr<int> uniqueInt = std::make_unique<int>(10); // ʹ�� make_unique
std::unique_ptr<Monster> monster1(new Monster()); new
��õ��÷�������������ԭʼָ�룬��߰�ȫ

shared ptr 
�����ᵽ������ָ�룬�ܴ�̶��Ͼ���ָ��shared_ptr��shared_ptrҲ��ʵ��Ӧ���й㷺ʹ�á�����ԭ����ʹ�����ü���ʵ�ֶ�ͬһ���ڴ�Ķ�����á������һ�����ñ��ͷ�ʱ��
ָ����ڴ���ͷţ���Ҳ�Ǻ� unique_ptr �������𡣵����������Ȩ��Ҫ����(share)ʱ��share_ptr���Խ��и�ֵ������
shared_ptrʹ�����ü�����ÿһ��shared_ptr�Ŀ�����ָ����ͬ���ڴ档ÿʹ����һ�Σ��ڲ������ü�����1��
ÿ����һ�Σ��ڲ������ü�����1����Ϊ0ʱ��ɾ����ָ��Ķ��ڴ档

shared ָ���д��
void f2() {
    shared_ptr<int> p = make_shared<int>(1);
    shared_ptr<int> p2(p);
    shared_ptr<int> p3 = p;
}

���Ǹ����ѡ������ָ�룺

�������Ҫʹ�ö��ָ��ͬһ�������ָ�룬Ӧѡ�� shared_ptr���������������
1.��һ��ָ�����飬��ʹ��һЩ����ָ������ʾ�ض���Ԫ�أ�������Ԫ�غ���С��Ԫ�أ�
2.�������������ָ������������ָ�룻
3.STL ��������ָ�롣�ܶ� STL �㷨��֧�ָ��ƺ͸�ֵ��������Щ���������� shared_ptr������������ unique_ptr������������ warning���� auto_ptr����Ϊ��ȷ������
�����ı�����û���ṩ shared_ptr����ʹ�� Boost ���ṩ�� shared_ptr��

���������Ҫ���ָ��ͬһ�������ָ�룬���ʹ�� unique_ptr���������ʹ�� new �����ڴ棬������ָ����ڴ��ָ�룬
���䷵����������Ϊ unique_ptr �ǲ����ѡ������������Ȩת�ø����ܷ���ֵ�� unique_ptr����������ָ�뽫������� delete��

####lambda 

��python��c++�п��Լ���lambda���ʽ��һ���±ư�
�Ƚ���c++�е�lambda���ʽ
��ʽ��
[�����б�](�����б�) -> �������� { ������ }
ʵ��
```
auto add = [](int a, int b) -> int { return a + b; };
int result = add(2, 3);  // resultΪ5

```
lambda���ʽ��Ҳ��Ϊlambda�������ڵ��û���Ϊ�����������ݵ�λ�ô�����������������ı�ݷ���

ʵ��2
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
��������У�sort�ĵ���������Ӧ����������������ͨ��lambda���ʽ��ֱ�ӽ��������ĺ����嶨�������棬���ڲ���Ҫ�����ұȽ�С�ĺ���������д���ܺ�
��python�� lambda���� 
����
add = lambda a,b: a+ b ǰ���ǲ������������Ǳ��ʽ

Lambda���ʽ���ŵ�
����ֱ������Ҫ���ú�����λ�ö����С�����ĺ�����������ҪԤ�ȶ���ú���
std::find_if(v.begin(), v.end(), [](int& item){return item > 2});
1
ʹ��Lamdba���ʽ��ø��ӽ��գ��ṹ��θ������ԡ�����ɶ��Ը���
Lambda���ʽ��ȱ��
Lamdba���ʽ�﷨�Ƚ����������Ķ�������Ѷ�
���ں�����������Ϊ��

Lambda���ʽ����ԭ��
���������һ��Lambda���ʽ����һ����������������󣬲����������غ��������������ʵ����һ��operator()������

auto print = []{cout << "Hello World!" << endl; };
1
���������������һ�䷭��Ϊ����Ĵ��룺

class print_class
{
public:
	void operator()(void) const
	{
		cout << "Hello World!" << endl;
	}
};
// �ù�����ഴ������print��ʱ����һ����������
auto print = print_class();



####std::function and std::bind �ṹ��

function��bind ��c++�ж��ڻص���������ͳһ�ĵ��úͷ�װ
���ȣ�c++�еĿɵ��ú������Զ��庯����lambda���ʽ�� ����ָ�룬bind���󣬺�������

����ָ�����ɺ��������ͷ������;�����
���ں���ָ�������
```
# include <iostream>

int fun(int x, int y) {                         //�����õĺ���
    std::cout << x + y << std::endl;
	return x + y;
}

int fun1(int (*fp)(int, int), int x, int y) {   //�β�Ϊ����ָ��
	return fp(x, y);
}

typedef int (*Ftype)(int, int);                 //����һ������ָ������Ftype
int fun2(Ftype fp, int x, int y) { 
	return fp(x, y);
}

int main(){
	fun1(fun, 100, 100);                          //����fun1���ú���fun
	fun2(fun, 200, 200);                          //����fun2���ú���fun
}


```
���Կ�������������Ϊһ������������һ�������Ĳ���

lambda���ʽ�����ԣ���֮���ǲ�����һ����������ĵ��ã����Ա�֤��ȫ��

�������������˺�����������������Ķ�����Ǻ�������

�ɵ��ö���Ķ��巽ʽ�ܶ൫�Ǻ����ĵ��ö������ƣ���Ҫһ��ͳһ�ķ�ʽ������ɵ��ö���
����std::function�ͳ�����
std::function��һ���ɵ��ö����װ������һ����ģ�壬�������ɳ������Ա����ָ��֮������пɵ��ö���
��������ͳһ�ķ�ʽ���������������󡢺���ָ�룬����������ӳ����ǵ�ִ�С�
����std����function
```
#include <functional>
std::function<type>

```
����
```
# include <iostream>
# include <functional>

typedef std::function<int(int, int)> comfun;//������һ������Ϊ int��int��int����comfun ģ��

// ��ͨ����
int add(int a, int b) { return a + b; }

// lambda���ʽ
auto mod = [](int a, int b){ return a % b; };

// ����������
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
//comfun ������Ϊģ���� �൱�ڴ�����һ��a���󣬽�add������divide��Ĵ��ȥ
���˺����ĵ���


####std::bind
bind ��һ��ͨ�ú�������������ͨ������һ���ɵ��õĺ�����������һ���µĿɵ��ö�������Ӧԭ�����б�
bind����˼���ǰ󶨵���˼�����Խ������Ͳ����б�󶨣�Ȼ������function����

bind�ĵ���

auto newfuntion = bind(function,argc_list)
//�ñ��ʽ��Ϊ ����newfunctionʱ�������function���Ҵ���argc_list�еĲ���

����ʹ�ô���
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
    //f1������Ϊ function<void(int, int, int)>
    auto f1 = std::bind(fun_1, 1, 2, 3); 					//��ʾ�󶨺��� fun �ĵ�һ��������������ֵΪ�� 1 2 3
    f1(); 													//print: x=1,y=2,z=3

    auto f2 = std::bind(fun_1, std::placeholders::_1, std::placeholders::_2, 3);
    //��ʾ�󶨺��� fun �ĵ���������Ϊ 3����fun �ĵ�һ�����������ֱ��ɵ��� f2 �ĵ�һ����������ָ��
    f2(1, 2);												//print: x=1,y=2,z=3
 
    auto f3 = std::bind(fun_1, std::placeholders::_2, std::placeholders::_1, 3);
    //��ʾ�󶨺��� fun �ĵ���������Ϊ 3����fun �ĵ�һ�����������ֱ��ɵ��� f3 �ĵڶ���һ������ָ��
    //ע�⣺ f2  ��  f3 ������
    f3(1, 2);												//print: x=2,y=1,z=3

    int m = 2;
    int n = 3;
    auto f4 = std::bind(fun_2, std::placeholders::_1, n); //��ʾ��fun_2�ĵ�һ������Ϊn, fun_2�ĵڶ��������ɵ���f4�ĵ�һ��������_1��ָ����
    f4(m); 													//print: a=3,b=4
    std::cout << "m = " << m << std::endl;					//m=3  ˵����bind���ڲ����Ȱ󶨵Ĳ�����ͨ��std::placeholders���ݵĲ�����ͨ�����ô��ݵ�,��m
    std::cout << "n = " << n << std::endl;					//n=3  ˵����bind����Ԥ�Ȱ󶨵ĺ���������ͨ��ֵ���ݵģ���n
    
    A a;
    //f5������Ϊ function<void(int, int)>
    auto f5 = std::bind(&A::fun_3, &a, std::placeholders::_1, std::placeholders::_2); //ʹ��auto�ؼ���
    f5(10, 20);												//����a.fun_3(10,20),print: k=10,m=20

    std::function<void(int,int)> fc = std::bind(&A::fun_3, a,std::placeholders::_1,std::placeholders::_2);
    fc(10, 20);   											//����a.fun_3(10,20) print: k=10,m=20 

    return 0; 
}
std::placeholders::_1 �� C++ ��׼���е�һ��ռλ����placeholder�������� std::bind ����ģ�塣ռλ���������ڰ�һ���������Ա����ʱ���ӳ�ָ��ĳЩ������ֱ��ʵ�ʵ���ʱ�ٴ�����Щ������
 auto f2 = std::bind(fun_1, std::placeholders::_1, std::placeholders::_2, 3);
    //��ʾ�󶨺��� fun �ĵ���������Ϊ 3����fun �ĵ�һ�����������ֱ��ɵ��� f2 �ĵ�һ����������ָ��
    f2(1, 2);												//print: x=1,y=2,z=3
std::placehoulders��һ�������������ڵ���ʱ��ʱ�������������Ϳ����ڵ���ʱʹ��f2(1,2),������f2()
    auto f3 = std::bind(fun_1, std::placeholders::_2, std::placeholders::_1, 3);
    //��ʾ�󶨺��� fun �ĵ���������Ϊ 3����fun �ĵ�һ�����������ֱ��ɵ��� f3 �ĵڶ���һ������ָ��
    //ע�⣺ f2  ��  f3 ������
    f3(1, 2);												//print: x=2,y=1,z=3
�� std::placeholder::1��2�ǲ�һ����
```
 int m = 2;
    int n = 3;
    auto f4 = std::bind(fun_2, std::placeholders::_1, n); //��ʾ��fun_2�ĵ�һ������Ϊn, fun_2�ĵڶ��������ɵ���f4�ĵ�һ��������_1��ָ����
    f4(m); 													//print: a=3,b=4
    std::cout << "m = " << m << std::endl;					//m=3  ˵����bind���ڲ����Ȱ󶨵Ĳ�����ͨ��std::placeholders���ݵĲ�����ͨ�����ô��ݵ�,��m
    std::cout << "n = " << n << std::endl;					//n=3  ˵����bind����Ԥ�Ȱ󶨵ĺ���������ͨ��ֵ���ݵģ���n

    bind����placeholder�����������ô��ݣ�����a��bc֮�����ͨ��ֵ���ݵ�


    Ϊʲô auto f5 = std::bind(&A::fun_3, &a, std::placeholders::_1, std::placeholders::_2);Ҫ��&a��
    ��C++�У�����ʹ�� std::bind ��һ����Ա����ʱ����Ҫ����һ�������ָ������ã���Ϊ��Ա��������ͨ��������á���Ա��������ͨ������ͬ�������������ض��Ķ���ʵ�����������ܷ��ʶ���ĳ�Ա���ݺ�������Ա����
    ������ʹ��bind��Ҫʵ����