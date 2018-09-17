#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#define nmax 11111

using namespace std;

int n=0;
int Parent[nmax], Child[nmax], Level[nmax]; 
vector<int> Sibbling[nmax];
vector<int> Vertex;
vector<int> Leafs;

void Add(int v, int u);
int Top_Tree();
int  Max_Degree();
void Vertex_Max(int degree);
void Leafs_Number();
int H(int u);
void Pass(int u, int number);

int main(void){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	for (int i = 0; i < n - 1; i++){
		int p = 0, c = 0;
		scanf("%d%d", &p, &c);
		Add(c, p);
	}
	int top = Top_Tree();
	int degree = Max_Degree();
	Vertex_Max(degree);
	Leafs_Number();
	int High = H(top);
	cout << High << endl;
	Pass(top, 1);
	for (int i = 1; i <= High; i++)
		cout << Level[i] << ' ';
	return 0;
}

void Add(int v, int u){
	Parent[v] = u;
	if (Child[u] != 0)
		Sibbling[u].insert(Sibbling[u].begin(), Child[u]);
	Child[u] = v;
}

int Top_Tree(){
	for (int i = 1; i <= n; i++)
		if (Parent[i] == 0)
			return i;
}

int  Max_Degree(){
	int res = 0;
	for (int i = 1; i <= n; i++)
		if (Child[i] != 0)
			if (Sibbling[i].size() + 1 > res)
				res = Sibbling[i].size() + 1;
	cout << res << endl;
	return res;	
}

void Vertex_Max(int degree){
	for (int i = 1; i <= n; i++)
		if (Child[i] != 0)
			if (Sibbling[i].size() + 1 == degree)
				Vertex.push_back(i);
	for (int i = 0; i < Vertex.size(); i++)
		printf("%d ", Vertex[i]);
	printf("\n");
}

void Leafs_Number(){
	int res = 0;
	for (int i = 1; i <= n; i++)
		if (Child[i] == 0) res++;
	cout<< res << endl;
}

int H(int u){
	if (u == 0) return 0;
	int h = 0;
	int v = Child[u];
	int i = 0;
	h = max(h,H(v));
	while(i < Sibbling[u].size()){
		h = max(h, H(Sibbling[u][i]));
		i++;
	}
	return h + 1;
}

void Pass(int u, int number){
	if (u == 0) return;
	Level[number]++;
	Pass(Child[u], number + 1);
	for (int i = 0; i < Sibbling[u].size(); i++)
		Pass(Sibbling[u][i], number + 1);
}
