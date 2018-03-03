/*
1005. Spell It Right (20)
时间限制 
400 ms
内存限制 
65536 kB
代码长度限制 
16000 B
判题程序 
Standard 
作者 
CHEN, Yue
Given a non-negative integer N, your task is to compute the sum of all the digits of N, and output every digit of the sum in English. 
Input Specification: 
Each input file contains one test case. Each case occupies one line which contains an N (<= 10100). 
Output Specification: 
For each test case, output in one line the digits of the sum in English words. There must be one space between two consecutive words, but no extra space at the end of a line. 
Sample Input:
12345
Sample Output:
one five
*/
/*
ac:1次;时长:10分钟;难度:1.

注意事项:
1. 要考虑和为0的情况.翻成英文没有什么特别规律,对应成相应英文就行了.其它也没有什么坑点.
*/
#include<cstdio>
#include<iostream>

#include <string>
#include <cstring>

#include <algorithm>
#include<cmath> 

#include<vector>
#include<stack>
#include<queue>

#include<map>
using namespace std;

#define P 0

const int MAXN = 110;
const int INF = 1000000000;

int n;
char num[MAXN];

int main() {
	cin >> num;
	int len = strlen(num);
	int sum = 0;
	for (int i = 0; i < len; i++) {
		sum += num[i] - '0';
	}
	int i = 0;
	if (sum == 0)printf("zero");//特判.
	else {
		while (sum) {
			num[i++] = sum % 10;
			sum /= 10;
		}
		char hash[10][6] = { "zero","one","two","three","four","five","six","seven","eight","nine" };
		while (i--) {
			if (i) {
				printf("%s ", hash[num[i]]);
			}
			else {
				printf("%s", hash[num[i]]);
			}
		}
	}
	return 0;
}
