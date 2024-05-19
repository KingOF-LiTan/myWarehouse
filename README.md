# c++ STL��

#### ����	
stl��������������õı���д��ĺ��� �������


#### STL��ɶ������
STL,ѧ��Standard Template Library��һ�����ǳ���Ϊ��׼ģ���
�Ӹ�����˵��STL��һЩ���������ļ��ϣ���Щ����������list,vector,set,mapһ��ѣ�STLҲ����
��������һЩ����ļ��ϡ�����˵<algorithm>��sort������<string>��string�඼
��STL�����ݡ�
stl���滹������漰��c++�ĸ߼����õĶ���������˵�Ӵ�����Щ�����ǿ�ʼ�Ӵ�c++�ľ���
��vector���� set���� mapӳ�� stackջ queue����	priority queue���ȶ��� list����
�Լ�max min sort ���㷨

#### ���� sort
��ţ�ƵĲ��ȶ�����
�ٶ�����
�����Զ���ȽϺ�����ʽ��
void sort(Ҫ����Ԫ�ص���ʼ��ַ��Ҫ����Ԫ�صĽ�����ַ���ȽϺ���)��
֮ǰ���ű������ǿ�����ô���ˡ�����
�ȽϺ�������ȱʡ��Ĭ�ϴ�С����

####CMP����
�ȽϺ������ǿ����Լ��Զ���
```
#include<algorithm>
#include<iostream>
using namespace std;
bool cmp(int x,int y)
{
	if(x>y)return true;//����
	return false;
}
int main()
{
	int a[]={3,5,2,6,9,3,5};
	sort(a,a+7,cmp);//7�������Ԫ�ظ���
	for(int i=0;i<6;i++)
		cout<<a[i]<<" ";
		
}
```
####CMP��ṹ��
ͬѧ�Ǳ����Է���������Ա�ֱ�Ϊ�������ͽ�����������ɷ����ϰˡ��Լ�����ͬѧ��˭�Եĸ���˭�����ڸ�ǰ�棬����Ե�һ������ô˭�Ե��ϰ˺�����˭�����ڸ�ǰ�棺
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
	else if(x.hanbao>y.hanbao&&x.zongshu==y.zongshu)//���һ������ô��˭�Եĺ�����
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

#### ʹ��˵��

1.  xxxx
2.  xxxx
3.  xxxx

#### ���빱��

1.  Fork ���ֿ�
2.  �½� Feat_xxx ��֧
3.  �ύ����
4.  �½� Pull Request


#### �ؼ�

1.  ʹ�� Readme\_XXX.md ��֧�ֲ�ͬ�����ԣ����� Readme\_en.md, Readme\_zh.md
2.  Gitee �ٷ����� [blog.gitee.com](https://blog.gitee.com)
3.  ����� [https://gitee.com/explore](https://gitee.com/explore) �����ַ���˽� Gitee �ϵ����㿪Դ��Ŀ
4.  [GVP](https://gitee.com/gvp) ȫ���� Gitee ���м�ֵ��Դ��Ŀ�����ۺ������������㿪Դ��Ŀ
5.  Gitee �ٷ��ṩ��ʹ���ֲ� [https://gitee.com/help](https://gitee.com/help)
6.  Gitee ����������һ������չʾ Gitee ��Ա��ɵ���Ŀ [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)