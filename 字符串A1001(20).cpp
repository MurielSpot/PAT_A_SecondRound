/*
1001. A+B Format (20)
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
Calculate a + b and output the sum in standard format -- that is, the digits must be separated into groups of three by commas (unless there are less than four digits).

Input

Each input file contains one test case. Each case contains a pair of integers a and b where -1000000 <= a, b <= 1000000. The numbers are separated by a space.

Output

For each test case, you should output the sum of a and b in one line. The sum must be written in the standard format.

Sample Input
-1000000 9
Sample Output
-999,991
*/

/*
ac:1次

难度:1

注意事项:
1. 下面第一个代码中,需特判0,因为0时,无法存入到字符串数组里,会什么都不输出.

思路:
1. 把数转成字符串,根据字符串中字符下标和逗号的关系加入逗号输出.

做题技巧:
1. 用string,里面有直接把数转为字符串的函数.string sum = to_string(a + b).
2. 求string字符串长度的函数s.length().
*/

#include<cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include<cmath> 
#include<queue>
using namespace std;

const int MAXN = 22;
const int INF = 1000000000;

char str[MAXN];
int strPtr=1;//[1,strPtr)里是字符串.strPtr存的是\0.

int a,b,sum;

int int2str(){
	int x = sum;
	while(x){
		str[strPtr++]=x%10+'0';
		x/=10;
	}
	str[strPtr]='\0';
}

int main() {
	cin>>a>>b;
	sum=a+b;
	if(sum<0){
		printf("-");
		sum=0-sum;
	}
	
	if (sum == 0) {
		printf("0");//特判.
	}
	else {
		int2str();
		strPtr--;
		for (int i = strPtr; i >= 1; i--) {
			if (i != strPtr && i % 3 == 0) {
				printf(",%c", str[i]);
			}
			else {
				printf("%c", str[i]);
			}
		}
	}
	return 0;
}

