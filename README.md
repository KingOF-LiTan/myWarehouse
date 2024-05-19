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

#####CMP快排
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

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

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