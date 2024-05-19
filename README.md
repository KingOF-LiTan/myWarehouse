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

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)