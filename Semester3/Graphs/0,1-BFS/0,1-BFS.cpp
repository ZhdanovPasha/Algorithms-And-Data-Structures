#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <deque>
#define MAX 100011

using namespace std;

struct MyVector{
	vector<int> Vec;
	vector<int> Dist;
};

typedef struct MyVector MV;

void BFS(MV Adj[MAX], int s);

MV Adj[MAX];
int Distance[MAX], Parent[MAX];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n,m,u,d,v;
	scanf("%d%d\n", &n, &m);
	for (int i = 1; i <= m; i++){
		scanf("%d%d%d", &u, &v, &d);
		Adj[u].Vec.push_back(v);
		Adj[u].Dist.push_back(d);
		Adj[v].Vec.push_back(u);
		Adj[v].Dist.push_back(d);	
	}
	for (int i = 1; i <= n; i++)
		Distance[i] = INT_MAX;
	BFS(Adj, 1);
	if (Distance[n] == INT_MAX) cout << "-1";
	else cout << Distance[n];
	return 0;
}

void BFS(MV Adj[MAX], int s){
	for (int i = 0; i < Adj[s].Vec.size(); i++)
		Parent[Adj[s].Vec[i]] = 0;
	Distance[s] = 0;
	deque<int> DECK;
	DECK.push_back(s);
	while (!DECK.empty()) {
		int u = DECK.front();
		DECK.pop_front();
		for (int v = 0; v < Adj[u].Vec.size(); v++){
			if (Distance[Adj[u].Vec[v]] > Distance[u] + Adj[u].Dist[v]){
				Distance[Adj[u].Vec[v]] = Distance[u] + Adj[u].Dist[v];
				Parent[Adj[u].Vec[v]] = u;
				if (Adj[u].Dist[v] == 0){
					DECK.push_front(Adj[u].Vec[v]);	
				} else {
					DECK.push_back(Adj[u].Vec[v]);  	
				} 
			}
		}
	}
}
