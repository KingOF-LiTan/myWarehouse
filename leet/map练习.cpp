#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
using namespace std;
int N, a[1000010], b[1000010];
map<int, int> m;
int main() {
	cin >> N;
	for (int i = 0; i <N; i++) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b, b + N);
	int c = 1;
	m[b[0]] = 1;
	for (int i = 1; i < N; i++) {
		if (b[i] != b[i - 1]) {
			c++;
			m[b[i]] = c;
		}
	}
	for (int i = 0; i < N; i++) {
		if (m[a[i]] != 0) {
			cout << m[a[i]] << " ";
		}
	}
	return 0;
}