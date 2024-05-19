# c++ STL库

#### 介绍	
stl库里面有许多有用的别人写完的函数 例如快排


#### STL是啥东西？
STL,学名Standard Template Library，一般我们称他为标准模板库
从根本上说，STL是一些“容器”的集合，这些“容器”有list,vector,set,map一大堆，STL也是算
法和其他一些组件的集合。比如说<algorithm>中sort函数、<string>中string类都
是STL的内容。
stl里面还有许多涉及到c++的高级运用的东西，可以说接触到这些才算是开始接触c++的精髓
如vector向量 set集合 map映射 stack栈 queue队列	priority queue优先队列 list链表
以及max min sort 等算法

#### 快排 sort
很牛逼的不稳定排序
速度贼快
可以自定义比较函数格式：
void sort(要排序元素的起始地址，要排序元素的结束地址，比较函数)；
之前蓝桥杯就忘记快排怎么用了。。。
比较函数可以缺省，默认从小到大

####CMP快排
比较函数我们可以自己自定义
```
#include<algorithm>
#include<iostream>
using namespace std;
bool cmp(int x,int y)
{
	if(x>y)return true;//降序
	return false;
}
int main()
{
	int a[]={3,5,2,6,9,3,5};
	sort(a,a+7,cmp);//7是数组的元素个数
	for(int i=0;i<6;i++)
		cout<<a[i]<<" ";
		
}
```
####CMP与结构体
同学们比赛吃饭，参赛队员分别为“法外狂徒张三”，“干饭者老八”以及王五同学，谁吃的更多谁就排在更前面，如果吃的一样多那么谁吃的老八汉堡多谁就排在更前面：
```
#include<algorithm>
#include<iostream>
using namespace std;
struct ganfan
{
	string name;
	int zongshu;
	int hanbao;
};
bool cmp(ganfan x,ganfan y)
{
	if(x.zongshu>y.zongshu)return true;
	else if(x.hanbao>y.hanbao&&x.zongshu==y.zongshu)//如果一样多那么比谁吃的汉堡多
	return false;
}
int main()
{
	ganfan a[3];
	a[0].name="zhangsan";a[0].zongshu=200;a[0].hanbao=6;
	a[1].name="laoba";a[1].zongshu=170;a[1].hanbao=13;
	a[2].name="wangwu";a[2].zongshu=170;a[2].hanbao=10;
	sort(a,a+3,cmp);
	for(int i=0;i<3;i++)
		cout<<a[i].name<<" ";
}
```

#### MAP
map是stl的一个关联容器
what is 关联容器？
在C++中，关联容器是一类容器，它们能够通过键来存储和访问元素，提供了快速的数据检索功能。这些容器通常基于平衡二叉树、哈希表或其他高效的数据结构实现。
C++ STL（标准模板库）提供了以下几种关联容器：
set：存储唯一元素的集合，元素按照升序排列。
multiset：可以存储重复元素的集合，元素同样按照升序排列。
map：使用键值对存储数据，每个键都是唯一的，并且按照升序排列。
multimap：允许有重复的键，每个键可以对应多个值，键值对按照升序排列。
unordered_set：基于哈希表实现的集合，不保证元素顺序，提供平均常数时间复杂度的成员检查。
unordered_multiset：类似于 unordered_set，但允许有重复元素。
unordered_map：基于哈希表实现的键值对映射，不保证元素顺序，提供平均常数时间复杂度的成员检查。
unordered_multimap：类似于 unordered_map，但允许有重复的键。
map和hash的关系密不可分

map定义 map<类型,类型> m;
第一个是关键字 即键 key 第二个即值value
和python中的容器大同小异 可以类比字典？
例子
```
#include<map>
#include<iostream>
using namespace std;
int main()
{
	map<string,string> m;
	m["张三"]="吃汉堡";
	cout<<"张三: "<<m["张三"]; 
}
```
每个键有唯一对应的值
例子：
离散化基础
输入：

5
8 2 6 9 2

输出：

3 1 2 4 1
输出每个数的排名
这题可以用sort和map做
```
#include<bits/stdc++.h>
using namespace std;
int N,a[100001],b[100001];
map<int,int> m;
int main(){
    
    cin>>N;
    for(int i=0;i<N;i++)
    {
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b,b+N);//将数组排序
    int c=1;//排名
    m[b[0]]=1;//因为数组经过排序，所以第1个元素肯定是第一
    for(int i=1;i<N;i++)
    {
        if(b[i]!=b[i-1])//判断是否不与前一个数相等
        {
            c++;
            m[b[i]]=c;
        }
    }
    for(int i=0;i<N;i++)
        if(m[a[i]]!=0)
            cout<<m[a[i]]<<" ";//按照原来的下标输出
    
    return 0;
}
```
####vector的简单介绍
在容器中，向量也是一维的存储形式，可以理解为长度可变的动态数组
在尾部增删的效率高，并且拥有很高的访问效率
vector 可以嵌套使用
如
```
#include <iostream> 
#include <vector> 
using namespace std;
// 程序的主函数
int main()
{
	vector<vector<int>> V;
	vector<int> sub_V;
	sub_V.push_back(1);
	sub_V.push_back(2);
	sub_V.push_back(1);
	V.push_back(sub_V);
	cout << V[0][1] << endl;
	system("pause");
	return 0;
}	

```
相当于将subv插入到v的尾部，形成一个二维数组
这是一些在vector中常见的操作
```
    int size = vec1.size();         //元素个数
 
    bool isEmpty = vec1.empty();    //判断是否为空
 
    vec1.insert(vec1.end(),5,3);    //从vec1.back位置插入5个值为3的元素
 
    vec1.pop_back();              //删除末尾元素
 
    vec1.erase(vec1.begin(),vec1.end());//删除之间的元素，其他元素前移
 
    cout<<(vec1==vec2)?true:false;  //判断是否相等==、！=、>=、<=...
 
    vector<int>::iterator iter = vec1.begin();    //获取迭代器首地址
 
    vector<int>::const_iterator c_iter = vec1.begin();   //获取const类型迭代器
 
    vec1.clear();                 //清空元素

```
c++赋予了其迭代器的用法
iterator 
例如
 ```
    vector<int> V;
    V.push_back(1);
	V.push_back(2);
	V.push_back(3);
	for(vector<int>::iterator it=v.begin();it!=v.end();it++)
	cout<<*it<<
 ```
 可知迭代器要用相同的数据结构初始化
 it是迭代器指针

 ####string
 和vector十分相似的容器，和c的string区别不是很大，


