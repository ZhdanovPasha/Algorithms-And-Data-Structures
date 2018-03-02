#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

const int nmax = 1E5 + 10;

int a[nmax];

void swap(int* l, int* r){
	int tmp = *l;
	*l = *r;
	*r = tmp;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int x, n = 0;
    while (scanf("%d", &x)>0){
       n++;
       a[n] = x;
    }
    int m = 0;
	for(int i = 1; i < n; i++){
    	m = i;
    	for (int j = i + 1; j <= n; j++)
    		if (a[j] < a[m]){
    			m = j;	
			}
    	swap(a[i], a[m]);	
    }
    for (int i = 1; i <= n; i ++){
    	cout << a[i] << ' ';
    }
    return 0;
}
