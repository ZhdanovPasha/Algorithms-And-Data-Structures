#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <time.h>

using namespace std;
const int N_MAX = 55;

struct Tree{
	Tree* Left;
	Tree* Right;
	char data[N_MAX] ;
	int size;
	int y;
	Tree(){}
	Tree(char* str){
		Right = NULL;
		Left = NULL;
		size = 1;
		y = rand();
		strcpy(data, str);
	}
};

int Size(Tree* t);
Tree* Pos(Tree* t, int ind);
void Split( Tree* t, int ind, Tree*& l, Tree*& r);
Tree* Merge(Tree* l, Tree* r);
void Add(Tree*& t, char c[N_MAX]);
void Ins(Tree*& u, int ind, char c[N_MAX]);
void Delete(Tree*& u, int indl, int indr);
void write(Tree* t);

int main(void){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	srand(time(NULL));
	Tree* Root = NULL;
	char s[N_MAX], c[N_MAX];
	int a, k, b;
	scanf("%s", s);
	while (strcmp(s, "END") != 0){
		if (s[0] == 'A'){
			scanf("%s\n", c);
			Add(Root, c);
		}
		if (s[0] == 'I'){
			scanf("%d %s\n", &k, c);
			Ins(Root, k - 1, c);
		}
		if (s[0] == 'D'){
			scanf("%d %d\n", &a, &b);
			Delete(Root, a - 1, b - 1);
		}	
		if (s[0] == 'K'){
			scanf("%d\n", &k);
			Tree* res = new Tree;
			res = Pos(Root, k - 1); 
			if (res == NULL) 
				printf("OUT OF RANGE\n");
			else 
				printf("%s\n", res->data);
		}
		scanf("%s", s);
	}
	printf("\n");
	return 0;
}

int Size(Tree* t){
	if (t == NULL) 
		return 0;
	return t->size;
}

Tree* Pos(Tree* t, int ind){
	if (t == NULL || ind >= t->size)
		return NULL;
	int L = Size(t->Left);
	if (ind == L)
		return t;
	else if (ind < L)
		return Pos(t->Left, ind);
	else 
		return Pos(t->Right, ind - L - 1);
}

void Split(Tree* t, int ind, Tree*& l, Tree*& r){
	if (t == NULL){
		l = NULL;
		r = NULL;
		return;
	}
	if (ind <= Size(t->Left)){
		Split(t->Left, ind, l, t->Left);
		r = t;
	}
	else{
		Split(t->Right, ind - Size(t->Left) - 1, t->Right, r);
		l = t;
	}
	t->size = 1 + Size(t->Left) + Size(t->Right);
}

Tree* Merge(Tree* l, Tree* r){
	if (l == NULL)
		return r;
	if (r == NULL)
		return l;
	Tree* u = new Tree;
	if (l->y > r->y){
		l->Right = Merge(l->Right, r);
		u = l;
	} else {
		r->Left = Merge(l, r->Left);
		u = r;
	}
	u->size = Size(u->Left) + Size(u->Right) + 1;
	return u;
}

void Add(Tree*& t, char c[N_MAX]){
	Tree* v = new Tree(c);
	t = Merge(t,v);	
}

void Ins(Tree*& u, int ind, char c[N_MAX]){
	Tree* l;
	Tree* r;
	Split(u,ind,l,r);
	Tree* v = new Tree(c);
	l = Merge(l,v);
	u = Merge(l,r);
} 

void Delete(Tree*& u, int indl, int indr){
	Tree* l;
	Tree* r;
	Tree* v;
	Split(u, indl, l, r);
	Split(r, indr - indl + 1, v, r);
	u = Merge(l, r);
}

void write(Tree* t){
	if (t == NULL) return;
	cout << endl;
	printf ("t=%d ", t);
	printf ("t->data= ");
	for (int i = 0; t->data[i]; i++)
		printf("%c", t->data[i]);
	printf (" size=%d, y=%d,R=%d, L=%d\n ", t->size, t->y, t->Right, t->Left);
	write(t->Left);
	write(t->Right);
}
