// by lsl
#include <bits/stdc++.h>
#define PI pair<int, int>
#define MK(x, y) make_pair((x), (y))
#define CON(x, y, z) \
  (tup) { (x), (y), (z) }
using namespace std;
const int N = 1e5 + 10, inf = 1e9;
int h[N], nex[N << 1], to[N << 1], tot;
struct node {
  PI c[2];
  void init() { c[0] = c[1] = MK(-inf, -inf); }
  void insert(PI x) {
    if (x > c[0])
      c[1] = c[0], c[0] = x;
    else if (x > c[1])
      c[1] = x;
  }
} dp[N];
int ans[N];
int cir[N], val[N], cnt, col[N], gx[N];
struct tup {
  int x, y, z;
};
tup operator+(tup a, tup b) { return CON(max(a.x, b.x), max(a.y, b.y), max({a.z, b.z, a.x + b.y})); }
struct segtree {
#define ls (k << 1)
#define rs (k << 1 | 1)
#define mid (l + r >> 1)
  int mx[2][N << 2], lz[2][N << 2], gx[N << 2];
  void pushup(int k) {
    mx[0][k] = max(mx[0][ls], mx[0][rs]);
    mx[1][k] = max(mx[1][ls], mx[1][rs]);
    gx[k] = max({gx[ls], gx[rs], mx[0][ls] + mx[1][rs]});
  }
  void ch(int k, int z, int o) { mx[o][k] += z, lz[o][k] += z, gx[k] += z; }
  void pd(int k, int o) {
    if (!lz[o][k]) return;
    ch(ls, lz[o][k], o), ch(rs, lz[o][k], o);
    lz[o][k] = 0;
  }
  void pushdown(int k) {
    pd(k, 0);
    pd(k, 1);
  }
  void build(int k, int l, int r, int o) {
    lz[o][k] = 0;
    gx[k] = 0;
    if (l == r) {
      mx[o][k] = dp[cir[l]].c[0].first + (!o ? l - 1 : (cnt + 1 - l) % cnt);
      gx[k] = -inf;
      return;
    }
    build(ls, l, mid, o), build(rs, mid + 1, r, o);
    pushup(k);
  }
  void upd(int k, int l, int r, int x, int y, int z, int o) {
    if (x > y) return;
    if (x <= l && r <= y) {
      ch(k, z, o);
      return;
    }
    pushdown(k);
    if (mid >= x) upd(ls, l, mid, x, y, z, o);
    if (y > mid) upd(rs, mid + 1, r, x, y, z, o);
    pushup(k);
  }
  int qry(int k, int l, int r, int x, int y, int o) {
    if (x > y) return -inf;
    if (x <= l && r <= y) return mx[o][k];
    pushdown(k);
    int ans = 0;
    if (mid >= x) ans = max(ans, qry(ls, l, mid, x, y, o));
    if (y > mid) ans = max(ans, qry(rs, mid + 1, r, x, y, o));
    return ans;
  }
  tup qpy(int k, int l, int r, int x, int y) {
    if (x > y) return CON(-inf, -inf, -inf);
    if (x <= l && r <= y) return CON(mx[0][k], mx[1][k], gx[k]);
    pushdown(k);
    tup ans = CON(-inf, -inf, -inf);
    if (mid >= x) ans = ans + qpy(ls, l, mid, x, y);
    if (y > mid) ans = ans + qpy(rs, mid + 1, r, x, y);
    return ans;
  }
} T;
void add(int x, int y) { to[++tot] = y, nex[tot] = h[x], h[x] = tot; }
int st[N], top, vis[N], dep[N];
int n;
void fcir(int u, int fa) {
  dep[u] = dep[fa] + 1;
  vis[u] = 1;
  st[++top] = u;
  for (int i = h[u]; i; i = nex[i]) {
    int v = to[i];
    if (v == fa) continue;
    if (!vis[v])
      fcir(v, u);
    else if (dep[v] < dep[u]) {
      while (st[top] != v && top) cir[++cnt] = st[top--];
      cir[++cnt] = v;
    }
  }
  top--;
}
void dfs(int u, int fa) {
  dp[u].init();
  for (int i = h[u]; i; i = nex[i]) {
    int v = to[i];
    if (vis[v] || v == fa) continue;
    dep[v] = dep[u] + 1;
    dfs(v, u);
    dp[u].insert(MK(dp[v].c[0].first + 1, v));
  }
  dp[u].insert(MK(0, u));
}
void calc(int u, int fa, int sum, int cl) {
  col[u] = cl;
  //  cout<<u<<' '<<dp[u].c[0].first<<' '<<dp[u].c[0].second<<' '<<sum<<'\n';
  ans[u] = max(dp[u].c[1].first, sum) + dp[u].c[0].first;
  for (int i = h[u]; i; i = nex[i]) {
    int v = to[i];
    if (vis[v] || v == fa) continue;
    if (v == dp[u].c[0].second)
      calc(v, u, max(sum, dp[u].c[1].first) + 1, cl);
    else
      calc(v, u, max(sum, dp[u].c[0].first) + 1, cl);
  }
}
int Te;
void work() {
  cin >> n;
  for (int i = 1; i <= n; i++) h[i] = 0;
  tot = cnt = top = 0;
  for (int i = 1; i <= n; i++) vis[i] = cir[i] = st[i] = dep[i] = ans[i] = gx[i] = val[i] = col[i] = 0;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    add(x, y), add(y, x);
  }
  fcir(1, 0);
  //  cout<<cnt<<endl;
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= cnt; i++) vis[cir[i]] = 1;  //,cout<<cir[i]<<endl;
  for (int i = 1; i <= cnt; i++) {
    dep[cir[i]] = 0;
    dfs(cir[i], 0);
    calc(cir[i], 0, 0, cir[i]);
  }
  T.build(1, 1, cnt, 0), T.build(1, 1, cnt, 1);
  for (int i = 1; i <= cnt; i++) {
    val[cir[i]] = max({T.qry(1, 1, cnt, 1, i - 1, 0), T.qry(1, 1, cnt, i + 1, cnt, 0), T.qry(1, 1, cnt, 1, i - 1, 1), T.qry(1, 1, cnt, i + 1, cnt, 1)});
    gx[cir[i]] = max({T.qpy(1, 1, cnt, 1, i - 1).z, T.qpy(1, 1, cnt, i + 1, cnt).z, T.qry(1, 1, cnt, 1, i - 1, 1) + T.qry(1, 1, cnt, i + 1, cnt, 0)});
    //    cout<<cir[i]<<' '<<gx[cir[i]]<<' '<<T.qpy(1,1,cnt,1,i-1).z<<' '<<T.qpy(1,1,cnt,i+1,cnt).z<<endl;
    //    cout<<cir[i]<<' '<<val[cir[i]]<<endl;
    T.upd(1, 1, cnt, 1, cnt, -1, 0);
    T.upd(1, 1, cnt, i, i, cnt, 0);
    T.upd(1, 1, cnt, 1, cnt, 1, 1);
    T.upd(1, 1, cnt, i + 1, i + 1, -cnt, 1);
  }
  //  for(int i=1;i<=n;i++)cout<<ans[i]<<' ';cout<<'\n';
  for (int i = 1; i <= n; i++) cout << max({ans[i], dep[i] + dp[i].c[0].first + val[col[i]], gx[i]}) << ' ';
  cout << '\n';
}
signed main() {
  //  freopen("data.in","r",stdin);
  //  freopen("1.out","w",stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> Te;
  while (Te--) work();
  return 0;
}
