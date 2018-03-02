#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#define MAX 1111

using namespace std;

int G[MAX][MAX];
int Q[MAX], Status[MAX], Distance[MAX], Root[MAX], Parent[MAX];
int Top, Tail;
int Components = 0;
int P[MAX];
int n = 0, res = 0;

void MAKE();
bool EMPTY();
void PUT(int x);
int GET();
void Init (int G[MAX][MAX]);
void BFS (int G[MAX][MAX], int s);
void BFS_FOREST(int G[MAX][MAX]);
void Path(int s, int t);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n" , &n);
	for ( int i = 1; i <= n; i++){
		scanf("%d", &G[i][0]);
		for (int j = 1; j <= G[i][0]; j++)
			scanf("%d", &G[i][j]);
			
		scanf("\n");	
	}
	BFS_FOREST (G);
	for (int i = 1; i < n; i++){
		res = 0;
		for (int j = 0; j <= n; j++)
			P[j] = 0;
		Path(n,i);
		if (res == 0) {
			cout << '0' << endl;
		}
		else {
			cout << res << ' ';
			for (int j = 1; j <= res; j++){
				cout << P[j] << ' ';
			}
			cout << endl;
		}
	}
	cout << Components;
	return 0;
}

void MAKE(){
	Top = 1;
	Tail = 0;
}

bool EMPTY(){
	if (Top > Tail) return true;
	else return false;
}

void PUT(int x){
	Tail++;
	Q[(Tail + 1) % n] = x;
}

int GET(){
	Top++;
	return Q[Top % n];
}

void Init (int G[MAX][MAX]){
	for (int i = 1; i <= n; i++){
		Status[i] = 0;
		Parent[i] = 0;
		Root[i] = 0;
		Distance[i] = INT_MAX;
	}
}

void BFS (int G[MAX][MAX], int s){
	Distance[s] = 0;
	Status[s] = 1;
	Root[s] = s;
	MAKE();
	PUT(s);
	while (!EMPTY()){
		int i = GET();
		for (int j = 1; j <= G[i][0]; j++){
			if (Status[G[i][j]] == 0){
				Status[G[i][j]] = 1;
				Parent[G[i][j]] = i;
				Distance[G[i][j]] = Distance[i] + 1;
				Root[G[i][j]] = s;
				PUT(G[i][j]);
			}
		}
	}
}

void BFS_FOREST (int G[MAX][MAX]){
	Init(G);
	for (int i = n; i >= 1; i--){
		if (Status[i] == 0){
			Components++;
			BFS(G, i);
		}
	}
}

void Path(int s, int t){
	int k = Distance[t];
	if (Root[t] != Root[s]){
		res = 0;
		return;
	}
	P[k] = t;
	res = k;
	while (k > 0) {
		k--;
		P[k] = Parent[P[k + 1]];
	}
}
