#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int p, d;
} e[400002];

struct B {
  int et;
} v[200001];

int n, m;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    e[++m * 2] = {v[x].et, y}, v[x].et = m * 2;
    e[m * 2 + 1] = {v[y].et, x}, v[y].et = m * 2 + 1;
  }
  for(int f = 1, x = e[v[1].et].d; n; n--) {
    cout << x << " ";
    if(e[v[x].et].d != f) {
      f = x, x = e[v[x].et].d;
    } else {
      f = x, x = e[e[v[x].et].p].d;
    }
  }
  return 0;
}
