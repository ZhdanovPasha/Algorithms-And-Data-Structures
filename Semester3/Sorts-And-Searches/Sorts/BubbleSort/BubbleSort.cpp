#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

const int NMAX = 1E7 + 10;

int a[NMAX];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int x = 0, n = 0;
    while (scanf("%d", &x)>0){
    	n++;
    	a[n] = x;
    }
    for (int i = 2; i <= n; i++){
    	if (a[i] > a[i-1]) continue;
    	int j = i-1;
    	int tmp = a[i];
    	while ((j > 0) && (tmp < a[j])){
    		a[j + 1] = a[j];
    		j--;
    	}
    	a[j + 1] = tmp;
    }
    for (int i = 1; i <= n; i++)
    	cout << a[i] << ' ';
	return 0;
}
