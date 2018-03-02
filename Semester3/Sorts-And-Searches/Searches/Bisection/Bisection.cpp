#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>

using namespace std;

const double MAX = 2E13 + 10;
double a,b,c,d;

double bisection  (double l, double r);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	printf("%.6lf", bisection(0,MAX));
	return 0;
}

double bisection (double l, double r){
	do {
		double x=(l+r)/2;
		double f_a=a*log(x+b);
	    double f_b=c/(d+x);
		if ((x==l) || (x==r))
			return x;
		if (f_a>f_b) r=x;
		else l=x;	
	}
	while (1);
}
