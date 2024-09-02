#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;
typedef unsigned int U;
typedef pair<U, U> P;
const int N = 9, K = 6, M = 13055, CNT = 305, inf = ~0U >> 1;
int a[CNT], b[CNT], f[CNT][M], perm[N], deg[N], d[N][N];
bool g[N][N];
U minS;
U two[N], w[N];
P ident[N];
inline void umin(int& a, int b) { a > b ? (a = b) : 0; }
inline void umax(int& a, int b) { a < b ? (a = b) : 0; }
struct Info {
  int n, m, tot, id[N][N], apsp[K][K][M];
  map<U, int> T;
  U mask[M];
  vector<int> adj[M];
  void init(int _n) {
    int i, j, k, o, A, B;
    n = _n;
    for (i = 0; i < n; i++)
      for (j = 0; j < i; j++) id[i][j] = id[j][i] = m++;
    dfs(0);
    for (i = 1; i <= tot; i++) {
      sort(adj[i].begin(), adj[i].end());
      adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }
    int d[N][N];
    for (A = 1; A < K; A++)
      for (B = 1; B < K; B++)
        for (o = 1; o <= tot; o++) {
          U S = mask[o];
          for (i = 0; i < n; i++)
            for (j = 0; j < i; j++) d[i][j] = d[j][i] = (S >> id[i][j] & 1) ? B : A;
          for (i = 0; i < n; i++) d[i][i] = 0;
          for (k = 0; k < n; k++)
            for (i = 0; i < n; i++)
              for (j = 0; j < n; j++) umin(d[i][j], d[i][k] + d[k][j]);
          int sum = 0;
          for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) sum += d[i][j];
          apsp[A][B][o] = sum;
        }
  }
  void reorder(int x, int vis) {
    if (x == n) {
      U now = 0;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
          if (g[perm[i]][perm[j]]) now |= 1U << id[i][j];
      if (minS > now) minS = now;
      return;
    }
    P mindeg(~0U >> 1, 0);
    for (int i = 0; i < n; i++)
      if (!(vis >> i & 1) && mindeg > ident[i]) mindeg = ident[i];
    for (int i = 0; i < n; i++)
      if (!(vis >> i & 1) && mindeg == ident[i]) {
        perm[x] = i;
        reorder(x + 1, vis | (1 << i));
      }
  }
  U adjust(U S) {
    int i, j;
    for (i = 0; i < n; i++) deg[i] = 0;
    for (i = 0; i < n; i++)
      for (j = 0; j < i; j++) {
        g[i][j] = g[j][i] = S >> id[i][j] & 1;
        if (g[i][j]) deg[i]++, deg[j]++;
      }
    for (i = 0; i < n; i++) {
      two[i] = 0;
      for (j = 0; j < n; j++)
        if (g[i][j]) two[i] += w[deg[j]];
    }
    for (i = 0; i < n; i++) ident[i] = P(deg[i], two[i]);
    minS = ~0U;
    int vis = 0, cnt = 0;
    for (i = 0; i < n; i++)
      if (deg[i] == 0) {
        vis |= 1 << i;
        perm[cnt++] = i;
      }
    for (i = 0; i < n; i++)
      if (deg[i] == n) {
        vis |= 1 << i;
        perm[cnt++] = i;
      }
    reorder(cnt, vis);
    return minS;
  }
  int dfs(U S) {
    S = adjust(S);
    int& x = T[S];
    if (x) return x;
    x = ++tot;
    mask[tot] = S;
    for (int i = 0; i < m; i++)
      if (!(S >> i & 1)) {
        int y = dfs(S ^ (1U << i));
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
      }
    return x;
  }
  void solve(int cnt) {
    for (int j = 1; j <= tot; j++) f[cnt + 1][j] = 0;
    for (int i = cnt; i; i--) {
      int A = a[i], B = b[i];
      for (int j = 1; j <= tot; j++) {
        int cur = -inf;
        for (const auto& k : adj[j]) umax(cur, apsp[A][B][k] - f[i + 1][k]);
        f[i][j] = cur;
      }
    }
    printf("%d\n", f[1][1]);
  }
} info[N];
int main() {
  freopen("b.in", "r", stdin);
  freopen("b.ans", "w", stdout);
  for (int i = 0; i < N; i++) w[i] = (rand() << 15) ^ rand();
  for (int i = 2; i <= 8; i++) info[i].init(i);
  int Case;
  scanf("%d", &Case);
  while (Case--) {
    int n, cnt;
    scanf("%d%d", &n, &cnt);
    for (int i = 1; i <= cnt; i++) scanf("%d%d", &a[i], &b[i]);
    info[n].solve(cnt);
  }
}
