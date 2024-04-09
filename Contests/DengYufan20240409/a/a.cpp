#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5e5 + 1, kMod = 1e9 + 7;
struct V {
  int i;
  vector<int> e;
} v[kMaxN];
int n, q[kMaxN];
pair<int, int> a[kMaxN];
class Seg1 {
  struct V {
    int w, t;
  } v[kMaxN * 8];

  void Tag(int p, int t) { v[p].w = v[p].t = t; }

  void Pushdown(int p) {
    if (v[p].t) {
      Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t);
      v[p].t = 0;
    }
  }

  int Ask(int p, int l, int r, int x) {
    if (l == r) {
      return v[p].w;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      return Ask(p << 1, l, mid, x);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, x);
    }
  }

  void Change(int p, int l, int r, int _l, int _r, int x) {
    if (l >= _l && r <= _r) {
      return Tag(p, x);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Change(p << 1, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      Change(p << 1 | 1, mid + 1, r, _l, _r, x);
    }
  }

 public:
  int Ask(int x) { return Ask(1, 1, n * 2, x); }
  void Change(int l, int r, int x) { Change(1, 1, n * 2, l, r, x); }
} seg1;
class Seg2 {
  struct V {
    int s, l, r;
  } v[kMaxN * 64];
  int m, s[kMaxN];

  void Copy(int &p) {
    v[++m] = v[p], p = m;
  }

  void Enable(int &p, int l, int r, int x) {
    Copy(p);
    if (l == r) {
      return v[p].s = 1, void();
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Enable(v[p].l, l, mid, x);
    } else {
      Enable(v[p].r, mid + 1, r, x);
    }
    v[p].s = v[v[p].l].s + v[v[p].r].s;
  }

  void Merge(int &p, int &q, int l, int r) {
    if (!q || v[p].s == r - l + 1) {
      return q = p, void();
    } else if (!p || v[q].s == r - l + 1) {
      return void();
    }
    Copy(q);
    if (l == r) {
      return v[q].s |= v[p].s, void();
    }
    int mid = l + r >> 1;
    Merge(v[p].l, v[q].l, l, mid);
    Merge(v[p].r, v[q].r, mid + 1, r);
    v[q].s = v[v[q].l].s + v[v[q].r].s;
  }

 public:
  void Enable(int o, int x) { Enable(s[o], 1, n, x); }
  int Count(int o) { return v[s[o]].s; }
  void Merge(int o1, int o2) { Merge(s[o1], s[o2], 1, n); }
} seg2;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void CalcG() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  for (int i = 1; i <= n; i++) {
    int x = seg1.Ask(a[i].first);
    int y = seg1.Ask(a[i].second);
    if (x) {
      v[i].e.push_back(x), v[x].i++;
    }
    if (y && x != y) {
      v[i].e.push_back(y), v[y].i++;
    }
    seg1.Change(a[i].first, a[i].second, i);
  }
}

void Sort() {
  int t = 0;
  for (int i = 1; i <= n; i++) {
    if (!v[i].i) {
      q[++t] = i;
    }
  }
  for (int h = 1; h <= t; h++) {
    for (int i : v[q[h]].e) {
      if (!--v[i].i) {
        q[++t] = i;
      }
    }
  }
}

void CalcAns() {
  LL ans = 0;
  for (int o = 1, i; o <= n; o++) {
    i = q[o], seg2.Enable(i, i);
    ans = (ans + Pow(seg2.Count(i))) % kMod;
    for (int j : v[i].e) {
      seg2.Merge(i, j);
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  CalcG(), Sort(), CalcAns();
  return 0;
}
