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

