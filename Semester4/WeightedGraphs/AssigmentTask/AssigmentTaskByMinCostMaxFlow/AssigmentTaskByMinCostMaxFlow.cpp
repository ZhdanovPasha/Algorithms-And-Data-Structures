#include <stdio.h>
#include <vector>
#include <deque>
#define INF 1000000000

using namespace std;
const int nmax = 500;
int a[nmax][nmax], f[nmax][nmax];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n = 0;
	scanf("%d\n", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	int m = n * 2 + 2;
	int s = m - 2;
	int t = m - 1;
	int cost = 0;
	for( ; ; ){
		vector<int> dist(m, INF);
		vector<int> p(m);
		vector<int> type(m, 2);
		deque<int> q;
		dist[s] = 0;
		p[s] = -1;
		type[s] = 1;
		q.push_back(s);
		for(;!q.empty(); ){
			int v = q.front();
			q.pop_front();
			type[v] = 0;
			if(v == s){
				for(int i = 0; i < n; i++)
					if(f[s][i] == 0){
						dist[i] = 0;
						p[i] = s;
						type[i] = 1;
						q.push_back(i);
					}	
			} else{
				if(v < n){
					for(int j = n; j < n + n; ++j)
						if(f[v][j] < 1 && dist[j] > dist[v] + a[v][j - n]){
							dist[j] = dist[v] + a[v][j - n];
							p[j] = v;
							if(type[j] == 0)
								q.push_front(j);
							else if(type[j] == 2)
								q.push_back(j);
							type[j] = 1;
						}
				} else {
					for(int j = 0; j < n; j++)
						if(f[v][j] < 0 && dist[j] > dist[v] - a[j][v - n]){
							dist[j] = dist[v] - a[j][v - n];
							p[j] = v;
							if(type[j] == 0)
								q.push_front(j);
							else if(type[j] == 2)
								q.push_back(j);
							type[j] = 1;
						}
				}
			}
		}
		int curcost = INF;
		for(int i = n; i < n + n; ++i)
			if(f[i][t] == 0 && dist[i] < curcost){
				curcost = dist[i];
				p[t] = i;
			}
		if(curcost == INF) break;
		cost += curcost;
		for(int cur = t; cur != -1; cur = p[cur]){
			int prev = p[cur];
			if(prev != -1)
				f[cur][prev] = -(f[prev][cur] = 1);
	   }
	}
	printf("%d\n", cost);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(f[i][j + n] == 1)
				printf("%d ", j + 1);
	return 0;
}
