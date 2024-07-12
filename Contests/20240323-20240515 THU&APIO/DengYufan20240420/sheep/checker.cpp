#include <bits/stdc++.h>

#include "testlib.h"
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
int n, m, C = 200000;
pii a[M], b[M];
int pos[N][N];
int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  n = inf.readInt(50, 50), m = inf.readInt(50, 1600);
  for (re int i = 1; i <= m; ++i)
    a[i].fi = inf.readInt(1, n),
    a[i].se = inf.readInt(1, n);
  for (re int i = 1; i <= m; ++i)
    b[i].fi = inf.readInt(1, n),
    b[i].se = inf.readInt(1, n);
  for (re int i = 1; i <= m; ++i)
    pos[a[i].fi][a[i].se] = i;
  int K = ouf.readInt();
  if (K < 0) quitf(_wa, "your K is negative, what are you doing???");
  if (K > 1e6) quitf(_wa, "your K is too large!!!");
  for (re int i = 1; i <= K; ++i) {
    int x, y, nx, ny;
    x = ouf.readInt(1, n);
    y = ouf.readInt(1, n);
    nx = ouf.readInt(1, n);
    ny = ouf.readInt(1, n);
    if (!pos[x][y]) quitf(_wa, "there is no cow, %d.", i);
    if (pos[nx][ny]) quitf(_wa, "cow %d and cow %d had a fight, %d.", pos[x][y], pos[nx][ny], i);
    if (abs(x - nx) + abs(y - ny) != 1) quitf(_wa, "you made a illegal move, %d.", i);
    a[pos[x][y]] = pii{nx, ny}, swap(pos[x][y], pos[nx][ny]);
  }
  for (re int i = 1; i <= m; ++i)
    if (a[i] != b[i]) quitf(_wa, "cow %d didn't come home.", i);
  if (K <= C) quitf(_ok, "thank you very much!!!");
  double w = 5.0 * C / K;
  quitp(floor(w), "thank you.");
}
// dat.exe && sheep.exe && checker sheep.in sheep.out sheep.out
