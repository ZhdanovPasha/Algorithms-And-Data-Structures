#include <stdio.h>
#include <math.h>
#include <algorithm>
#define INF 111111111

using namespace std;

const int nmax = 555;

int c[nmax][nmax], f[nmax][nmax], P[nmax], Q[nmax * nmax], Distance[nmax], Status[nmax], Parent[nmax];
int top, tail, n, k;

void Make();
bool Empty();
void Put(int x);
int Get();
bool BFS(int s);
void Path(int s, int t);
void Init();

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			c[i][j] = 0;
	int u, v, w;
	while(scanf("%d%d%d", &u, &v, &w) > 0)
		c[u][v] = w;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			f[i][j] = 0;
	int res = 0;
	Init();
	while(BFS(1)){
		Path(1, n);
		int b = P[1], e = P[2];
		int cfp = INF;
		k = Distance[n];
		for(int i = 0; i < k; i++){
			b = P[i];
			e = P[i + 1];
			cfp = min(cfp, c[b][e] - f[b][e]);
		}
		res += cfp;
		b = 0, e = 0;
		for(int i = 0; i < k; i++){
			b = P[i];
			e = P[i + 1];
			f[b][e] = f[b][e] + cfp;
			f[e][b] = (-1) * f[b][e];			
		}
		Init();
	}
	printf("%d\n", res);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
			printf("%d ", f[i][j]);
		printf("\n");
	}
	return 0;
}

void Make(){
	top = 1;
	tail = 0;
}

bool Empty(){
	return top > tail;
} 

void Put(int x){
	tail++;
	Q[tail] = x;
}

int Get(){
	top++;
	return Q[top - 1];
}

void Init(){
	for(int i = 0; i <= n; i++){
		Distance[i] = 0;
		Status[i] = 0;
		Parent[i] = 0;
		P[i] = 0;	
		Q[i] = 0;
	}	
}


bool BFS(int s){
	Distance[s] = 0;
	Status[s] = 1;
	Make();
	Put(s);
	while(!Empty()){
		int u = Get();
		for(int i = 1; i <= n ;i++){
			if(Status[i] == 0  && c[u][i] > f[u][i]){
				Status[i] = 1;
				Distance[i] = Distance[u] + 1;
				Parent[i] = u;
				Put(i);
				if(i == n) return true;
			}
		}
	}
	return false;
}

void Path(int s, int t){
	k = Distance[t];
	P[k] = t;
	while(k > 0){
		k--;
		P[k] = Parent[P[k + 1]];
	}
}
