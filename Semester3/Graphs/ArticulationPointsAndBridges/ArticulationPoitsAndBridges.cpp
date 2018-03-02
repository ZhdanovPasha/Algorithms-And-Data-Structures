#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <cstdlib>
#define MAX 1111

using namespace std;

vector<int> Adj[MAX];
int a[MAX*100][3];
int G[MAX][MAX];
int Status[MAX], Root[MAX], Parent[MAX], t1[MAX], ap[MAX], low[MAX], Res[MAX];
int t = 0, n = 0, w = 0; 

void DFSap(int u, int r);
void ARTICULATION_POINTS();
void BRIDGES();
void Init();
void DFS(int u, int r);
void DFS_FOREST();
void quicksort( int a, int b);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int u,v;
	scanf("%d\n", &n);
	while(scanf("%d%d", &u, &v)>0){
		Adj[u].push_back(v);
		Adj[v].push_back(u);
		G[u][v] = 1;
		G[v][u] = 1;
	}
	ARTICULATION_POINTS();
	BRIDGES();
	quicksort(1, w);
    for (int i = 1; i <=n ; i++)
		if (ap[i] > 0)
			printf("%d ", i);
	for (int i = 1; i <= w; i++){
	   if (G[a[i][1]][a[i][2]] != 0){
	    G[a[i][1]][a[i][2]] = 0;
		G[a[i][2]][a[i][1]] = 0;
		cout << endl << a[i][1] << ' ' << a[i][2];
	   }
	}
	cout << endl;
	Res[1] = 1;
	DFS_FOREST();
	for (int i = 1; i <= n; i++)
		if (Res[i] == 1) cout << i << ' ';
	return 0;
}

void DFSap (int u, int r){
	t++;
	t1[u] = t;
	Status[u] = 1;
	Root[u] = r;
	low[u] = t;		
	int pow = 0;	
	int lm = 0;    
	for (int i = 0; i < Adj[u].size(); i++){
		int v = Adj[u][i];
		if (Status[v] == 0){
			pow ++;
			Parent[v] = u;
			DFSap(v,r);
			low[u] = min(low[u], low[v]);
			lm = max(lm, low[v]);
		} else { // status[i]==1
   		    if (v!=Parent[u]){
   		    	low[u]=min(low[u], t1[v]);
			} 	
   		}
   	}
   	Status[u] = 2;
   	if (((Root[u] == u) && (pow > 1)) || ((Root[u] != u) &&(lm >= t1[u]))){
   		ap[u] = 1;
	}	
}

void ARTICULATION_POINTS(){
	for (int i = 1; i <= n; i++){
		Status[i] = 0;
		Parent[i] = 0;
		ap[i] = 0;
	}
	t = 0;
	for (int i = 1; i <= n; i++)
		if (Status[i] == 0)
			DFSap(i, i);
}

void BRIDGES(){
	for (int i = 1; i <= n; i++){
		if (Adj[i].size() == 1) {
				w++;
				a[w][1] = i;
				a[w][2] = Adj[i][0];
		}
		else{
			for (int j = 0; j < Adj[i].size(); j++){
				int u = i;
				int v = Adj[i][j];
				if (((ap[u] == 1) && (low[v] > t1[u])) || ((ap[v] == 1) && (low[u] > t1[v]))){
					w++;
					a[w][1] = u;
					a[w][2] = v;
				}
			}	
		}	
	}
}

void Init(){
	t = 0;
	for (int i = 1; i <= n; i++){
		Status[i] = 0;
		Parent[i] = 0;
		Root[i] = 0;
	}
}

void DFS(int u, int r){
	t++;
	Root[u] = r;
	Status[u] = 1;
	for (int i = 0; i < Adj[u].size(); i++){
		int v = Adj[u][i];
		if ((Status[v] == 0) && (G[u][v] == 1)){
			Res[v] = 1;
			Parent[v] = u;
			DFS(v,r);
		}
	}
	t++;
	Status[u] = 2;
}

void DFS_FOREST(){
	Init();
	DFS(1, 1);
}	

void swap(int *a, int *b){
	int tmp= *a;
	*a = *b;
	*b = tmp;	
}	
	
void quicksort(int b, int c){
    if (b >= c) return;
	int m = b + rand() % (c - b + 1);
	int k = a[m][2];
	int l = b - 1;
	int r = c + 1;
	do{
		while (a[++l][2] < k);
		while (a[--r][2] > k);
		if (l >= r) break;
		if (a[l][1] >= a[r][1]){
			swap(&a[l][2], &a[r][2]);
			swap(&a[l][1], &a[r][1]);
		}
	}
    while (+1);
	quicksort(b,r);
	quicksort(r+1, c);
}
