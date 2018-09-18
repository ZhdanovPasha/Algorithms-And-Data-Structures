#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
const int nmax = 1111111;
vector<int> Adj[nmax];
int Parent[nmax], Ord[nmax], First[nmax], H[nmax], Status[nmax], T1[nmax], T2[nmax], ans[nmax];
int c = 0; 

void DFS(int u, int t, int h);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n = 0;
	scanf("%d\n", &n);
	int u, v;
	for (int i = 0; i < n - 1; i++){
		scanf("%d %d", &u, &v);
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	DFS(1, 0, 1);
	int root = 0, minimum = nmax + 11, maximum, minimum_vert = 0;
	while (root * root <= c) root++;
	for (int i = 1; i <= c; i++){
		if (H[Ord[i]] < minimum){
			minimum = H[Ord[i]];
			minimum_vert = Ord[i];
		}
		if(i%root == 0 || i == c){
			int l = i/root;
			if(i%root > 0) l++;
			ans[l] = minimum_vert;
			minimum_vert = 0;
			minimum = nmax + 11;
		}
	}
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
		int l_part = (l/root), r_part = (r/root);
		if (l%root > 0) l_part++;
		if(!r%root) r_part--;
		for (int i = l; i <= l_part * root && i <= r; i++)
			if(res > H[Ord[i]]){
				res = H[Ord[i]];
				res_vert = Ord[i];
			}
		for (int i = l_part + 1; i <= r_part && i * root <= r; i++){
			if(i * root > r) break;
			if(res > H[ans[i]]){
				res = H[ans[i]];
				res_vert = ans[i];
			}
		}
		for (int i = max((r_part) * root, l_part * root); i <= r; i++)
			if(res > H[Ord[i]]){
				res = H[Ord[i]];
				res_vert = Ord[i];
			}
		printf("%d ", res_vert);
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
