#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
const int SZ = 20;
char s[MAXN];
struct SAM {
 public:
  vector<int> e[MAXN];
  vector<pair<int, pair<int, int> > > occ[MAXN];
  vector<int> lp[MAXN], rp[MAXN];
  vector<long long> sl[MAXN], sr[MAXN], sx[MAXN];
  int ch[MAXN][2];
  int sum[MAXN], Max[MAXN], fa[MAXN], pos[MAXN], up[MAXN][SZ];
  int posmin[MAXN];
  int n_last, sz;

 public:
  void init(int n) {
    n_last = sz = 1;
    for (int i = 0; i <= n; i++) {
      sum[i] = Max[i] = fa[i] = ch[i][0] = ch[i][1] = pos[i] = 0;
      memset(up[i], 0, sizeof(up[i]));
      posmin[i] = 0x3f3f3f3f;
      e[i].clear();
      occ[i].clear();
    }
  }
  void p(int i, int c) {
    int p = n_last, np = ++sz;
    n_last = sz;
    sum[np]++;
    pos[i] = np;
    Max[np] = Max[p] + 1;
    posmin[np] = min(posmin[np], i);
    for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
    if (!p) {
      fa[np] = 1;
      return;
    }
    int q = ch[p][c];
    if (Max[q] == Max[p] + 1)
      fa[np] = q;
    else {
      int nq = ++sz;
      Max[nq] = Max[p] + 1;
      fa[nq] = fa[q];
      fa[np] = fa[q] = nq;
      memcpy(ch[nq], ch[q], sizeof(ch[q]));
      for (; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
    }
  }
  void build_tree() {
    for (int i = 2; i <= sz; i++) e[fa[i]].push_back(i);
  }
  void dfs(int now, int father) {
    up[now][0] = father;
    for (int i = 1; i < SZ; i++) up[now][i] = up[up[now][i - 1]][i - 1];
    for (int i = 0; i < e[now].size(); i++) {
      int u = e[now][i];
      dfs(u, now);
      sum[now] += sum[u];
      posmin[now] = min(posmin[now], posmin[u]);
    }
    if (Max[now]) {
      occ[sum[now]].push_back(make_pair(posmin[now], make_pair(posmin[now] - Max[now] + 1, posmin[now] - Max[father])));
    }
  }
  void init() {
    for (int i = 1; i <= sz; i++) {
      sort(occ[i].begin(), occ[i].end());
      sl[i].resize(occ[i].size());
      sr[i].resize(occ[i].size());
      sx[i].resize(occ[i].size());
      lp[i].resize(occ[i].size());
      rp[i].resize(occ[i].size());
      for (int j = 0; j < occ[i].size(); j++) {
        sl[i][j] = (j ? sl[i][j - 1] : 0ll) + occ[i][j].second.first;
        sr[i][j] = (j ? sr[i][j - 1] : 0ll) + occ[i][j].second.second;
        sx[i][j] = (j ? sx[i][j - 1] : 0ll) + occ[i][j].second.second - occ[i][j].second.first + 1;
        lp[i][j] = occ[i][j].second.first;
        rp[i][j] = occ[i][j].second.second;
      }
    }
  }
  int getsum(int id, int len) {
    for (int i = SZ - 1; i >= 0; i--)
      if (up[id][i] != 0 && Max[up[id][i]] >= len) id = up[id][i];
    return sum[id];
  }
  int getmin(int id, int len) {
    for (int i = SZ - 1; i >= 0; i--)
      if (up[id][i] != 0 && Max[up[id][i]] >= len) id = up[id][i];
    return posmin[id];
  }
  long long solve1(int l, int r) {
    int s = getsum(pos[r], r - l + 1);
    int pos = lower_bound(occ[s].begin(), occ[s].end(), make_pair(r, make_pair(0, 0))) - occ[s].begin();
    int posl = upper_bound(rp[s].begin(), rp[s].end(), l) - rp[s].begin();
    int posr = upper_bound(lp[s].begin(), lp[s].end(), l) - lp[s].begin();
    long long ans = 0;
    if (pos < posl) {
      ans += sx[s][posl - 1] - (pos ? sx[s][pos - 1] : 0ll);
    }
    pos = max(pos, posl);
    if (pos < posr) {
      ans += 1ll * (posr - pos) * (l + 1) - (sl[s][posr - 1] - (pos ? sl[s][pos - 1] : 0ll));
    }
    return ans;
  }
  long long solve2(int l, int r) {
    int s = getsum(pos[r], r - l + 1);
    int pos = lower_bound(occ[s].begin(), occ[s].end(), make_pair(r + 1, make_pair(0, 0))) - occ[s].begin();
    int posl = lower_bound(rp[s].begin(), rp[s].end(), l) - rp[s].begin();
    int posr = lower_bound(lp[s].begin(), lp[s].end(), l) - lp[s].begin();
    long long ans = 0;
    if (posr < pos) {
      ans += sx[s][pos - 1] - (posr ? sx[s][posr - 1] : 0ll);
    }
    pos = min(pos, posr);
    if (posl < pos) {
      ans += (sr[s][pos - 1] - (posl ? sr[s][posl - 1] : 0ll)) - 1ll * (pos - posl) * (l - 1);
    }
    return ans;
  }
} sam;
int main() {
  freopen("f.in", "r", stdin);
  freopen("f.ans", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> s;
    int n = strlen(s);
    sam.init(n << 1);
    for (int i = 1; i <= n; i++) {
      sam.p(i, s[i - 1] - 'a');
    }
    sam.build_tree();
    sam.dfs(1, 0);
    sam.init();
    int q, op, l, r;
    cin >> q;
    long long lastans = 0;
    for (int i = 1; i <= q; i++) {
      cin >> op >> l >> r;
      l = (l + lastans % n - 1) % n + 1;
      r = (r + lastans % n - 1) % n + 1;
      int len = r - l;
      r = sam.getmin(sam.pos[r], r - l + 1);
      l = r - len;
      if (op == 1) {
        lastans = sam.solve1(l, r);
      } else
        lastans = sam.solve2(l, r);
      cout << lastans << endl;
    }
  }
  return 0;
}
