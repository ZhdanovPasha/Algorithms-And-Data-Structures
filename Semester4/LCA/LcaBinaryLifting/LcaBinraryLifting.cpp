#include <stdio.h>
#include <vector>
#include <algorithm>
#define INF 111111111

using namespace std;
const int nmax = 1111111;
vector<int> Adj[nmax];
int  Parent[nmax], H[nmax], Status[nmax], T1[nmax], T2[nmax], ans[nmax];
int P[nmax][100];
int c = 0, n, t = 0; 

void DFS(int u, int h, int parent=1);
void Init();
int LOG(int m);
bool Par(int u , int v);
int LCA(int u, int v);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	int u,v;
	for(int i = 0; i < n - 1; i++){
		scanf("%d %d", &u, &v);
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	DFS(1, 1);
	int q, maximum = 0,minimum = INF ;
	int l = LOG(n);
	scanf("\n%d\n", &q);
	for(int i = 0; i < q; i++){
		scanf("%d%d", &u, &v);
		int l = 0, r = INF;
		r = max(u,v);
		l = min(u,v);
		printf("%d ", LCA(l, r));
	}
	return 0;
}

void DFS(int u, int h, int parent){
	H[u] = h;
	t++;
	Status[u] = 1;
	T1[u] = t;
	P[u][0] = parent;
	for(int i = 1; i <= 99; i++){
		P[u][i] = P[P[u][i - 1]][i - 1];
	}
	for (int i = 0; i < Adj[u].size(); i++){
		if(Status[Adj[u][i]] == 0){
			Parent[Adj[u][i]] = u;
			DFS(Adj[u][i], h + 1, u);
		}
	}
	Status[u] = 2;
	t++;
	T2[u] = t;
}

int LOG(int m){
	int l = 1;
	while ((1<<l) <= m)  ++l;
	return l;
}

bool Par(int u , int v){
	return(T1[u] < T1[v] && T2[v] < T2[u]);
}

int LCA(int u, int v){
	if(v == u)
		return u;
	if(Par(u, v))
		return u;
	if(Par(v, u))
		return v;
	int l = LOG(n);
	while(l >= 0){
		if(P[u][l] > 0 && !Par(P[u][l], v))
			u = P[u][l];
		l--;
	}
	return P[u][0];
}
