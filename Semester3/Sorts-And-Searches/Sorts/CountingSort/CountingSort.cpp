#include <iostream>
#include <stdio.h>
#include <math.h>
#define MAX_1 3000100
#define MAX_2 1000100

using namespace std;

int a[MAX_1], b[MAX_1];
int c[MAX_2];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n=0, x, min, max;
	while (scanf("%d", &x)>0) {
		n++;
		a[n]=x;
		if (n==1) {
			max=a[n];
			min=a[n];
		} 
		if (a[n]>max) max=a[n];
		if (a[n]<min) min=a[n];
	}
	for (int i=min; i<=max; i++)
		c[i]=0;
	for (int i=1; i<=n; i++)
		c[a[i]]++;
	for (int i=min+1; i<=max; i++)
		c[i]=c[i]+c[i-1];
	for (int i=1; i<=n; i++){
		int r=a[i];
		b[c[r]]=a[i];
		c[r]--;
	}			
	for (int i=1; i<=n; i++)
		a[i]=b[i];
	for (int i=1; i<=n; i++)
		printf("%d ",a[i]);	
	return 0;
}
