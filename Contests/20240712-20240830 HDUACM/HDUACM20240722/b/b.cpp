// by lsl
#include <bits/stdc++.h>
#define MK(x, y) make_pair((x), (y))
#define PI pair<node, int>
#define PII pair<int, node>
#define x first
#define y second
using namespace std;
const int N = 31, M = (1 << 10) + 5;
int dis[M][N][N];
bool vis[M][N][N];
struct node {
  int s, x, y;
};
bool operator<(node x, node y) { return x.s < y.s; }
struct mobs {
  int x, y, a, b, c;
} b[11];
int ds(int x, int y, int x2, int y2) { return abs(x - x2) + abs(y - y2); }
node CON(int s, int x, int y) { return (node){s, x, y}; }
vector<PI> G[M][N][N];
int v[N][N];
int n, m, k, d, sx, sy, ans;
int sum[M];
void dij() {
  priority_queue<PII, vector<PII>, greater<PII>> q;
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  dis[0][sx][sy] = 0;
  q.push(MK(0, CON(0, sx, sy)));
  while (!q.empty()) {
    PII x = q.top();
    q.pop();
    node u = x.y;
    if (vis[u.s][u.x][u.y]) continue;
    vis[u.s][u.x][u.y] = 1;
    for (auto vv : G[u.s][u.x][u.y]) {
      int w = dis[u.s][u.x][u.y] + vv.y;
      node v = vv.x;
      if (dis[v.s][v.x][v.y] > w) {
        dis[v.s][v.x][v.y] = w;
        q.push(MK(dis[v.s][v.x][v.y], v));
      }
    }
  }
  for (int i = 1; i < (1 << k); i++)
    for (int x = 1; x <= n; x++)
      for (int y = 1; y <= m; y++)
        ans = max(ans, sum[i] - dis[i][x][y]);
}
bool in(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= m; }
void build(int i, int x, int y, int op) {
  int vx = x, vy = y;
  int cst = 0, s = 0;
  while (abs(vx - x) + abs(vy - y) <= d && in(vx, vy)) {
    s |= v[vx][vy];
    if ((v[vx][vy] & i) == v[vx][vy]) {
      cst = 0;
      for (int j = 1; j <= k; j++)
        if (!((i | s) >> (j - 1) & 1)) cst += b[j].b * (ds(b[j].x, b[j].y, vx, vy) <= b[j].c);
      G[i][x][y].push_back(MK(CON(i | s, vx, vy), cst));
    }
    s |= v[vx][vy];
    vx += (op == 0 ? 1 : (op == 1 ? -1 : 0)), vy += (op == 2 ? 1 : (op == 3 ? -1 : 0));
  }
}
int T;
void work() {
  cin >> n >> m >> k >> d;
  ans = 0;
  for (int i = 0; i < (1 << k); i++) {
    sum[i] = 0;
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= m; k++)
        G[i][j][k].clear();
  }
  for (int j = 1; j <= n; j++)
    for (int k = 1; k <= m; k++)
      v[j][k] = 0;
  for (int i = 1; i <= k; i++) cin >> b[i].x >> b[i].y >> b[i].a >> b[i].b >> b[i].c, v[b[i].x][b[i].y] |= (1 << i - 1);
  cin >> sx >> sy;
  for (int i = 1; i < (1 << k); i++)
    for (int j = 1; j <= k; j++)
      if (i >> (j - 1) & 1) sum[i] += b[j].a;
  for (int i = 0; i < (1 << k) - 1; i++) {
    for (int x = 1; x <= n; x++)
      for (int y = 1; y <= m; y++) {
        if ((v[x][y] & i) != v[x][y]) continue;
        for (int k = 0; k < 4; k++) build(i, x, y, k);
      }
  }
  dij();
  cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) work();
  return 0;
}
