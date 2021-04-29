#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int a, b;
} v[200001];

int t, n, d[200001], ans[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1, tmp1, tmp2; i <= n; i++) {
      cin >> tmp1 >> tmp2;
      v[i].a = max(tmp1, tmp2), v[i].b = max(tmp1, tmp2), d[i] = i;
    }
    sort(d + 1, d + n + 1, [](int i, int j) {
      return v[i].b < v[j].b || v[i].b == v[j].b && v[i].a > v[j].a;
    });
    for (int i = 1, x = 1, q = d[1]; i <= n; i++) {
      ans[q] = v[q].a > v[d[x]].a ? d[x] : -1;
      x = ans[q] == -1 ? i : x;
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
  }
  return 0;
}
