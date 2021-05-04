/*
ID: dengyuf1
TASK: milk
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int a, p;
  bool operator<(const A &x) const {
    return p < x.p;
  }
} v[5001];

LL n, m, ans, num;

int main() {
  freopen("milk.in", "r", stdin);
  freopen("milk.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (LL i = 1; i <= m; i++) {
    cin >> v[i].p >> v[i].a;
  }
  sort(v + 1, v + m + 1);
  for (LL i = 1; i <= m; i++) {
    if (num + v[i].a > n) {
      ans += (n - num) * v[i].p;
      break;
    } else {
      num += v[i].a;
      ans += v[i].a * v[i].p;
    }
  }
  cout << ans << endl;
  return 0;
}
