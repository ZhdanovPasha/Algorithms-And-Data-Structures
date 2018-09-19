#include <stdio.h>

using namespace std;
const int nmax = 2048;
const int degtwo = 1024;

int T[nmax][nmax];
void Init();
void Change(int i, int j, int d);
int Sum(int i, int j);
int Isum(int i, int j);

int main(){
	freopen("election.in", "r", stdin);
	freopen("election.out", "w", stdout);
	int n;
	Init();
	scanf("%d\n", &n);
	for(int i = 1; i <= n ;i++){
		char c;
		int x, y, x1, y1, x2, y2;
		scanf("%c", &c);
		if(c == 'R'){
			scanf("%d%d%d%d\n", &x1, &y1, &x2, &y2);
			int res = 0, ans = 0;
			if(x1 == x2 && y1 == y2){
				res = T[x1 + degtwo - 1][y1 + degtwo - 1];
				ans = 1 - res;
			} else {
				int flag = 0;
				res = Sum(x2, y2);
				if(y1 != 1){
					res -= Sum(x2, y1 - 1);
					flag++;
				}
				if(x1 != 1){
					res -= Sum(x1 - 1, y2);
					flag++;
				}
				if (flag == 2 && x1 > 1 && y1 > 1) res += Sum(x1 - 1, y1 - 1);
				ans = (x2 - x1 + 1) * (y2 - y1 + 1);	
				ans -= res;
			}
			printf("%d %d\n", res,ans);
		} else {
			scanf("%d%d\n", &x, &y);
			if(c == 'A' && T[degtwo + x - 1][degtwo + y - 1] != 1) Change(x, y, 1);
			else if(c == 'B' && T[degtwo + x - 1][degtwo + y - 1] != 0 ) Change(x, y, -1);
		}
	}
	return 0;
}

void Init(){
	for(int i = degtwo; i < nmax; i++)
		for(int j = degtwo; j < nmax; j++)
			if((!(i%2) && !(j%2)) || (i%2 && j%2))
				Change(i - degtwo + 1, j - degtwo + 1, 1);
			else 
				T[i][j] = 0;
}

void Change(int i, int j, int d){
	i += degtwo - 1;
	j += degtwo - 1;
	int j0 = j;
	while(i > 0){
		j = j0;
		while(j > 0){
			T[i][j] += d;
			j /= 2;
		}
		i /= 2;
	}
}

int Sum(int i, int j){
	i += degtwo - 1;
	j += degtwo - 1;
	int res = Isum(i,j);
	while(j > 1){
		if(j%2 == 1)
			res += Isum(i, j - 1);
		j /= 2;	
	}
	return res;
}

int Isum(int i, int j){
	int res = T[i][j];
	while(i > 1){
		if(i%2 == 1)
			res += T[i - 1][j];
		i /= 2;
	}
	return res;
}
