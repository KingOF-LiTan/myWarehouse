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
