#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int p, d;
} e[400002];

struct B {
  int et;
} v[200001];

int n, m, a, b, s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> a >> b;
  e[++m * 2] = {v[a].et, b}, v[a].et = m * 2;
  e[m * 2 + 1] = {v[b].et, a}, v[b].et = m * 2 + 1;
  for (int i = 2, x, y; i <= n; i++) {
    cin >> x >> y;
    if (x == 1 && y == a || x == a && y == 1) {
      s = a;
    } else if (x == 1 && y == b || x == b && y == 1) {
      s = b;
    }
    e[++m * 2] = {v[x].et, y}, v[x].et = m * 2;
    e[m * 2 + 1] = {v[y].et, x}, v[y].et = m * 2 + 1;
  }
  for (int f = 1, x = s; n; n--) {
    cout << x << " ";
    if (e[v[x].et].d != f) {
      f = x, x = e[v[x].et].d;
    } else {
      f = x, x = e[e[v[x].et].p].d;
    }
  }
  return 0;
}
