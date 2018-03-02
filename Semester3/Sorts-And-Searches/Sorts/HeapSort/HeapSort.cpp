#include <iostream>
#include <stdio.h>
#define MAX 3000100
using namespace std;

int a[MAX];
int n=0;

void swap (int* a, int* b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

void lift(int c){
	while (c>1){
		int p=c/2;
		if (a[p]>a[c]) break;
		swap(&a[c], &a[p]);
		c=p;
	
	
	}
}

void add(int x){
	n=n+1;
	a[n]=x;
	lift(n);
}

void sift(int p ){
	while (2*p<=n){
			int c=2*p;
			if ((c<n) && (a[c+1]>a[c]))
				c++;
			if (a[p]>a[c])
				break;
			swap(&a[p], &a[c]);
			p=c;	
	}
}

int extract_max(){
	int tmp=a[1];
	a[1]=a[n];
	n--;
	sift(1);
	return tmp;
}

void heapsort(int m, int a[MAX]){
	for(int i=1; i<=m; i++)
		add(a[i]);
	for (int i=m; i>=2; i--)	
		a[i]=extract_max();
}


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int x=0, m=0;
	while (scanf("%d", &x)>0){
		m++;
		a[m]=x;
	}
    heapsort(m,a);	
	for (int i=1; i<=m; i++)
		cout<<a[i]<<' ';
	return 0;
}
