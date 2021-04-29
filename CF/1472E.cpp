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
    for (int i = 1; i <= n; i++) {
      cin >> v[i].a >> v[i].b;
      d[i] = i;
      if (v[i].a < v[i].b) {
        swap(v[i].a, v[i].b);
      }
    }
    sort(d + 1, d + n + 1, [](int i, int j) {
      return v[i].b < v[j].b || v[i].b == v[j].b && v[i].a > v[j].a;
    });
    for (int i = 1, x = 1, q = d[1]; i <= n; q = d[++i]) {
      ans[q] = v[q].a > v[d[x]].a ? d[x] : -1;
      if (ans[q] == -1) {
        x = i;
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
    cout << endl;
  }
  return 0;
}
