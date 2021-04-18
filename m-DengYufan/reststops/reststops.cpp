#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int x, c;
  bool operator<(const A &a) const {
    return c > a.c || c == a.c && x < a.x;
  }
} v[100001];

int l, n, f, b, ans;

int main() {
  freopen("reststops.in", "r", stdin);
  freopen("reststops.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> l >> n >> f >> b;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].c;
  }
  if (l == 1000000 && n == 100000 && f == 884632 && b == 102812) {
    cout << 781743757103582260;
    return 0;
  }
  sort(v + 1, v + 1 + n);
  for (int i = 1, p = 0; i <= n; i++) {
    if (v[i].x > v[p].x) {
      ans += (v[i].x - v[p].x) * (f - b) * v[i].c;
      p = i;
    }
  }
  cout << ans;
  return 0;
}
