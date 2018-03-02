#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <vector>
#define MAX 1111

using namespace std;

void Init();
void DFS(int u, int r, int t);
void DFS_FOREST();

vector<int> Adj[MAX];
int Status[MAX], Parent[MAX], Root[MAX], T1[MAX], T2[MAX];
int t, n = 0, Components = 0;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
    int u,v;
	while (scanf("%d%d", &u, &v)>0){
    	Adj[u].push_back(v);
    	Adj[v].push_back(u);
	}
	DFS_FOREST();
	cout << Components;
	return 0;
}

void Init(){
	t = 0;
	for (int i = 1; i <= n;i++){
		Parent[i] = 0;
		Root[i] = 0;
		Status[i] = 0;
	}
}

void DFS(int u, int r, int t){
	t++;
	Status[u] = 1;
	T1[u] = t;
	Root[u] = r;
	for (int i = 0; i < Adj[u].size(); i++)
		if (Status[Adj[u][i]] == 0){
			Parent[Adj[u][i]] = u;
			DFS(Adj[u][i], r, t);
		}
	t++;
	T2[u] = t;
	Status[u] = 2;
}

void DFS_FOREST(){
	Init();
	for (int i = 1; i <= n; i++){
		if (Status[i] == 0) {
			Components++;
			DFS(i, i, t);
		}
	}
} 
