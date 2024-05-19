
//�������ʽ������ֵ���ʽ ��4+3=7���˺ÿ������ǶԼ�������Ѻ�
//�������Ҫ��4+3�ټ���ɨ�����ƥ���Ƿ���������Լ����ȼ�
//����׺���ʽת���ɺ�׺���ʽ�Ϳ���ʹ�����ֱ�Ӽ���
//�൱�ڶ������ĺ������
//tokens = ["2","1","+","3","*"]
//((2 + 1) * 3) = 9
//��ջʵ�ֵľ��䶫��


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
				st.push(stoi(tokens[i]));//stoi ��һ����׼�⺯�������ڽ��ַ���ת��Ϊ����
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