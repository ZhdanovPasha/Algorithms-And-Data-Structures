#include <iostream>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <vector>

using namespace std;

struct Tree{
	int x;
	int y;
	Tree* L;
	Tree* R;
};

void write(Tree* t);
Tree* Merge(Tree*& l, Tree*& r);
void Split(Tree* t, int x, Tree*& l, Tree*& r);
void Add(Tree*& t, int x, int y);
void Delete(Tree*& t, int x);
int Search(Tree* t, int x, int time);

int main(void){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w" , stdout);
	char sign;
	Tree* t = new Tree;
	t = NULL;
	int x = 0, y = 0;
	scanf("%c", &sign);
	while (sign != 'E'){
		if (sign  == '+') 
			scanf("%d%d\n", &x, &y);
		else 
			scanf("%d\n", &x);		
		if (sign == '+' && !Search(t, x, 1)) 
			Add(t, x, y);
		if (sign == '-') 
			Delete(t, x);
		if (sign == '?') 
			printf("%d %d\n",  x, Search(t, x, 1));
		scanf("%c", &sign);	
	}
	return 0;	
}

Tree* Merge(Tree*& left, Tree*& right){
	if (left == NULL)
		return right;
	if (right == NULL)
		return left;
	if (left->y > right->y){
		left->R = Merge(left->R, right);
		return left;
	}
	if (right->y >= left->y){
		right->L = Merge(left, right->L);
		return right;
	} 
}

void Split(Tree* t, int x, Tree*& l, Tree*& r){
	if (t == NULL){
		l = NULL;
		r = NULL;
		return;
	}
	if (t->x < x){
		Split(t->R, x, t->R, r);
		l = t;
		return;
	} else {
		Split(t->L, x, l ,t->L);
		r = t;
		return;
	}
}

void Add(Tree*& t, int x, int y){
	if (t == NULL || y >= t->y){
		Tree* L = new Tree;
		Tree* R = new Tree;
		Split(t, x, L, R);
		Tree* p = new Tree;
		p->x = x;
		p->y = y;
		p->L = L;
		p->R = R;
		t = p;
		return;
	}
	if (x < t->x)
		Add(t->L, x, y);
	else if (x > t->x)
		Add(t->R, x ,y);
}
	
void Delete(Tree*& t, int x){
	if (t == NULL)
		return;
	if (t->x == x)
		t = Merge(t->L, t->R);
	else if (x < t->x)
		Delete(t->L, x);
	else 
		Delete(t->R, x);
}

int Search(Tree* t, int x, int time){
	if (t == NULL) return 0;
	if (t->x == x) return time;
	if (t->x > x) return Search(t->L, x, time + 1);
	else return Search(t->R, x, time + 1);
}

void write(Tree* t){
	if (t == NULL) return;
	cout << endl;
	printf ("x=%d, y=%d,R=%d, L=%d\n ", (*t).x, (*t).y, t->R, t->L);
	write(t->L);
	write(t->R);
}
