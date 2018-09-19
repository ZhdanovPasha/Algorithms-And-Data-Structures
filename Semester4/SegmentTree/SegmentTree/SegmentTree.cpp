#include <iostream>
#include <stdio.h>

using namespace std;

const int nmax = 524300;
const int degtwo = 262144;
int  leaf[nmax], left[nmax], right[nmax], count[nmax], Parent[nmax];

void Init(int u);
void Change(int u, int d);
long long Sum(int u);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int a, b;
	char c;
	Init(1);
	scanf("%c%d%d\n", &c, &a, &b);
	while (c != 'E'){
		if (c == 'C'){
			Change(degtwo + a - 1, b);
		}
		if (c == 'S'){
			long long res = 0;
			res = Sum(degtwo + b - 1) - Sum(degtwo + a - 1) + count[degtwo + a - 1];
			cout << res << endl;
		}
		int deg = 1;
		scanf("%c%d%d\n", &c, &a, &b);
	}
	return 0;
}

void Init(int u){
	count[u] = 0;
	if (u >= degtwo) return;
	Init(u * 2);
	Init(u * 2 + 1);
}

void Change(int u, int d){
	while (u != 0){
		count[u] += d;
		u = u/2;
	}
}

long long Sum(int u){
	long long s = count[u];
	while (u != 0){
		int p = u/2;
		if (u == (p * 2 + 1))
			s += count[p * 2];
		u = p;
	}
	return s;
}
