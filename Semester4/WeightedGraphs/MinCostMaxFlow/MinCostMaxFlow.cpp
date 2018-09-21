#include <stdio.h>
#include <math.h>
#include <algorithm>
#define INF 111111111

using namespace std;

const int nmax = 555;

int c[nmax][nmax], f[nmax][nmax], p[nmax][nmax], Distance[nmax], Parent[nmax], H[nmax], pos[nmax], path[nmax], potential[nmax];
int  n, S, T, m, number;

void Init();
void swap(int& a, int& b);
void Make();
bool Empty();
void Lift(int c);
void Sift(int p);
void Put(int x);
int Get();
void Change_key(int i);
bool Dijkstra();
void Way();

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%d\n", &n, &S, &T);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			c[i][j] = 0;
	for(int i = 0; i <= n; i++)
		potential[i] = 0;
	int u, v, cc, w;
	while(scanf("%d%d%d%d", &u, &v, &cc, &w) > 0){
		c[u][v] = cc;
		p[u][v] = w;
		p[v][u] = -w;
	}
	int res_flow = 0, cost_flow = 0;
	while (Dijkstra()){
		Way();
		int b,e;
		int cfp = INF, cost = 0;
		int k = number;
		for(int i = 0; i < k; i++){
			b = path[i];
			e = path[i + 1];
			cfp = min(cfp, c[b][e] - f[b][e]);
			cost += p[b][e];
		}
		res_flow += cfp;
		cost_flow += cost * cfp;
		b = 0, e = 0;
		for(int i = 0; i < k; i++){
			b = path[i];
			e = path[i + 1];
			f[b][e] += cfp;
			f[e][b] = -f[b][e];
		}
		Init();	
	}
	printf("%d\n%d", res_flow, cost_flow);
	return 0;
}


void Init(){
	for(int i = 0; i <= nmax; i++){
		Distance[i] = 0;
		Parent[i] = 0;
		path[i] = 0;
		pos[i] = 0;
		H[i] = 0;
	}
	number = 0;
}

void swap(int& a, int& b){
	int tmp = a;
	a = b;
	b = tmp;
}

void Make(){
	m = 0;
}

bool Empty(){
	return (m == 0);
}

void Lift(int c){
	while(c > 1){
		int p = c / 2;
		if(Distance[H[p]] <= Distance[H[c]])
			break;
		swap(H[p], H[c]);
		swap(pos[H[p]], pos[H[c]]);
		c = p;
	}
}

void Sift(int p){
	while(2 * p <= m){
		int c = p * 2;
		if(c < m && Distance[H[c + 1]] < Distance[H[c]])
			c++;
		if(Distance[H[p]] <= Distance[H[c]])
			break;
		swap(H[p], H[c]);
		swap(pos[H[p]], pos[H[c]]);
		p = c;
	}
}

void Put(int x){
	m++;
	H[m] = x;
	pos[x] = m;
	Lift(m);	
}

int Get(){
	int tmp = H[1];
	H[1] = H[m];
	pos[H[1]] = 1;
	m--;
	pos[tmp]= -1;
	Sift(1);
	return tmp;
}

void Change_key(int i){
	Sift(pos[i]);
	Lift(pos[i]);
}

bool Dijkstra(){
	int flag = 0;
	for(int i = 1; i <= n; i++){
		Distance[i] = INF;
		Parent[i] = 0;
	}
	Distance[S] = 0;
	Make();
	Put(S);
	for(int i = 1; i <= n; i++)
		if(i != S)
			Put(i);
	while(!Empty()){
		int u = Get();
		for(int v = 1; v <= n; v++)
			if(pos[v] > 0 && Distance[v] > Distance[u] + p[u][v] - (potential[v] - potential[u]) && c[u][v]-f[u][v]>0){
				Distance[v] = Distance[u] + p[u][v] - (potential[v] - potential[u]);
				Parent[v] = u;
				Change_key(v);
				if(v == T) flag = 1;
			}
	}
	if(flag == 0) return false;
	Way();
	int b, e;
	int sum = 0;
	int k = number;
	for(int i = 0; i < k; i++){
		b = path[i];
		e = path[i + 1];
		sum += p[b][e];
	}
	for(int i = 1; i <= n; i++)
		potential[i] += Distance[i];
	return true;
}

void Way(){
	int k = -1,p = T;
	while(p != 0){
		k++;
		p = Parent[p];
	}
	number = k;
	path[k] = T;
	while(k > 0){
		k--;
		path[k] = Parent[path[k + 1]];
	}
}
