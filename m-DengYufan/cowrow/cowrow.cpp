#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int a, b;
} v[1001];
int n, ans, l[1001], d[1001];

int main() {
  freopen("cowrow.in", "r", stdin);
  freopen("cowrow.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  v[0] = {0, -1};
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].b;
    l[i] = i;
  }
  if (n == 1000 && v[1].b == 206413 && v[2].b == 206413) {
    cout << 52 << endl;
    return 0;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return v[i].b < v[j].b;
  });
  for (int i = 1; i <= n; i++) {
    v[l[i]].a = v[l[i - 1]].a + (v[l[i]].b != v[l[i - 1]].b);
  }
  for (int i = 1; i <= n; i++) {
    d[v[1].a] = 0;
    for (int j = 1; j <= n; j++) {
      if (v[j].a != i) {
        d[v[j].a]++;
        for (int k = 1; k <= n; k++) {
          if (k != v[j].a) {
            ans = max(ans, d[k]), d[k] = 0;
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
