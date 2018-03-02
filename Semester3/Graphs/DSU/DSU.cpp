#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#define MAX 100111

using namespace std;

int res[MAX],  Parent[MAX], Count[MAX];

void Set(int i);
int Rep(int u);
void Union(int u1, int u2);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n = 0, ans = 0;
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++)
		Set(i);
	int u, v;
	while (scanf("%d%d\n", &u, &v)>0){
		Union(u,v);
	}
	for (int i = 1; i <= n; i++){
		if (Rep(i) == i)  ans++;
	}
	cout << ans;
	return 0;
}

void Set(int i){
	Parent[i] = 0;
	Count[i] = 1;
}

int Rep(int u){
	while (Parent[u] != 0)
		u = Parent[u];
	return u;
}

void Union(int u1, int u2){
	u1 = Rep(u1);
	u2 = Rep(u2);
	if (u1 == u2) return;
	if (Count[u1] > Count[u2]){
		Count[u1] += Count[u2];
		Parent[u2] = u1;
	}
	else{
		Count[u2] += Count[u1];
		Parent[u1] = u2;
	}
}
