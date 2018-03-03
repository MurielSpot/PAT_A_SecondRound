/*
ac:1次,时长:31分钟,难度:2.

注意事项:
1. 出了不少细节错误,比如把赋值等号=写成比较的等号==,最短路径找出新的最近结点时没有标记已访问vis[]=true,结果让输出最短路径条数和最大成员数,我输出成了最短路径经过的各个结点.
这些浪费了差不多十分钟时间调试.
2. 最短路径中容易出错的地方:找最小dist时,要在未访问的结点中找,更新dist时,也是更新未访问结点的;找到dist最小的结点之后,应该标记已访问.
3. vector不能用memset全部赋值为-1,我记得之前试过,赋值为全0不会异常退出,但是赋值为全-1,会异常退出.
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
