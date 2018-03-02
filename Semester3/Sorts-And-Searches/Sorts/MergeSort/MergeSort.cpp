#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

const int nmax = 3E7 + 10;
int a[nmax], y[nmax];

void mergesort(int x[nmax], int a, int b){
	if (a>=b) return;
	int m=(a+b)/2;
	mergesort(x,a,m);
	mergesort (x, m+1, b);
	int i=a;
	int j=m+1;
	for (int r=a; r<=b; r++){
	    if ((j>b) || ((i<=m) && (x[i]<x[j]))){
		  	y[r]=x[i];
	    	i++;
		} else {	
			y[r]=x[j];
			j++;
		} 		
	}
	for (int k=a; k<=b; k++)
		x[k]=y[k];
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n=0, x=0;
	while (scanf("%d", &x)>0) {
		n++;
		a[n]=x;
	}
	mergesort(a,1,n);
	for (int i=1; i<=n; i++)
		cout<<a[i]<<' ';
	return 0;
}
