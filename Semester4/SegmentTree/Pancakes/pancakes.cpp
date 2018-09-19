#include <stdio.h>
#include <cstdlib>
#include <time.h>

using namespace std;
const int nmax = 1048600;
const int degtwo = 262144;
long long x[nmax], b[nmax], pos[nmax], loc_pos[nmax], Data[nmax], y[nmax];

void swap(long long& a, long long& b);
void Sort(int a, int b);
void Init(int u);
void Change(int u, int d);
long long  Sum(int u);

int main(void){
	freopen("pancakes.in", "r", stdin);
	freopen("pancakes.out", "w", stdout);
	srand(time(NULL));
	int n = 0;
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++)
		scanf("%I64d", &x[i]);
	for(int i = 1; i <= n; i++)
		pos[i] = i;
	Sort(1, n);
	Init(1);
	long long sum = 0;
	for(int i = 1; i <= n; i++){
		sum += Sum(degtwo + pos[i] - 1);
		Change(degtwo + pos[i] - 1, 1);
	}
	printf("%I64d", sum);
	return 0;
}

void swap(long long& a, long long& b){
	long long tmp = a;
	a = b;
	b = tmp;
}

void Sort(int a, int b){
	if(a >= b) return;
	int m =(a + b)/2;
	Sort(a, m);
	Sort(m + 1, b);
	int i = a;
	int j = m + 1;
	for (int r = a; r <= b; r++){
	    if ((j > b) || ((i <= m) && (x[i] <= x[j]))) {
		  	y[r] = x[i];
		  	loc_pos[r] = pos[i];
	    	i++;
		} else {	
			y[r] = x[j];
			loc_pos[r] = pos[j];
			j++;
		} 		
	}
	for (int k = a; k <= b; k++){
		x[k] = y[k];
		pos[k] = loc_pos[k];
	}
}

void Init(int u){
	Data[u] = 0;
	if(u >= degtwo) return;
	Init(u * 2);
	Init(u * 2 + 1);
}

void Change(int u, int d){
	while(u != 0){
		Data[u] += d;
		u /= 2;
	}
}

long long Sum(int u){
	long long s = Data[u];
	while(u != 0){
		int p = u/2;
		if(u == (p * 2 + 1))
			s +=Data[p * 2];
		u = p;		
	}
	return s;	
}
