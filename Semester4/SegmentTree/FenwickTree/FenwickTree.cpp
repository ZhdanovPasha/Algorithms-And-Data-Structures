#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

using namespace std;

const int nmax = 1111111;

int A[nmax], B[nmax];

void Change(int a, int b);
long long Sum(int a);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int a, b;
	char c;
	scanf("%c%d%d\n", &c, &a, &b);
	while (c != 'E'){
		if (c == 'C'){
			A[a] += b;
			Change(a, b);
		}
		if (c == 'S'){
			long long res = Sum(b) - Sum(a) + A[a];
			printf("%I64d\n", res);
		}
		scanf("%c%d%d\n", &c, &a, &b);
	}
	return 0;
}

void Change(int a, int b){
	while (a < nmax){
		B[a] = B[a] + b;
		a = a | (a + 1);
	}
}

long long Sum(int a){
	long long s = 0;
	while (a >= 0){
		s += B[a];
		a = (a & (a + 1)) - 1;
	}
	return s;
}
