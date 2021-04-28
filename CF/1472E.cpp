#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int a, b, n;
  bool operator<(const A &x) const {
    return a < x.a;
  }
} v[200001];

int t, n, mn, num, ans[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1, tmp1, tmp2; i <= n; i++) {
      cin >> tmp1 >> tmp2;
      v[i].a = max(tmp1, tmp2), v[i].b = max(tmp1, tmp2), v[i].n = i;
    }
    sort(v + 1, v + n + 1);
    
  }
  return 0;
}
