#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int n, m, k, opt[N], a[N], def[N];
bool vis[N];
vector<int> G[N], RG[N], use[N];
void dfs_out(int s, int x);
void dfs(int b, int x) {
  if (vis[b])
    return;
  vis[b] = true;
  dfs_out(b, x);
}
void dfs_in(int s, int x) {
  for (auto p : RG[s])
    dfs(p, x);
}
void dfs_out(int s, int x) {
  int d = 0;
  if (opt[s] == 1)
    d = a[s];
  if (d != 0 && d != x) {
    G[d].push_back(x);
    G[x].push_back(d);
  }
  if (x != d)
    dfs_in(s, x);
}

int nxt[N << 1], pre[N << 1];
int w[N], q[N], dy[N];
void push(int x) {
  pre[nxt[x] = nxt[N + w[x]]] = x;
  nxt[pre[x] = N + w[x]] = x;
}
void del(int x) {
  pre[nxt[x]] = pre[x];
  nxt[pre[x]] = nxt[x];
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &opt[i], &a[i]);
      if (opt[i] == 1)
        def[a[i]] = i;
      else
        use[a[i]].push_back(i);
    }
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      RG[y].push_back(x);
    }
    for (int i = 1; i <= k; i++) {
      for (int j = 1; j <= n; j++)
        vis[j] = false;
      for (auto s : use[i])
        dfs_in(s, i);
    }

    for (int i = 1; i <= k; i++)
      push(i);
    int now = 0, ans = 0;
    for (int j = k; j; j--, now++) {
      while (!nxt[N + now])
        now--;
      int x = nxt[N + now];
      del(x);
      q[j] = x;
      dy[x] = j;
      int sum = 1;
      for (auto y : G[x])
        if (!dy[y]) {
          del(y);
          ++w[y];
          push(y);
        } else
          ++sum;
      if (sum > ans)
        ans = sum;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= k; i++) {
      G[i].clear();
      use[i].clear();
      def[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      RG[i].clear();
    }
    for (int i = 0; i < N << 1; i++) {
      nxt[i] = pre[i] = 0;
    }
    for (int i = 0; i < N; i++)
      w[i] = q[i] = dy[i] = 0;
  }
  return 0;
}
