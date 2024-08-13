// by lsl
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
vector<int> f[N];
int n, m, ct, TE;
int cs[N];
bool ok[N];
int find(int i, int x) { return f[i][x] == x ? x : f[i][x] = find(i, f[i][x]); }
void work() {
  for (int i = 1; i <= ct; i++) f[i].clear(), f[i].shrink_to_fit(), ok[i] = 0;
  cin >> n >> m;
  ct = m / (n - 1);
  for (int i = 1; i <= ct; i++) {
    f[i].resize(n + 1);
    for (int j = 1; j <= n; j++) f[i][j] = j;
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    int l = 1, r = ct, ans = ct + 1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (find(mid, x) == find(mid, y))
        l = mid + 1;
      else
        ans = mid, r = mid - 1;
    }
    cs[i] = ans;
    if (ans <= ct) {
      int px = find(ans, x), py = find(ans, y);
      f[ans][py] = px;
    }
  }
  for (int i = 1; i <= ct; i++) {
    int jl = find(i, 1);
    ok[i] = 1;
    for (int j = 2; j <= n; j++) {
      if (find(i, j) != jl) {
        ok[i] = 0;
        break;
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (cs[i] > ct || !ok[cs[i]])
      cout << -1 << ' ';
    else
      cout << cs[i] << ' ';
  }
  cout << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> TE;
  while (TE--) work();
  return 0;
}
