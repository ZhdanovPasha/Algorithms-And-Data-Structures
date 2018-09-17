#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

struct Tree{
	long long data;
	Tree* Left;
	Tree* Right;
	int size;
	int y;
	Tree(){
	}
	Tree(long long x){
		Left = NULL;
		Right = NULL;
		data = x;
		y = rand();
		size = 1;	
	}
};

int n = 0;

int Size(Tree* t);
Tree* Pos(Tree* t, int ind);
void Split(Tree* t, int ind, Tree*& l, Tree*& r);
Tree* Merge(Tree* l, Tree* r);
void Add(Tree*& t, long long c);
void Ins(Tree*& u, int ind, long long c);
void Delete(Tree*& u, int indl, int indr);
void write(Tree* t);

int main(){
	freopen("river.in", "r", stdin);
	freopen("river.out", "w", stdout);
	srand(time(NULL));
	Tree* t = NULL;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int x = 0;
		scanf("%d", &x);
		Ins(t, i, x);		
	}	
	long long sum = 0;
	for(int i = 0; i < n; i++){
		long long part = Pos(t,i)->data;
		sum += part * part;
	}
	cout << sum << endl;
	int k = 0;
	scanf("%d\n", &k);
	for(int i = 0; i < k ;i++){
		int v, e;
		scanf("%d%d\n", &e, &v);
		v--;
		long long d = Pos(t,v)->data;
		long long p1 = 0, p2 = 0;
		p1= d/2;
		p2= d/2;
		if (d%2) 
			p2++;
		if(e == 1){
			if(v == 0){
				sum -= (Pos(t, 0)->data *Pos(t, 0)->data);
				sum -= (Pos(t, 1)->data *Pos(t, 1)->data);
				Pos(t, 1)->data += d;
				sum += (Pos(t, 1)->data *Pos(t, 1)->data);
				Delete(t, 0, 0);
			}
			if(v == (n - 1)){
				sum -= (Pos(t, n - 1)->data * Pos(t, n - 1)->data);
				sum -= (Pos(t, n - 2)->data * Pos(t, n - 2)->data);
				Pos(t, n - 2)->data += d;
				sum += (Pos(t, n - 2)->data * Pos(t, n - 2)->data);
				Delete(t, n - 1, n - 1);
			}
			if(v != 0 && (v != (n - 1))){
				sum -= (Pos(t, v-1)->data *Pos(t, v - 1)->data);
				sum -= (Pos(t, v)->data * Pos(t, v)->data);
				sum -= (Pos(t, v + 1)->data * Pos(t, v + 1)->data);
				Pos(t, v - 1)->data += p1;
				Pos(t, v + 1)->data += p2;
				sum += (Pos(t, v - 1)->data * Pos(t, v - 1)->data);
				sum += (Pos(t, v + 1)->data * Pos(t, v + 1)->data);
				Delete(t, v, v);
			}
			n--;
		} else {
			sum -= (Pos(t, v)->data * Pos(t, v)->data);
			Ins(t, v, p1);
			Pos(t, v + 1)->data -= p1;
			sum += (Pos(t, v)->data * Pos(t, v)->data);
			sum += (Pos(t, v + 1)->data * Pos(t, v + 1)->data);
			n++;
		}
		cout << sum << endl;
	}
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
		Split(t->Left, ind, l, t->Left );
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
	}
	else {
		r->Left=Merge(l, r->Left);
		u = r;
	}
	u->size = Size(u->Left) + Size(u->Right) + 1;
	return u;
}

void Add(Tree*& t, long long c){
	Tree* v = new Tree(c);
	t = Merge(t,v);	
}

void Ins(Tree*& u, int ind, long long c){
	Tree* l;
	Tree* r;
	Split(u, ind, l, r);
	Tree* v = new Tree(c);
	l = Merge(l, v);
	u = Merge(l, r);
} 

void Delete(Tree*& u, int indl, int indr){
	Tree* l;
	Tree* r;
	Tree* v;
	Split(u, indl, l, r);
	Split(r, indr - indl + 1, v, r);
	u = Merge(l, r);
}
