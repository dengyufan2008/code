// by wls
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m;
struct node {
  bool tp;
  int l, r;
  bool operator<(const node &rhs) const { return l < rhs.l; }
} c[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) c[i].tp = 0, cin >> c[i].l >> c[i].r;
    for (int i = 1; i <= m; i++) c[i + n].tp = 1, cin >> c[i + n].l >> c[i + n].r;
    sort(c + 1, c + n + m + 1);
    int rp = -1;
    bool ans = 1;
    for (int i = 1; i <= n + m; i++) {
      if (i != n + m && c[i + 1].l < c[i].r) {
        ans = 0;
        break;
      }
      if (c[i].tp == 0 && c[i].r > rp) {
        ans = 0;
        break;
      }
      if (c[i].tp == 1) {
        rp = c[i].r + (c[i].r - c[i].l) * 2;
      }
    }
    cout << (ans ? "Yes\n" : "No\n");
  }
  return 0;
}
