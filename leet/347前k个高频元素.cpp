#define _CRT_SECURE_NO_WARNINGS 1

#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
using namespace std;
#define MAX 100000140;
#include <unordered_map>
//Ѱ��ǰkƵ�ʵ�Ԫ�� ������mapͳ��
//һ�����������ü����ȶ���
//���ȶ��еĽӿ���ʵ��һ������Ƥ�Ķ�
//ֻ�ܴӶ�ͷ������β�룬���ޱ�Ķ�������
//����map�Ľ�ֵ�Զ�ƥ��
//�󶥶Ѻ�С���� 
//������ȫ����������ÿ���ڵ�Ȩֵ���ڵ������Һ��ӣ��󶥶Ѽ����ڵ��ֵ���ڵ������Һ��ӵ�ֵ

/*
����һ���������� nums ��һ������ k �����㷵�����г���Ƶ��ǰ k �ߵ�Ԫ�ء�����԰� ����˳�� ���ش𰸡�



ʾ�� 1:

����: nums = [1,1,1,2,2,3], k = 2
���: [1,2]
*/
//������С���ѣ�ÿ�ε���Ԫ��Ƶ����С��Ԫ�أ������ǵĵ� ���ľ�������

class Solution {
public:
	//С����
	class mycomparison {
	public:
		bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
			return lhs.second > rhs.second;
		}
	};
	vector<int> topKFrequent(vector<int>& nums, int k) {
		//ͳ��Ԫ�س��ָ���
		unordered_map<int, int>map;//map <nums[i] 
		for (int i = 0; i < nums.size(); i++) {
			map[nums[i]]++;
		}
		//����Ԫ�ش���
		//�����СΪk��С����
		priority_queue < pair<int, int>, vector<pair<int, int>>, mycomparison >pri_que;
		//������ȶ��н�ʹ�� vector<pair<int, int>> ��Ϊ��ײ�����������ʹ���Զ���ıȽϺ��� mycomparison ��ȷ��Ԫ�ص����ȼ�˳��
		for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
			pri_que.push(*it);
			if (pri_que.size() > k) {
				pri_que.pop();
			}
		}
		vector<int> result(k);
		for (int i = k - 1; i >= 0; i--) {
			result[i] = pri_que.top().first;
			pri_que.pop();
		}
		return result;
	}

};