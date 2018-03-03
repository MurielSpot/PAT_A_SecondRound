/*
有三种做法:
1. 只用dfs.这道题比较简单用这种方法即可.
2. 用dijkstra+dfs.复杂一点.
3. 指用dijkstra,可增加记录当前路径条数和汇集到的帮手的人数的数组,在每次找到最近结点之后对发现路径更近或路径相同帮手更多则对数组进行更新,思路比较复杂,不过也能做出来.(由于dijkstra经过n次循环之后,计算完了n个结点,到每个结点时,到这个结点的最大帮手数都是到这个结点时最优的,而与它相连的下一个结点肯定等于之前这个局部最优的最大值,加上下一个结点本身的帮手数,所以这种局部更新帮手数的方法不会出错.)

方法一:ac:1次,时长:31分钟,难度:2.
方法二:ac:1次,时长:20分钟左右,难度2.

注意事项:
1. 针对指用dfs的方法:
** 剪枝可以删,没有超时.
2. 针对第二种方法:
** 出了不少细节错误,比如把赋值等号=写成比较的等号==,最短路径找出新的最近结点时没有标记已访问vis[]=true,结果让输出最短路径条数和最大成员数,我输出成了最短路径经过的各个结点.
这些浪费了差不多十分钟时间调试.
** 最短路径中容易出错的地方:找最小dist时,要在未访问的结点中找,更新dist时,也是更新未访问结点的;找到dist最小的结点之后,应该标记已访问.
** vector不能用memset全部赋值为-1,我记得之前试过,赋值为全0不会异常退出,但是赋值为全-1,会异常退出.
*/
//dfs
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

const int MAXN = 510;
const int INF = 1000000000;

void connectedOutput();

int n;//cities.[0,n-1].
int m;//roads.
int c1, c2;

int team[MAXN] = { 0 };
int road[MAXN][MAXN] = { 0 };

bool vis[MAXN] = { false };
int maxTeam = -1;
int minDist = INF;
int cnt = 0;
void dfs(int u,int sumTeam,int sumDist) {
#if P
	connectedOutput();
	printf("cnt=%d,minDist=%d,maxTeam=%d\n", cnt, minDist, maxTeam);
	printf("   u=%d,sumTeam=%d,sumDist=%d\n", u, sumTeam, sumDist);
#endif
	vis[u] = true;
	if (u == c2) {
		//cnt++;//这里并不总是需要cnt++;
		if (sumDist < minDist) {
			minDist = sumDist;
			maxTeam = sumTeam;
			cnt = 1;
		}
		else if (sumDist == minDist) {
			cnt++;
			if (sumTeam > maxTeam) {
				maxTeam = sumTeam;
			}
		}
		vis[u] = false;
		return;
	}
	if (sumDist > minDist) {//这个剪枝如果删掉,也能通过,不过第五个测试点运行的时间会从几ms变为70多ms.
		vis[u] = false;
		return;//剪枝.
	}
	for (int i = 0; i < n; i++) {
		if (road[i][u] != 0&&vis[i]==false) {
			dfs(i, sumTeam + team[i], sumDist + road[i][u]);
		}
	}
	vis[u] = false;
}
void connectedOutput() {
	printf("\n----------------------------\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (vis[i] == false && vis[j] == false) {
				printf("[%d]-[%d]:%d\n", i, j, road[i][j]);
			}
		}
	}
	printf("----------------------------\n");
}
int main() {
	cin >> n >> m >> c1 >> c2;
	for (int i = 0; i < n; i++) {
		scanf("%d", &team[i]);
	}
	for (int i = 0; i < m; i++) {
		int t1, t2, len;
		scanf("%d%d%d", &t1, &t2, &len);
		road[t1][t2] = road[t2][t1] = len;
	}
	dfs(c1,team[c1],0);
	printf("%d %d\n", cnt, maxTeam);
	return 0;
}


//dijkstra+dfs
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

const int MAXN = 510;
const int INF = 1000000000;

int n;//cities.[0,n-1].
int m;//roads.
int c1, c2;

int team[MAXN] = { 0 };
int road[MAXN][MAXN] = { 0 };

bool vis[MAXN] = { false };
vector<int> pre[MAXN];
int dist[MAXN];
void dijkstra(int u) {
	//memset(pre, -1, sizeof(pre));//用的vector，就不能再memset了！
	fill(dist, dist + MAXN, INF);
	dist[u] = 0;

	for (int i = 0; i < n; i++) {
		int minDist = INF, minIndex = -1;
		for (int i = 0; i < n; i++) {
			if (dist[i] < minDist&&vis[i] == false) {
				minDist = dist[i];//寫成了==導致出錯.
				minIndex = i;
			}
		}
#if P
		printf("minIndex=%d,minDist=%d\n", minIndex , minDist);
#endif
		if (minIndex == -1)break;
		vis[minIndex] = true;//这一句不要忘了！
		for (int i = 0; i < n; i++) {
			if (road[i][minIndex] != 0 && vis[i] == false) {
#if P
				printf("   dist[i]=%d,minDist+road[i][minIndex]=%d\n", dist[i] , minDist + road[i][minIndex]);
#endif
				if (dist[i] > minDist + road[i][minIndex]) {
					dist[i] = minDist + road[i][minIndex];
					pre[i].clear();
					pre[i].push_back(minIndex);
				}
				else if (dist[i] == minDist + road[i][minIndex]) {
					pre[i].push_back(minIndex);
				}
			}
		}
	}
}

int maxTeam = -1;
int cnt = 0;
//vector<int> ans, tmp;
void dfs(int u,int sumteam) {
	//tmp.push_back(u);
	if (u == c1) {
		cnt++;
		if (sumteam > maxTeam) {
			//ans = tmp;
			maxTeam = sumteam;
		}
		//tmp.pop_back();
		return;
	}
	for (int i = pre[u].size() - 1; i >= 0; i--) {
		int v = pre[u][i];
		dfs(v, team[v] + sumteam);
	}
	//tmp.pop_back();
}

int main() {
	cin >> n >> m >> c1 >> c2;
	for (int i = 0; i < n; i++) {
		scanf("%d", &team[i]);
	}
	for (int i = 0; i < m; i++) {
		int t1, t2, len;
		scanf("%d%d%d", &t1, &t2, &len);
		road[t1][t2] = road[t2][t1] = len;
	}
	dijkstra(c1);
	dfs(c2,team[c2]);
	/*for (int i = ans.size() - 1; i >= 0; i--) {
		printf("%d", ans[i]);
		if (i)printf(" ");
	}*/
	printf("%d %d\n", cnt, maxTeam);
	return 0;
}
