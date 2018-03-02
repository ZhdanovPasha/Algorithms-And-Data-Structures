#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <vector>
#define MAX 1001100

using namespace std;

vector<int> Adj[MAX];
vector<int> Otvet;
int pov[MAX],res[MAX];
int n;

void EULER(int i); 

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++){
		res[i] = 0;
		pov[i] = 0;
	}
	for (int i = 1; i <= n; i++){
		int m = 0;
		scanf("%d", &m);
		for (int j = 1; j <= m; j++){
			int x = 0;
			scanf("%d", &x);
			Adj[i].push_back(x);
			pov[x]--;
		}
		pov[i] += m;
		scanf("\n");
	}
	int flag = 0;
	EULER(1);
	for (int i = 1; i <= n; i++){
		if  ((pov[i] != 0) || (res[i] == 0)){
			flag = -1;
			break;
		}
	}
	if (flag == -1) cout << "-1";
	else {
		for (int i = Otvet.size() - 1; i >= 0; i--)
			cout << Otvet[i] << ' ';
	}
	return 0;
}

void EULER(int u){
	res[u]++;
	for (int i = 0; i < Adj[u].size(); i++){
		int v = Adj[u][i];
		Adj[u].erase(Adj[u].begin());
		EULER(v);
		i--;
	}
	Otvet.push_back(u);
}
