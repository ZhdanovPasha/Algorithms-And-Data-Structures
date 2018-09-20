#include <stdio.h>
#include <vector>

using namespace std;

struct edge{
	int v;
	int w;
};

const int nmax = 1111111;
int vert[nmax], H[nmax], w[nmax], parent[nmax], pos[nmax];
vector<edge> Adj[nmax];
int t[nmax][2];
int k, m, n = 0, sum = 0;

void Make();
void swap(int& a, int& b);
void Lift(int c);
void Sift(int p);
void Change_key(int i);
void Put( int x);
int Get();
bool Empty();
void Prim();

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	int u, v, w;
	while(scanf("%d%d%d\n", &u, &v, &w)>0){
		edge a,b;
		a.v = v;
		a.w = w;
		b.v = u;
		b.w = w;
		Adj[u].push_back(a);
		Adj[v].push_back(b);
	}
	Prim();
	printf("%d\n", sum);
	for (int i = 0; i <= k; i++)
		printf("%d %d\n", t[i][0], t[i][1]);
	return 0;
}

void Make(){
	m = 0;
}

void swap(int& a, int& b){
	int tmp = a;
	a = b;
	b = tmp;
}

void Lift(int c){
	while(c > 1){
		int p = c/2;
		if (w[H[p]] <= w[H[c]])
			break;
		swap(H[c], H[p]);
		swap(pos[H[c]], pos[H[p]]);
		c = p;
	}
}

void Sift(int p){
	while (2 * p <= m){
		int c = 2 * p;
		if (c < m && w[H[c + 1]]<w[H[c]])
			c++;
		if (w[H[p]] <= w[H[c]])
			break;
		swap(H[p], H[c]);
		swap(pos[H[c]], pos[H[p]]);
		p = c;
	}
}

void Change_key(int i){
	Lift(pos[i]);
	Sift(pos[i]);
}

void Put( int x){
	m++;
	H[m] = x;
	pos[x] = m;
	Lift(m);	
}

bool Empty(){
	return m == 0;
}

int Get(){
	int tmp = H[1];
	H[1] = H[m];
	pos[H[1]] = 1;
	m--;
	Sift(1);
	pos[tmp] = -1;
	return tmp;
}

void Prim(){
	Make();
	for (int i = 1; i <= n; i++){
		w[i] = 2147483646;
		Put(i);
		parent[i] = 0;
	}
	while (!Empty()){
		int u = Get();
		for (int i = 0; i < Adj[u].size(); i++){
			int v = Adj[u][i].v;
			if (pos[v] > 0 && Adj[u][i].w < w[v]){
				w[v] = Adj[u][i].w;
				parent[v] = u;
				Change_key(v);
			}
		}
	}
	k = -1;
	for (int i = 1; i <= n; i++){
		if (parent[i] != 0){
			k++;
			sum += w[i];
			t[k][0] = i;
			t[k][1] = parent[i];
		}
	}
}
