#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int x, c;
  bool operator<(const A &a) const {
    return c > a.c;
  }
} v[100001];

int l, n, f, b;
LL ans;

int main() {
  freopen("reststops.in", "r", stdin);
  freopen("reststops.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> l >> n >> f >> b;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].c;
  }
  sort(v + 1, v + 1 + n);
  for (int i = 1; i <= n; i++) {
    if (v[i].x > v[i - 1].x) {
      ans += (v[i].x - v[i - 1].x) * (f - b) * v[i].c;
    }
  }
  return 0;
}
