#include <bits/stdc++.h>
using namespace std;
namespace QYB {
  int n, m, q, seed, cnt, gx, gy, vis[1805][1805]; char s[1805][1805];
  mt19937_64 rnd;
  int get(int l, int r) {
    uniform_int_distribution<int> distribution(l, r);
    return distribution(rnd);
  } bool dfs(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m || vis[x][y] == cnt) return false;
    if (x == gx && y == gy) return true; vis[x][y] = cnt; bool res = false;
    if (s[x][y] != 'U') res |= dfs(x - 1, y);
    if (s[x][y] != 'D') res |= dfs(x + 1, y);
    if (s[x][y] != 'L') res |= dfs(x, y - 1);
    if (s[x][y] != 'R') res |= dfs(x, y + 1);
    return res;
  } int main() {
    freopen("retribution.in", "r", stdin);
    freopen("retribution.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &q, &seed);
    rnd = mt19937_64(seed);
    for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    while (q--) {
      int sx, sy;
      sx = get(1, n); sy = get(1, m);
      gx = get(1, n); gy = get(1, m);
      ++cnt; printf("%d", int(dfs(sx, sy)));
    } return 0;
  }
} int main() { return QYB::main(); }