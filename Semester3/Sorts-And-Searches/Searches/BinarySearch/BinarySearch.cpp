#include <iostream>
#include <stdio.h>
#include <math.h>
#define MAX 1000100

using namespace std;

int a[MAX];

int search_1(int n, int x[], int k);
int search_2(int n, int x[], int k);
int search_3(int n, int x[], int k);

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	char c[2];
	int k, n=0, x=0;
	scanf("%c %d\n", &c[1], &k);
	while (scanf("%d", &x)==1){
		n++;
		a[n]=x;
	}
	if (c[1]=='=') cout<<search_1(n,a,k);
	if (c[1]=='<') cout<<search_2(n,a,k);
    if (c[1]=='>') cout<<search_3(n,a,k);
	return 0;
}

int search_1(int n,int x[], int k){
	if (x[1]>k) return 0;
	if (x[1]==k) return 1;
	if (x[n]<k) return 0;
	int a=1,b=n;
	while (a+1 <b){ 
		int c=((a+b)/2);
		if (x[c]<k)	
			a=c;
		else
			b=c;	
    }
    if (x[b]==k)
    	return b;
    else 
		return 0;
}
int search_2(int n,int x[], int k){
	int res=0;
	if (x[1]>k) return 0;
	if (x[1]<k) res=1;
	if (x[n]<k) return n;
	int a=1,b=n;
	while (a+1 <b){ 
		int c=((a+b)/2);
		if (x[c]<k){	
			a=c;
			res=a;
     	}
		else
			b=c;	
    }
    return res;
}

int search_3(int n,int x[], int k){
    int res=0;
	if (x[1]>k) return 1;
	if (x[n]>k) res=n;
	if (x[n]<k) return 0;
	int a=1,b=n;
	while (a+1 <b){ 
		int c=((a+b)/2);
		if (x[c]<k)	
			a=c;
		else {
			b=c;
			res=b;
	    }
    }
    return res;
}
