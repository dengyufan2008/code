#include <bits/stdc++.h>
#define il inline
#define re register
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
#define N 55
#define M 1705
int n, m;
pii a[M], b[M];
mt19937 rnd(time(0));
bool vis[N][N];
il int rand(int l, int r) {
  return rnd() % (r - l + 1) + l;
}
il void born(pii *v) {
  memset(vis, 0, sizeof(vis));
  for (re int i = 1, x, y; i <= m; ++i) {
    do {
      x = rand(1, n), y = rand(1, n);
    } while (vis[x][y]);
    vis[x][y] = 1, v[i] = pii{x, y};
  }
}
int main() {
  freopen("data.in", "r", stdin);
  freopen("sheep.in", "w", stdout);
  cin >> n >> m;
  assert(m <= n * n);
  born(a), born(b);
  cout << n << " " << m << "\n";
  for (re int i = 1; i <= m; ++i) cout << a[i].fi << " " << a[i].se << "\n";
  for (re int i = 1; i <= m; ++i) cout << b[i].fi << " " << b[i].se << "\n";
}
