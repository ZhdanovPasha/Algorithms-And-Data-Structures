#include <stdio.h>
#include <vector>
#include <algorithm>
#include <list>
#define inf 1111111111

using namespace std;

const int nmax = 10000;
int c[nmax][nmax], e[nmax], f[nmax][nmax], h[nmax], Current[nmax], Number[nmax];
int n, res;

vector<int> Adj[nmax];

void Lift(int u);
void Init();
int LIFT_TO_FRONT();
void Push(int u, int v);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	int u, v, w;
	while(scanf("%d%d%d",&u, &v, &w)>0){
		u--;
		v--;
		c[u][v] = w;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	res = LIFT_TO_FRONT();
	printf("%d\n", res);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%d ", f[i][j]);
		printf("\n");
	}
	return 0;
}

void Init(){
    for(int i = 0; i < n; i++){
		h[i] = 0;
		e[i] = 0;
	}
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			f[i][j] = 0;
			f[j][i] = 0;
	}
	h[0] = n;
	for(int i = 1; i < n; i++){
		f[0][i] = c[0][i];
		f[i][0] = -c[0][i];
		e[i] = f[0][i];
	}
}

void Lift(int u){
	int height = inf;
	for(int i = 0; i < n; i++)
		if(c[u][i] - f[u][i] > 0)
			height = min(height, h[i]);
	if(height == inf) return;
	h[u] = height + 1;
	return;
}

void Push(int u, int v){
	int df = min(e[u], c[u][v] - f[u][v]);
	f[u][v] += df;
	f[v][u] = (-1) * (f[u][v]);
	e[u] -= df;
	e[v] += df;
}

int LIFT_TO_FRONT(){
	int u, v;
	Init();
	for( ; ; ){
		int i;
		for(i = 1; i < n - 1; i++)
			if(e[i] > 0)
				break;
		if(i == (n - 1))
			break;
		int j;
		for(j = 0; j < n; j++)
			if(c[i][j] - f[i][j] > 0 && h[i] == (h[j] + 1))
				break;
		if(j < n)
			Push(i, j);
		else
			Lift(i);
	}
	int flow = 0;
	for(int i = 0; i < n; i++)
		flow += f[0][i];
	return max(flow, 0);
}
