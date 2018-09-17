#include <stdio.h>
#include <cstring>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

struct Tree{
	string data;
	Tree* Left;
	Tree* Right;
	int height;
	Tree(string s){
		data=s;
		height=1;
		Left=NULL;
		Right=NULL;
	}
};
int Height(Tree* t);
int balanceFactor(Tree* t);
void fix(Tree* t);
Tree* SLR(Tree* p);
Tree* SRR(Tree* q);
Tree* Balance(Tree* p);
Tree* findMin(Tree* p);
Tree* RemoveMin(Tree* p);
void Remove(Tree*& p, string s);
int Search(Tree* t, string s, int time);
void Add(Tree*& t ,string s);
void write(Tree* t);

int main(void){
	std::ios::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w" , stdout);
	char sign;
	string s;
	Tree* t = NULL;
	int count = 0;
	cin >> sign >> s;
	while (sign != 'E'){
		count++;
		if (sign == '+') Add(t,s);
		if (sign == '-') Remove(t,s);
		if (sign == '?') {
			int time = 1;
			cout << s << ' ' << Search(t, s, time) << endl;
		}
		cin >> sign >> s;
	}
	return 0;
}

int Height(Tree* p){
	return p ? p->height : 0;
}

int balanceFactor(Tree* t){
	return Height(t->Right) - Height(t->Left);
}

void fix(Tree* t){
	int hl = Height(t->Left);
	int hr = Height(t->Right);
	t->height = (hl > hr ? hl : hr) + 1;
}

Tree* SRR(Tree* p){
	Tree* q = p->Left;
	p->Left = q->Right;
	q->Right = p;
	fix(p);
	fix(q);
	return q;
}

Tree* SLR(Tree* q){
	Tree* p = q->Right;
	q->Right = p->Left;
	p->Left = q;
	fix(q);
	fix(p);
	return p;
}

Tree* Balance(Tree* p){
	fix(p);
	if (balanceFactor(p) == 2){
		if (balanceFactor(p->Right) <0)
			p->Right = SRR(p->Right);
		return SLR(p);
	}
	if (balanceFactor(p) == -2){
		if (balanceFactor(p->Left) > 0)
			p->Left = SLR(p->Left);
		return SRR(p);
	}
	return p ;	
}

void Add(Tree*& p ,string s){
	if (!p){
		p = new Tree(s);
		return;
	}
	if(p->data == s)
		return;
	if (s < p->data)
		Add(p->Left, s);
	else 
		Add(p->Right, s);
	p = Balance(p);
}

Tree* findMin(Tree* p){
	return p->Right ? findMin(p->Right) : p;
}

Tree* RemoveMin(Tree* p){
	if (p->Right == 0)
		return p->Left;
	p->Right = RemoveMin(p->Right);
	return Balance(p);	
}

void Remove(Tree*& p, string s){
	if (p == NULL) return ;
	if (s < p->data)
		Remove(p->Left, s);
	else 
		if (s > p->data)
			Remove(p->Right, s);
		else {
			Tree* q = p->Left;
			Tree* r = p->Right;
			if(!r && !q){
				p = NULL;
				return;
			} 
			if (!r){
				p = q;
				return;
			} 
			if (!q){
				p = r;
				return;
			} 
			Tree* min = findMin(q);
			min->Left = RemoveMin(q);
			min->Right = r;
			p = Balance(min);
		}
	p = Balance(p); 
}

int Search(Tree* t, string s, int time){
	if (t == NULL)
		return 0;
	if (t->data == s)
		return time;
	if (s < t->data)
		return Search(t->Left, s, time + 1);
	else if (s > t->data)
		return Search(t->Right, s, time + 1); 
}

void write(Tree* t){
	if (t == NULL) return;
	cout << "t=" << t;
	cout << " t->data= " << t->data;
	cout << " R=" << t->Right << " L= " << t->Left << endl;
	write(t->Left);
	write(t->Right);
}
