#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

const int NMAX = 1E4 + 10;

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int a[NMAX];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt","w", stdout);
	int x = 0,n = 0;
	while (scanf("%d", &x)>0){
		n++;
		a[n] = x;
	}
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			if (a[i] > a[j]) swap(&a[i], &a[j]);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
    return 0;
}
