#include "C.h"
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int sid = 300 + 5;

static int n, T1, T2, M1, M2;
static int a[sid];

static void error(const char *msg) {
	printf("%s\n", msg);
	exit(0);
}

static void init() {
	T1 = T2 = 0;
	scanf("%d%d%d", &n, &M1, &M2);
	for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
	srand(time(0) | n ^ (M2 * M1));
}

int qry1(int i) {
	if(++ T1 > M1) error("too many 1 operators !");
	if(i < 0 || i >= n) error("the argument i in 1 operator is not in [0, n - 1]");
	return a[i];
}

static vector<int> to_see, ans ;
int abs(int x) { return (x > 0) ? x : -x; }
vector<int> qry2(const vector<int> &S) {
	if(++ T2 > M2) error("too many 2 operators !");
	to_see = S; sort(to_see.begin(), to_see.end());
	for(int i = 0; i < to_see.size(); i ++) {
		if(to_see[i] < 0 || to_see[i] >= n) error("the argument i in 2 operator is not in [0, n - 1]");
		if(i && to_see[i] == to_see[i - 1]) error("the argument i in 2 operator are not unique");
	}
	ans.clear();
	for(int i = 0; i < to_see.size(); i ++) for(int j = 0; j < i; j ++)
		ans.push_back( abs( a[ to_see[i] ] - a[ to_see[j] ] ) );
	random_shuffle(ans.begin(), ans.end());
	return ans ; 
}

void answer(const vector<int> &ret) {
	if(ret.size() != n) error("your answer's length is not n");
	for(int i = 0; i < ret.size(); i ++) 
		if(ret[i] != a[i]) error("Wrong Answer");
	printf("Correct!\n");
	printf("You use (%d) operator 1 and (%d) operator 2\n", T1, T2);
	exit(0);
}

int main() {
	init();
	find(n, M1, M2);
	return 0;
}
