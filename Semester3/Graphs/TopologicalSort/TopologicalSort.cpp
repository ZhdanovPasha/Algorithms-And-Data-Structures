#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <vector>
#define MAX 100011

using namespace std;

void FOREST();
int TOPSORT(int i);

vector <int> Adj[MAX];
int n,m, flag=0;
int Status[MAX];
vector<int> Otvet;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d\n", &n, &m);
	for (int i = 1; i <= m; i++){
		int u = 0, v = 0;
		scanf("%d%d", &u, &v);
		Adj[u].push_back(v);
	}
	for (int i = 1; i <= n; i++)
		Status[i] = 0;
	FOREST();
	if (flag == -1) cout << "-1";
	else for (int i = Otvet.size() - 1; i >= 0; i--)
		cout << Otvet[i] << ' ';
	return 0;
}

int TOPSORT(int x){
	Status[x] = 1;
	for (int i = 0; i < Adj[x].size(); i++ ){
		if (Status[Adj[x][i]] == 0)
			TOPSORT(Adj[x][i]);
		else if (Status[Adj[x][i]] == 1)
			return -1;
	}
	Status[x] = 2;
	Otvet.push_back(x);
}
	
void FOREST(){
	for (int i = 1; i <= n; i++){
		if (Status[i] == 0){
		  int h = TOPSORT(i);
		  if (h == -1) flag = -1;
		}
	}
}
	
	

