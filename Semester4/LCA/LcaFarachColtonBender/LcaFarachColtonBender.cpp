#include <stdio.h>
#include <vector>
#include <algorithm>
#define INF 111111111

using namespace std;
const int nmax = 1111111;
vector<int> Adj[nmax];
int Parent[nmax], Ord[nmax], First[nmax], H[nmax], Status[nmax], T1[nmax], T2[nmax], ans[nmax], S[nmax];
int T[nmax][100];
int c = 0; 

void DFS(int u, int t, int h);
int LCA(int l, int r);
int Log(int c);
int pow(int j);
int Init_s();
void Init();

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n = 0;
	scanf("%d\n", &n);
	int u, v;
	for(int i = 0; i < n - 1; i++){
		scanf("%d %d", &u, &v);
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	DFS(1, 0, 1);
	Init();
	Init_s();
	int l = Log(c);
	int q, maximum, minimum;
	scanf("\n%d\n", &q);
	for(int i = 0; i < q; i++){
		scanf("%d%d", &u, &v);
		int res_vert = 0;
		int res = nmax + 11;
		int l = First[u], r = First[v];
		maximum = max(l, r);
		minimum = min(l, r);
		l = minimum;
		r = maximum;
		printf("%d ", LCA(l, r));
	}
	return 0;
}

void DFS(int u, int t, int h){
	H[u] = h;
	c++;
	Ord[c] = u;
	First[u] = c;
	t++;
	Status[u] = 1;
	T1[u] = t;
	for (int i = 0; i < Adj[u].size(); i++){
		if(Status[Adj[u][i]] == 0){
			Parent[Adj[u][i]] = u;
			DFS(Adj[u][i], t, h + 1);
			c++;
			Ord[c] = u;
		}
	}
	Status[u] = 2;
	t++;
	T2[u] = t;
}

int Log(int c){
	int l = 1;
	while ((1<<l) <= c)  ++l;
	return l;
}

int pow(int j){
	int l = 0, res = 1;
	while(l < j){
		res *= 2;
		l++;
	}
	return res;
}

void Init(){
	for(int i = 1; i < nmax; i++)
		for(int j = 0; j <= 99; j++)
			T[i][j] = INF;
	for(int i = 1; i <= c; i++)
		T[i][0] = Ord[i];
	int l = Log(c);
	for(int j = 1; j <= l; j++){
		for(int i = 1; i <= c; i++){
			if(H[T[i][j - 1]] > H[T[i + pow(j - 1)][j - 1]]){
					T[i][j] = T[i + pow(j - 1)][j - 1];
			}
			else 
				T[i][j] = T[i][j - 1];
		}
	}
}

int Init_s(){
	S[0] = 0;
	int k = 0, j = 1;
	for(int i = 1; i <= c; i++){
		if(i == j){
			k++;
			j *= 2;
		}
		S[i] = k - 1;
	}
}

int LCA(int l, int r){
	if(l == r)
		return Ord[r];
	int s = S[r - l + 1];
	if(H[T[l][s]] < H[T[r - pow(s) + 1][s]])
		return T[l][s];
	else
		return T[r - pow(s) + 1][s];
}
