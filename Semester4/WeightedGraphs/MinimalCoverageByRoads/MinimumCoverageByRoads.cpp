#include <stdio.h>
#include <math.h>
#include <algorithm>
#define INF 111111111

using namespace std;

const int nmax = 5000;

int c[nmax][nmax], f[nmax][nmax], P[nmax], Q[nmax*nmax], Distance[nmax], Status[nmax], Parent[nmax];
int top, tail, n, k;
int S,T;

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
	int nn = n;
	for(int i = 1; i <= n * 3; i++)
		for(int j = 1; j <= n * 3; j++)
			c[i][j] = 0;
	int u,v;
	while(scanf("%d%d", &u, &v)>0)
		c[u + 1][v + 1]=1;
	S = 1, T = n * 2 + 2;
	for(int i = 2; i <= n + 1; i++){
		for(int j = 2; j <= n + 1; j++){
			if(c[i][j] == 1){
				c[i][j + n] = 1;
				c[i][j] = 0;
			}
		}
	}
	n *= 2;
	n += 2;
	for(int i = 2; i <= (n - 2)/2 + 1; i++)
		c[S][i] = 1;
	for(int i= (n - 2)/2 + 2; i < n; i++)
		c[i][T] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			f[i][j] = 0;
	//Admonds-karp
	int res = 0;
	Init();
	while(BFS(S)){
		Path(S, T);
		int b = P[1], e = P[2];
		int cfp = INF;//проегаем по пути и находим минимальный вес ребра
		k = Distance[T];
		for(int i = 0;i < k; i++){
			b = P[i];
			e = P[i + 1];
			cfp=min(cfp, c[b][e] - f[b][e]);
		}
		res += cfp;
		b = 0, e = 0;
		for(int i = 0;i < k;i++){
			b = P[i];
			e = P[i + 1];
			f[b][e] = f[b][e] + cfp;
			f[e][b]=(-1) * f[b][e];			
		}
		Init();
	}
	printf("%d\n", nn - res);
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
	for(int i = 0; i <= n * 2; i++){
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
				if(i == T) return true;
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
