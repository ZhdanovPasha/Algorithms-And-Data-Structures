#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

const int nmax = 3E7 + 10;
int a[nmax];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n=0, x;
	while (scanf("%d", &x)>0){
		n++;
		a[n]=x;
	}
	int h=1, d=10;
	while (h<n/d) h=3*h+1;
	while (h>=1){
		for (int  r=1; r<=h; r++){
			int i=r+h;
			while (i<=n){
				int j=i-h;
		        int tmp=a[i];
				while ((j>0) && (a[j]>tmp)){
					a[j+h]=a[j];
					j=j-h;
				}
				a[j+h]=tmp;
				i=i+h;
			}
		}
		h=h/3;
	}
    for (int i=1; i<=n; i++)
	cout<<a[i]<<' ';
	return 0;
}
