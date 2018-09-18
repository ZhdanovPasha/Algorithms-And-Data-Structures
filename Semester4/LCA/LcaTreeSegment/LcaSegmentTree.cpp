#include <stdio.h>
#include <vector>
#include <algorithm>
#define INF 1111111111

using namespace std;
const int nmax = 11111111;
const int degtwo = 262144;
vector<int> Adj[nmax];
int Parent[nmax], Ord[nmax], First[nmax], H[nmax], Status[nmax], T1[nmax], T2[nmax], ans[nmax], data[nmax], vert[nmax];
int c = 0, n; 

void DFS(int u, int t, int h);
int Min(int l, int r);
void Change(int u,int d);
void Init(int u);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	int u, v;
	for(int i = 0; i < n - 1; i++){
		scanf("%d %d", &u, &v);
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	DFS(1, 0, 1);
	int maximum = 0, minimum = INF;
	Init(1);
	for(int i = 1; i <= c; i++){
		Change(i + degtwo - 1, H[Ord[i]]);
	}
	int deg = 1;
	int q;
	scanf("\n%d\n", &q);
	for(int i = 0; i < q; i++){
		scanf("%d%d", &u, &v);
		int res_vert = 0;
		int res = nmax + 11;
		int l = First[u], r = First[v];
		maximum = max(l,r);
		minimum = min(l,r);
		l = minimum;
		r = maximum;
		printf("%d ", Min(l + degtwo - 1, r + degtwo - 1));	
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

void Init(int u){
	if(u >= degtwo && u <= degtwo + c - 1){
		data[u] = H[Ord[u - degtwo + 1]];
		vert[u] = Ord[u - degtwo + 1];
	}
	else{
		data[u] = INF;	
		vert[u] = u;
	}
	if(u > 2 * degtwo) return;
	Init(u * 2);
	Init(u * 2 + 1);
}

void Change(int u,int d){
	int v = u - degtwo + 1;
	while(u != 0){
		if(data[u] > d){
			vert[u] = Ord[v];
			data[u] = d;
		}
		u = u/2;
	}
}

int Min(int l, int r){
	int ans = INF, ans_vert = 0;
	int m = c/2;
	while(l <= r){
		if(l & 1)
			if(ans > data[l]){
				ans = data[l];
				ans_vert = vert[l];
			}		
		if(!(r & 1))
			if(ans > data[r]){
				ans = data[r];
				ans_vert = vert[r];
			}
		l = (l + 1)/2;
		r = (r - 1)/2;
	}
	return ans_vert;
}
