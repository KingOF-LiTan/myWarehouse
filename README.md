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

#### MAP
map��stl��һ����������
what is ����������
��C++�У�����������һ�������������ܹ�ͨ�������洢�ͷ���Ԫ�أ��ṩ�˿��ٵ����ݼ������ܡ���Щ����ͨ������ƽ�����������ϣ���������Ч�����ݽṹʵ�֡�
C++ STL����׼ģ��⣩�ṩ�����¼��ֹ���������
set���洢ΨһԪ�صļ��ϣ�Ԫ�ذ����������С�
multiset�����Դ洢�ظ�Ԫ�صļ��ϣ�Ԫ��ͬ�������������С�
map��ʹ�ü�ֵ�Դ洢���ݣ�ÿ��������Ψһ�ģ����Ұ����������С�
multimap���������ظ��ļ���ÿ�������Զ�Ӧ���ֵ����ֵ�԰����������С�
unordered_set�����ڹ�ϣ��ʵ�ֵļ��ϣ�����֤Ԫ��˳���ṩƽ������ʱ�临�Ӷȵĳ�Ա��顣
unordered_multiset�������� unordered_set�����������ظ�Ԫ�ء�
unordered_map�����ڹ�ϣ��ʵ�ֵļ�ֵ��ӳ�䣬����֤Ԫ��˳���ṩƽ������ʱ�临�Ӷȵĳ�Ա��顣
unordered_multimap�������� unordered_map�����������ظ��ļ���
map��hash�Ĺ�ϵ�ܲ��ɷ�

map���� map<����,����> m;
��һ���ǹؼ��� ���� key �ڶ�����ֵvalue
��python�е�������ͬС�� ��������ֵ䣿
����
```
#include<map>
#include<iostream>
using namespace std;
int main()
{
	map<string,string> m;
	m["����"]="�Ժ���";
	cout<<"����: "<<m["����"]; 
}
```
ÿ������Ψһ��Ӧ��ֵ
���ӣ�
��ɢ������
���룺

5
8 2 6 9 2

�����

3 1 2 4 1
���ÿ����������
���������sort��map��
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
    sort(b,b+N);//����������
    int c=1;//����
    m[b[0]]=1;//��Ϊ���龭���������Ե�1��Ԫ�ؿ϶��ǵ�һ
    for(int i=1;i<N;i++)
    {
        if(b[i]!=b[i-1])//�ж��Ƿ���ǰһ�������
        {
            c++;
            m[b[i]]=c;
        }
    }
    for(int i=0;i<N;i++)
        if(m[a[i]]!=0)
            cout<<m[a[i]]<<" ";//����ԭ�����±����
    
    return 0;
}
```

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