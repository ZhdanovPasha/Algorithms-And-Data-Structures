#include <stdio.h>
#include <vector>

using namespace std;

struct edge{
	int v;
	int w;
};

const int nmax = 111;
vector<edge> Adj[nmax];
int Distance[nmax], Parent[nmax], Path[nmax], H[nmax], pos[nmax];
int n = 0, m;
int ans[1000000];

void swap(int& a, int& b);
void Make();
bool Empty();
void Lift(int c);
void Sift(int p);
void Put(int x);
int Get();
void Change_key(int i);
void Dijkstra(int s);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	int u, w, v;
	while (scanf("%d%d%d" , &u, &v, &w) > 0){
		edge a, b;
		a.v = v;
		a.w = w;
		b.v = u;
		b.w = w;
		Adj[u].push_back(a);
		Adj[v].push_back(b);		
	}
	Dijkstra(n);
	int k = -1;
	for (int i = 1; i < n;i++){
		if	(!Path[i]){
			printf("no path\n");
		} else {
			k++;
			int j = Parent[i];
			ans[k] = i;
			while(j != n){
				k++;
				ans[k] = j;
				j = Parent[j];
				if(j == 0) break;
			}
			if(!j) {
				printf("no path\n");
				k = -1;
			} else{
				k++;
				ans[k] = n;
				for (int i = k; i >= 0; i--)
					printf("%d " ,ans[i]);
				for(int i = k; i >= 0; i--)
					ans[i] = 0;
				k = -1;
				printf("\n");
			}
		}
	}
	return 0;
}

void swap(int& a, int& b){
	int tmp = a;
	a = b;
	b = tmp;
}

void Make(){
	m = 0;
}

bool Empty(){
	return m == 0;
}

void Lift(int c){
	while(c > 1){
		int p = c/2;
		if (Distance[H[p]] <= Distance[H[c]])
			break;
		swap(H[p], H[c]);
		swap(pos[H[p]], pos[H[c]]);
		c = p;
	}
}

void Sift(int p){
	while(2 * p <= m){
		int c = p * 2;
		if(c < m && Distance[H[c + 1]] < Distance[H[c]])
			c++;	
		if(Distance[H[p]] <= Distance[H[c]])
			break;
		swap(H[p], H[c]);
		swap(pos[H[p]], pos[H[c]]);
		p = c;
	}
}

void Put(int x){
	m++;
	H[m] = x;
	pos[x] = m;
	Lift(m);
}

int Get(){
	int tmp = H[1];
	H[1] = H[m];
	pos[H[1]] = 1;
	m--;
	pos[tmp] = -1;
	Sift(1);
	return tmp;
}

void Change_key(int i){
	Sift(pos[i]);
	Lift(pos[i]);
}

void Dijkstra(int s){
	for (int i = 1; i <= n; i++){
		Distance[i] = 2147483645;
		Parent[i] = 0;
	}
	Distance[s] = 0;
	Make();
	for (int i = 1; i <= n; i++)
		Put(i);
	while (!Empty()){
		int u = Get();
		for (int i = 0; i < Adj[u].size(); i++){
			int v = Adj[u][i].v;
			if (pos[v] > 0 && Distance[v] > Distance[u] + Adj[u][i].w){
				Path[v] = 1;
				Distance[v] = Distance[u] + Adj[u][i].w;
				Parent[v] = u;
				Change_key(v);
			}
		}
	}
}
