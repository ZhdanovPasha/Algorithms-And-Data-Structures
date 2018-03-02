#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#define MAX 3000100

using namespace std;

int x[MAX];

void swap(int* a, int*b){
	int tmp=*a;
	*a=*b;
	*b=tmp;	
}

void quicksort(int x[], int a, int b){
    if (a>=b) return;
	int m=a+rand()%(b-a+1);
	int k=x[m];
	int l=a-1;
	int r=b+1;
	do{
		while (x[++l]<k);
		while (x[--r]>k);
		if (l>=r) break;
		swap(&x[l] , &x[r]);
	}
    while (+1);
	quicksort(x,a,r);
	quicksort(x,r+1, b);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n=0, i=0;
	while (scanf("%d", &n)>0){
		i++;
		x[i]=n;
	}
	n=i;
	quicksort(x,1,n);
	for (int i=1; i<=n; i++)
	cout<<x[i]<<' ';
	return 0;
}
