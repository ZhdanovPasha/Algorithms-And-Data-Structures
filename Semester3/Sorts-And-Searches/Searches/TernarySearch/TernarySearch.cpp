#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#define MAX 1000010

using namespace std;

int t[MAX];

int search(int a, int b);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n = 0, x = 0;
	while (scanf("%d", &x)>0){
		n++;
		t[n] = x;
	}
	int res = search(1,n);
	cout << res;
	return 0;
}

int search(int a, int b){
	do{
		int h = (b - a) / 3;
		int a1 = a + h;
		int b1 = b - h;
		if ((a + h == a) || (b - h == b)) {
			if ((t[a] >= t[(a + b) / 2]) && (t[a] >= t[b])) return t[a];
			if ((t[b] >= t[(a + b) / 2]) && (t[b] >= t[a])) return t[b];
			if ((t[(a + b) / 2] >= t[a]) && (t[(a + b) / 2] >= t[b])) return t[(a + b) / 2];	
		}
		if (t[a1] < t[b1]){
			a=a1;
		} else{
			b=b1;	
		} 
    }
    while(1);
}	
