
//正常表达式都是中值表达式 如4+3=7对人好看，但是对计算机不友好
//计算机需要从4+3再继续扫描进行匹配是否可以运算以及优先级
//将中缀表达式转化成后缀表达式就可以使计算机直接计算
//相当于二叉树的后序遍历
//tokens = ["2","1","+","3","*"]
//((2 + 1) * 3) = 9
//用栈实现的经典东西


#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
using namespace std;
#define MAX 100000140;

class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack<int> st;
		for (int i = 0; i < tokens.size(); i++) {
			if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/"  ) {
				int  num1 = st.top();
					st.pop();
					int num2 = st.top();
					st.pop();
					if (tokens[i] == "+")  st.push(num2 + num1);
					if (tokens[i] == "-")  st.push(num2 -num1);
					if (tokens[i] == "*")  st.push(num2 * num1);
					if (tokens[i] == "/")  st.push(num2 / num1);
			}
			else {
				st.push(stoi(tokens[i]));//stoi 是一个标准库函数，用于将字符串转换为整数
			}


		}
		int result = st.top();
		st.pop();
		return result;
	}


};



vector<string> tokenize(string str) {
	vector<string> tokens;
	stringstream ss(str);
	string token;
	while (ss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

int main() {
	string input;
	cout << "Enter the RPN expression: ";
	getline(cin, input);

	vector<string> tokens = tokenize(input);
	Solution solution;
	int result = solution.evalRPN(tokens);

	cout << "The result is: " << result << endl;
	return 0;
}