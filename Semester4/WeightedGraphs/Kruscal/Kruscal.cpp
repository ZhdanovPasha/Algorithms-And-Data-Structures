#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <time.h>


using namespace std;

const int nmax = 100111;
vector<int> U, V ,W, U_answer, V_answer, W_answer;
int n, sum = 0;
int Parent[nmax], Count[nmax];

void swap(int& a, int& b );
void Quicksort(int a, int b);
void Set(int i);
int Rep(int i);
void Union(int u1, int u2);
void Kruskal();

int main(void){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	srand(time(NULL));
	scanf("%d\n", &n);
	int u, v, w;
	while (scanf("%d%d%d\n", &u, &v, &w)>0){
		U.push_back(u);
		V.push_back(v);
		W.push_back(w);
	}	
	Kruskal();
	printf("%d\n", sum);
	for (int i = 0; i < U_answer.size(); i++)
		printf("%d %d\n", U_answer[i], V_answer[i]);
	return 0;
}

void swap(int& a, int& b){
	int tmp = a;
	a = b;
	b = tmp;
}

void Quicksort(int a, int b){
	if (a >= b) return;
	int l = a - 1;
	int r = b + 1;
	int m = a + rand()%(b - a + 1);
	int x = W[m];
	do{
	    while (W[++l] < x);
		while (W[--r] > x);
		if(l >= r) break;
		swap(W[l], W[r]);
		swap(U[l], U[r]);
		swap(V[l], V[r]);
	}
	while(1);
	Quicksort(a, r);
	Quicksort(r + 1, b);
}

void Set(int i){
	Parent[i] = 0;
	Count[i] = 1;
}

int Rep(int i){
	while (Parent[i] != 0)
		i = Parent[i];
	return i;	
}

void Union(int u1, int u2){
	u1 = Rep(u1);
	u2 = Rep(u2);
	if(u1 == u2) return;
	if (Count[u1] > Count[u2]){
		Parent[u2] = u1;
		Count[u1] += Count[u2];
	} else{
		Count[u2] += Count[u1];
		Parent[u1] = u2;
	}
}

void Kruskal(){
	Quicksort(0, U.size() - 1);
	for (int i = 1; i <= n; i++)
		Set(i);	
	for (int i = 0; i < U.size(); i++){
		if (Rep(U[i]) != Rep(V[i])){
			Union(Rep(U[i]), Rep(V[i]));
			V_answer.push_back(V[i]);
			U_answer.push_back(U[i]);
			W_answer.push_back(W[i]);
			sum += W[i];			
		}
	}
	return;
}
