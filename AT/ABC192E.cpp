#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL p, d, t, k;
} e[200002];
struct B {
  LL et, d = 1e18;
} v[100001];
LL n, m, x, y;

void T(int x) {
  for (int i = v[x].et; i; i = e[i].p) {
    if (v[e[i].d].d > v[x].d + e[i].t + v[x].d % e[i].k) {
      v[e[i].d].d = v[x].d + e[i].t + v[x].d % e[i].k;
      T(e[i].d);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m >> x >> y;
  for (LL i = 1, a, b, c, d; i <= m; i++) {
    cin >> a >> b >> c >> d;
    e[i * 2] = {v[a].et, b, c, d}, v[a].et = i * 2;
    e[i * 2 + 1] = {v[b].et, a, c, d}, v[b].et = i * 2 + 1;
  }
  v[x].d = 0;
  T(x);
  cout << (v[y].d == 1e18 ? -1 : v[y].d) << endl;
  return 0;
}
/*
9 14 6 7
3 1 4 1
5 9 2 6
5 3 5 8
9 7 9 3
2 3 8 4
6 2 6 4
3 8 3 2
7 9 5 2
8 4 1 9
7 1 6 9
3 9 9 3
7 5 1 5
8 2 9 7
4 9 4 4
*/
