#include <stdio.h>
#include <string.h>
#include <cstdlib>

using namespace std;

const int nmax = 30;

struct Tree{
	char data[nmax];
	Tree* U;
	Tree* L;
	Tree* R;
};

Tree* Make(char data[nmax], Tree* U, Tree* L, Tree* R);
void swap(char x[nmax], char y[nmax]);
void SLR(Tree *a);
void SRR(Tree* a);
void Splay(Tree* x);
void Search(Tree* root, char str[nmax]);
void Add(Tree** root, char str[nmax]);
void Delete(Tree** root, char str[nmax]);


int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Tree* root = NULL;
	char c, str[nmax];
	scanf("%c%s\n", &c, str);
	while(c != 'E'){
		if(c == '+') Add(&root, str);
		if(c == '?') Search(root, str);
		if(c == '-') Delete(&root, str);
		scanf("%c%s\n", &c, str);
	}
	return 0;
}

Tree* Make(char data[nmax], Tree* U, Tree* L, Tree* R){
	Tree* u = new Tree;
	strcpy(u->data, data);
	u->U = U;
	u->L = L;
	u->R = R;
	return u;	
}

void swap(char x[nmax], char y[nmax]){
	char tmp[nmax];
	strcpy(tmp, x);
	strcpy(x, y);
	strcpy(y, tmp);
}

void SLR(Tree* a){
	Tree *b = a->L;
	Tree *R = a->R;
	Tree* P = b->L;
	Tree* Q = b->R;
	swap(a->data, b->data);
	a->L = P;
	if(P) P->U = a;
	a->R = b;
	b->L = Q;
	b->R = R;
	if(R) R->U = b;
}

void SRR(Tree* a){
	Tree* b = a->R;
	Tree* P = a->L;
	Tree* Q = b->L;
	Tree* R = b->R;
	swap(a->data, b->data);
	a->L = b;
	a->R = R;
	if(R) R->U = a;
	b->L = P;
	if(P) P->U = b;
	b->R = Q;
}


void Splay(Tree* x){
	if(!(x->U)) return;
	Tree* p = x->U;
	if(!(p->U)){
		if(x == p->L) 
			SLR(p);
		else
			SRR(p);
		return;
	}
	Tree*g = p->U;
	if(p == g->L){
		if(x == p->L){
			SLR(g);
			SLR(g);
		} else {
			SRR(p);
			SLR(g);
		}
	} else {
		if(x == p->R){
			SRR(g);
			SRR(g);
		} else {
			SLR(p);
			SRR(g);
		}
	}
	Splay(g);
}

void Search(Tree* root, char str[nmax]){
	int h = 0;
	if(root){
		h = 1;
		Tree* u = root;
		while((u->L && strcmp(str, u->data) < 0) || (u->R && strcmp(str, u->data) > 0)){
			if(strcmp(str, u->data) < 0) 
				u = u->L;
			else 
				u = u->R;
			++h;
		}
		if(strcmp(str, u->data)) 
			h = 0;
		else 
			Splay(u);
	}
	printf("%s %d\n", str, h);
}

void Add(Tree** root, char str[nmax]){
	if(!*root){
		*root = Make(str, 0, 0, 0);
	} else {
		Tree* u= *root;
		while((u->L && strcmp(str, u->data) < 0) || (u->R && strcmp(str, u->data) > 0)){
			if(strcmp(str, u->data) < 0) 
				u = u->L;
			else 
				u = u->R;
		}
		if(!strcmp(str, u->data)) return;
		Tree* v=Make(str, u, 0, 0);
		if(strcmp(str, u->data) < 0) u->L = v;
		else u->R = v;
		Splay(v);
	}
}

void Delete(Tree** root, char str[nmax]){
	if(!*root) return;
	Tree* u = *root;
	while((u->L && strcmp(str, u->data) < 0) || (u->R && strcmp(str, u->data) > 0)){
		if(strcmp(str, u->data) <0)
			u = u->L;
		else 
			u = u->R;
	}
	if(strcmp(str, u->data)) return;
	Tree* t;
	Tree*U = u->U;
	if(u->L && u->R){
		t = u->R;
		while(t->L) 
			t = t->L;
		swap(u->data, t->data);
		u = t;
	}
	if(u->L) 
		t = u->L;
	else
		t = u->R;
	if(t) t->U = u->U;
	if(u != *root){
		if(u == u->U->L) 
			u->U->L = t;
		else 
			u->U->R=t;
	} else {
		*root=t;
	}	
	if(U) 
		Splay(U);
}
