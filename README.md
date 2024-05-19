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
####vector�ļ򵥽���
�������У�����Ҳ��һά�Ĵ洢��ʽ���������Ϊ���ȿɱ�Ķ�̬����
��β����ɾ��Ч�ʸߣ�����ӵ�кܸߵķ���Ч��
vector ����Ƕ��ʹ��
��
```
#include <iostream> 
#include <vector> 
using namespace std;
// �����������
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
�൱�ڽ�subv���뵽v��β�����γ�һ����ά����
����һЩ��vector�г����Ĳ���
```
    int size = vec1.size();         //Ԫ�ظ���
 
    bool isEmpty = vec1.empty();    //�ж��Ƿ�Ϊ��
 
    vec1.insert(vec1.end(),5,3);    //��vec1.backλ�ò���5��ֵΪ3��Ԫ��
 
    vec1.pop_back();              //ɾ��ĩβԪ��
 
    vec1.erase(vec1.begin(),vec1.end());//ɾ��֮���Ԫ�أ�����Ԫ��ǰ��
 
    cout<<(vec1==vec2)?true:false;  //�ж��Ƿ����==����=��>=��<=...
 
    vector<int>::iterator iter = vec1.begin();    //��ȡ�������׵�ַ
 
    vector<int>::const_iterator c_iter = vec1.begin();   //��ȡconst���͵�����
 
    vec1.clear();                 //���Ԫ��

```
c++����������������÷�
iterator 
����
 ```
    vector<int> V;
    V.push_back(1);
	V.push_back(2);
	V.push_back(3);
	for(vector<int>::iterator it=v.begin();it!=v.end();it++)
	cout<<*it<<
 ```
 ��֪������Ҫ����ͬ�����ݽṹ��ʼ��
 it�ǵ�����ָ��

 ####string
 ��vectorʮ�����Ƶ���������c��string�����Ǻܴ�


