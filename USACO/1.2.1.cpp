/*
ID: dengyuf1
TASK: milk2
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int l, r;
  bool operator<(const A &a) const {
    return l < a.l;
  }
} v[5001];

int n, s, t, a1, a2;

int main() {
  freopen("milk2.in", "r", stdin);
  freopen("milk2.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].l >> v[i].r;
  }
  sort(v + 1, v + n + 1);
  s = v[1].l, t = v[1].r;
  for (int i = 2; i <= n; i++) {
    if (v[i].l <= t) {
      t = max(t, v[i].r);
    } else {
      a1 = max(a1, t - s), a2 = max(a2, v[i].l - t);
      s = v[i].l, t = v[i].r;
    }
  }
  a1 = max(a1, t - s);
  cout << a1 << " " << a2 << endl;
  return 0;
}
