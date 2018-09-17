#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

const int WORD_SIZE = 33;
const char DELETED[] = ".delete.";
char e[WORD_SIZE];

struct Tree{
	char data[WORD_SIZE];
	Tree* L;
	Tree* R;
};

void Add(Tree*& t, char s[WORD_SIZE]);
void DeleteMin (Tree*& t);
void Delete(Tree*& t, char k[WORD_SIZE]);
int Search(Tree*& t, char s[WORD_SIZE], int time);

int main(void){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	char slovo[33];
	char sign;
	Tree* t = new Tree;
	strcpy(t->data, DELETED);
	t->L = NULL;
	t->R = NULL;
	int n = 1;
	int j = 0;
	while (scanf("%c%s\n", &sign, &slovo)>0){
		j++;
		if (sign == 'E') break;
		if (sign == '+') Add(t,slovo);
		if (sign == '-') Delete(t,slovo);
		if (sign == '?'){
			for (int i = 0; i < strlen(slovo); i++)
				printf("%c", slovo[i]);
			printf(" %d\n", Search(t, slovo, n));
		}
	}
	return 0;
}

void Add(Tree*& t, char s[WORD_SIZE]){
	if (strcmp(t->data, DELETED) == 0){
		strcpy(t->data, s);
	} else if (strcmp(s, t->data) < 0){
		if (t->L == NULL){
			Tree* e = new Tree;
			t->L = e;
			strcpy(e->data, DELETED);
			e->R = NULL;
			e->L = NULL;
		}
		Add(t->L, s);
	} else if (strcmp(s,t->data) > 0){
		if (t->R == NULL){
			Tree* e = new Tree;
			t->R = e;
			strcpy(e->data, DELETED);
			e->R = NULL;
			e->L = NULL;
		}
		Add(t->R, s);	
	}
}

void DeleteMin (Tree*& t){
	if (t->L != NULL){
		return DeleteMin(t->L);
	} else {
		strcpy(e, t->data);
		t = t->R;
	}
}

void Delete(Tree*& t, char k[WORD_SIZE]){
	if (t == NULL)
		return ;
	if (strcmp(k, t->data) < 0){
		Delete(t->L, k);
	} else if (strcmp(k, t->data) > 0){	
		Delete(t->R, k);
	} else if(t->L == NULL){
		t = t->R;
	} else if (t->R == NULL){
		t = t->L;
	} else {
		DeleteMin(t->R);
		strcpy(t->data, e);
	}
}

int Search(Tree*& t, char s[WORD_SIZE], int time){
	if (t == NULL)
		return 0;
	if (strcmp(t->data, s) == 0)
		return time;
	if (strcmp(s, t->data) < 0)
		return Search(t->L, s, time + 1);
	else if (strcmp(s, t->data) > 0)
		return Search(t->R, s, time + 1); 
}
