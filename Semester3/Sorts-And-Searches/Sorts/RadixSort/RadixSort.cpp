#include <iostream>
#include <stdio.h>
#include <math.h>
#define MAX 3000100
#define BASE 8

using namespace std;

int a[MAX], d[MAX];
int b[BASE][MAX];
int c[BASE];

int check(int a);
int make_zero(int b[BASE][MAX],int c[BASE]);

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n=0, x, max=0;
	while (scanf("%d", &x)>0){
		n++;
		a[n]=x;
		d[n]=x;
		if (check(x)>max) max=check(x);
	}
	int k=0;
	while (k<=max){
	   	for (int j=0; j<=BASE-1; j++)
				c[j]=0;
	   	for (int i=1; i<=n; i++){
			int mod=d[i]%BASE;
			c[mod]++;
			b[mod][c[mod]]=a[i];
			d[i]=d[i]/BASE;
	    }
	    int z=0;
		for (int i=0; i<=BASE-1; i++){
	    	for (int j=1; j<=c[i]; j++){
				z++;
				a[z]=b[i][j];
				d[z]=b[i][j];
				int h=k;
				while (h>0){
					d[z]/=BASE;
					h--;
				}
			} 
		}
		make_zero(b,c);
		k++;
	}
	for (int i=1; i<=n; i++)
	cout<<a[i]<<' ';
	return 0;
}

int check(int a){
	int res=0;
	while (a>0){
		a/=BASE;
		res++;
	}
	return res;
}

int make_zero(int b[BASE][MAX],int c[BASE]){
	for(int i=0; i<=BASE-1; i++)
		for (int j=0; j<=c[i]; j++)
			b[i][j]=0;
}
