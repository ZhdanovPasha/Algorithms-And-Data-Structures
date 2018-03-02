#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#define MAX 1000100
using namespace std;

int x[MAX];
int n=0;

void swap(int* a, int* b){
	int tmp= *a;
	*a=*b;
	*b=tmp;
}

int search(int a, int b, int k){
    if (a>=b){
    	if (a==b) return x[a];
    }
	int l=a-1, r=b+1;
	int m = a + rand()%(b-a+1);
	int z=x[m];
	do {
		while (x[++l]<z);
		while (x[--r]>z);
		if (l>=r) break;
	    swap(&x[l], &x[r]);
    }
    while (+1);
    if (k<=r){
    	return (search(a,r,k));
	} else {
	    return search (r+1,b,k);		
	}
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int  l=0, k=0;
    scanf("%d\n", &k);
    while (scanf("%d", &l)==1) {
    	n++;
    	x[n]=l;
    }
    cout<<search(1,n,k);
  	return 0;
}
