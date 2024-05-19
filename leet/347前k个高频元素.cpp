#define _CRT_SECURE_NO_WARNINGS 1

#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
using namespace std;
#define MAX 100000140;
#include <unordered_map>
//寻找前k频率的元素 可以用map统计
//一重容器的运用即优先队列
//优先队列的接口其实是一个队列皮的堆
//只能从队头出，队尾入，再无别的队列特征
//根据map的建值自动匹配
//大顶堆和小顶堆 
//堆是完全二叉树，即每个节点权值大于等于左右孩子，大顶堆即父节点的值大于等于左右孩子的值

/*
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。



示例 1:

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
*/
//可以用小顶堆，每次弹出元素频率最小的元素，即他们的爹 最后的就是最大的

class Solution {
public:
	//小顶堆
	class mycomparison {
	public:
		bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
			return lhs.second > rhs.second;
		}
	};
	vector<int> topKFrequent(vector<int>& nums, int k) {
		//统计元素出现个数
		unordered_map<int, int>map;//map <nums[i] 
		for (int i = 0; i < nums.size(); i++) {
			map[nums[i]]++;
		}
		//排序元素次序
		//定义大小为k的小顶堆
		priority_queue < pair<int, int>, vector<pair<int, int>>, mycomparison >pri_que;
		//这个优先队列将使用 vector<pair<int, int>> 作为其底层容器，并且使用自定义的比较函数 mycomparison 来确定元素的优先级顺序。
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