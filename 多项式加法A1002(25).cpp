/*
ac:1;时长:20分钟左右;难度:1.

注意事项:
1. 系数为0表名没有值.
2. 第二个多项式录入时可以直接加到第一个多项式里,不需要另外设数组.

其他:是加法,不是多项式乘法,差点按乘法做.另外总感觉多项式的题不容易做.
*/
#include<cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include<cmath> 
#include<queue>
using namespace std;

#define P 0
#if P
int tmpDebug;
#endif

const int MAXN = 1010;
const int INF = 1000000000;

int k;
struct info {
	int e;
	double c;
	info() {
		c = 0;
		e = 0;
	}
	info(int e_, double c_) {
		e = e_;
		c = c_;
	}
}num[MAXN];

int main() {
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int e; double c;
		scanf("%d %lf", &e, &c);
		num[e] = info(e, c);
	}
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int e; double c;
		scanf("%d %lf", &e, &c);
		num[e].e = e;
		num[e].c += c;
	}
	vector<info> ans;
	for (int i = MAXN - 1; i >= 0; i--) {
		if (num[i].c) {
			ans.push_back(num[i]);
		}
	}
	printf("%d", ans.size());
	for (int i = 0; i < ans.size(); i++) {
		printf(" %d %.1lf", ans[i].e, ans[i].c);
	}
	return 0;
}
