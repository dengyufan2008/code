#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1, kMaxL = 18, kInf = 1e9;
struct V {
  int d;  // 深度, 环为 0
  int r;  // 连通块代表元, 编号为 1
  int l;  // 环长
  int o;  // 环上编号, 1base, 大向小连边
  int f[kMaxL];
  vector<int> e, del;
  vector<pair<int, int>> ins;
} v[kMaxN];
int n, m, ans;

class Seg {
  struct D {
    int c, mx = -kInf, l, r;  // 深度 + 反向编号
  } d[kMaxN * (kMaxL + 1)];
  int k, s[kMaxN];

  void Add(int &p, int l, int r, int x, int w) {
    !p && (p = ++k);
    if (l == r) {
      d[p].c += w, d[p].mx = d[p].c ? l + d[p].c - 1 : -kInf;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Add(d[p].l, l, mid, x, w);
    } else {
      Add(d[p].r, mid + 1, r, x, w);
    }
    d[p].c = d[d[p].l].c + d[d[p].r].c;
    d[p].mx = max(d[d[p].l].mx + d[d[p].r].c, d[d[p].r].mx);
  }

  void Merge(int &p, int q, int l, int r) {
    if (!p || !q) {
      p |= q;
      return;
    } else if (l == r) {
      d[p].c += d[q].c, d[p].mx = d[p].c ? l + d[p].c - 1 : -kInf;
      return;
    }
    int mid = l + r >> 1;
    Merge(d[p].l, d[q].l, l, mid);
    Merge(d[p].r, d[q].r, mid + 1, r);
    d[p].c = d[d[p].l].c + d[d[p].r].c;
    d[p].mx = max(d[d[p].l].mx + d[d[p].r].c, d[d[p].r].mx);
  }

 public:
  void Add(int o, int x, int w) { Add(s[o], 1, n * 2, x, w); }
  void Merge(int o1, int o2) { Merge(s[o1], s[o2], 1, n * 2); }
  int Ask(int o) { return d[s[o]].mx; }
  void Clear() {
    for (int i = 1; i <= k; i++) {
      d[i] = d[0];
    }
    k = 0;
    for (int i = 1; i <= n; i++) {
      s[i] = 0;
    }
  }
} seg;

int F(int x, int d) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (d >> i & 1) {
      x = v[x].f[i];
    }
  }
  return x;
}

void Init() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].f[0];
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      v[j].f[i] = v[v[j].f[i - 1]].f[i - 1];
    }
  }
  for (int i = 1, j, c; i <= n; i++) {
    for (c = 0, j = i; !v[j].r; j = v[j].f[0]) {
      v[j].r = -1, c++;
    }
    if (v[j].r == -1) {
      for (int k = v[j].f[0]; k != j; k = v[k].f[0]) {
        v[k].r = j, v[j].l++;
      }
      v[j].r = j, v[j].o = 1, c -= ++v[j].l;
      for (int k = v[j].f[0], o = v[j].l; k != j; k = v[k].f[0]) {
        v[k].l = v[j].l, v[k].o = o--;
      }
    }
    for (int k = i, d = v[j].d + c; v[k].r == -1; k = v[k].f[0]) {
      v[k].d = d--, v[k].r = v[j].r;
    }
    v[i].d ? v[v[i].f[0]].e.push_back(i) : void();
  }
  cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    if (v[x].r != v[y].r || v[x].d < v[y].d) {
      cout << -1 << '\n', exit(0);
    }
    if (v[y].d) {
      if (F(x, v[x].d - v[y].d) != y) {
        cout << -1 << '\n', exit(0);
      }
      seg.Add(x, v[x].d, 1), v[y].del.push_back(v[x].d);
    } else {
      int z = F(x, v[x].d);
      v[x].d ? seg.Add(x, v[x].d, 1) : void();
      if (y != z) {
        v[z].ins.push_back({v[x].d, y});
      } else {
        v[z].del.push_back(v[x].d);
      }
    }
  }
}

void Calc(int x) {
  for (int i : v[x].e) {
    Calc(i), seg.Merge(x, i);
  }
  for (int i : v[x].del) {
    seg.Add(x, i, -1);
  }
  v[x].del.clear();
  ans = max(ans, seg.Ask(x) - v[x].d + 1);
}

void CalcTree() {
  for (int i = 1; i <= n; i++) {
    if (!v[i].d) {
      Calc(i);
    }
  }
}

void CalcRing() {
  seg.Clear();
  for (int i = 1, p = 0; i <= n; i++) {
    if (v[i].r == i) {
      for (int j = v[i].f[0]; j != i; j = v[j].f[0]) {
        for (auto k : v[j].ins) {
          if (v[j].o > v[k.second].o) {
            seg.Add(j, v[j].o + k.first, 1);
            v[k.second].del.push_back(v[j].o + k.first);
          } else {
            seg.Add(j, v[j].o + k.first, 1);
            v[0].del.push_back(v[j].o + k.first);
            seg.Add(v[i].f[0], v[j].o + k.first + v[i].l, 1);
            v[k.second].del.push_back(v[j].o + k.first + v[i].l);
          }
        }
      }
      for (auto j : v[i].ins) {
        seg.Add(i, 1 + j.first, 1);
        v[0].del.push_back(1 + j.first);
        seg.Add(v[i].f[0], 1 + j.first + v[i].l, 1);
        v[j.second].del.push_back(1 + j.first + v[i].l);
      }
      for (int j = v[i].f[0]; j != i; j = v[j].f[0]) {
        seg.Merge(j, p), p = j;
        for (int k : v[j].del) {
          seg.Add(j, k, -1);
        }
        ans = max(ans, seg.Ask(j) - v[j].o + 1);
      }
      seg.Merge(i, p), p = 0;
      for (int j : v[i].del) {
        seg.Add(i, j, -1);
      }
      ans = max(ans, seg.Ask(i));
      for (int j : v[0].del) {
        seg.Add(i, j, -1);
      }
      v[0].del.clear();
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), CalcTree(), CalcRing();
  cout << ans << '\n';
  return 0;
}
