#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#define MAX 22222

using namespace std;

const int WORD_SIZE = 20, ARR_SIZE = 2E4;
const string EMPTY = ".empty.", DELETED = ".deleted.";
string s[MAX], x[MAX];

void make();
int search(char q[WORD_SIZE]);
void add(char q[WORD_SIZE]);
void del(char q[WORD_SIZE]);
int H(const char*str);

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    char q[WORD_SIZE];
    char ch;
    make();
    while (scanf("%c%s\n", &ch, &q)>0){
		if (ch == 'E') break;
		if (ch == '+') {
			add(q);
		}
		if (ch == '-') del(q);  
		if (ch == '?') {
			if(search(q) == -1) {
				printf("-");
				printf("%s\n", q);
			}
			else {
				printf("+");
				printf("%s\n", q);
		    }
	    }
	}
	return 0;
}

void make(){
	for (int i = 0; i < MAX; i++)
		x[i] = ".empty.";
}

unsigned int H(char* str){
	unsigned int hash=2139062143;
	for ( ; *str; str++){
		hash = hash*37 + *str;
	}
	return hash % ARR_SIZE;	
}

int search(char y[WORD_SIZE]){
    unsigned int p = H(y);
   	do {
		if (x[p] == y)
			return p;
		if 	(x[p] == EMPTY)
			return -1;
		p = (p + 1) % ARR_SIZE;
	}
	while(1);
}

void add(char y[WORD_SIZE]){
	if (search(y) >= 0){
		return;
	}
	int p = H(y);
	do{
		if ((x[p] == EMPTY) || (x[p] == DELETED)){
			x[p] = y;
			return;
	    }
		p = (p + 1) % ARR_SIZE;
    }
	while (1);
}

void del(char y[WORD_SIZE]){
	int p = H(y);
	do{ 
		if (x[p] == y){                  
			x[p] = DELETED;
			return;
		} 
		if (x[p] == EMPTY){
			return;
	    }
	    p = (p + 1) % ARR_SIZE;
    }
	while (1);
}
