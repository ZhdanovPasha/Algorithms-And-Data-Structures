#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <cstdlib>

#define MAX 100111

using namespace std;

typedef vector<int> vi;

vi G[MAX];
vi Gt[MAX];
int t1[MAX], t2[MAX], t1_t[MAX], t2_t[MAX], Status[MAX], Parent[MAX], Root[MAX], vert[MAX];

void Init();
void DFS(int u, int r);
void DFS_t(int u, int r);
void DFS_FOREST();
void DFS_FOREST_t();
void swap(int* a, int* b);
void QUICKSORT(int a, int b);

int n = 0, Components = 0, t;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int  k = 0, x = 0;
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &k);
		for (int j = 1; j <= k; j++){
			scanf("%d", &x);
			G[i].push_back(x);
			Gt[x].push_back(i);
		}
		scanf("\n");
	}
	for (int i = 1; i <= n; i++)
		vert[i] = i;
	DFS_FOREST_t();
	QUICKSORT(1,n);
	DFS_FOREST();
	cout << Components;
	return 0;
}

void Init(){
	t = 0;
	for (int i = 1; i <= n; i++){
		Parent[i] = 0;
		Root[i] = 0;
		Status[i] = 0;
	}
}

void DFS(int u, int r){
	t++;
	t1[u] = t;
	Status[u] = 1;
	Root[u] = r;
	for (int v = 0; v<G[u].size(); v++){
		if (Status[G[u][v]] == 0){
			Parent[G[u][v]] = u;
			DFS(G[u][v],r);
		}
	}
	t++;
	t2[u] = t;
	Status[u] = 2;
}

void DFS_t(int u, int r){
	t++;
	t1_t[u] = t;
	Status[u] = 1;
	Root[u] = r;
	for (int v = 0; v < Gt[u].size(); v++){
		if (Status[Gt[u][v]] == 0){
			Parent[Gt[u][v]] = u;
			DFS_t(Gt[u][v],r);
		}
	}
	t++;
	t2_t[u] = t;
	Status[u] = 2;
}

void DFS_FOREST(){
	Init();
	for (int u = 1; u <= n; u++){
		if (Status[vert[u]] == 0){
			Components ++;
			DFS(vert[u],vert[u]);
		}
	}
}

void DFS_FOREST_t(){
	Init();
	for (int u = 1; u <= n; u++){
		if (Status[u] == 0){
			DFS_t(u,u);
		}	
	}
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void QUICKSORT(int a, int b){
	if (a >= b) return;
	int m = a + rand() % (b - a + 1);
	int k = t2_t[m];
	int l = a - 1;
	int r = b + 1;
	do{
		while (t2_t[++l] > k);
		while (t2_t[--r] < k);
		if (l >= r) break;
		swap(&t2_t[l], &t2_t[r]);
		swap(&vert[l], &vert[r]);
	}
	while (+1);
	QUICKSORT(a,r);
	QUICKSORT(r+1, b);
}
