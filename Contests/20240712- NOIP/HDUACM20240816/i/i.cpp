#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 1e5 + 1;
struct A {
  int o;
  LL w;
} f1, f2, g1, g2, g3;
struct O {
  int o1, o2, o3;
} o[kMaxN];
struct Q {
  int l, r, o;
} q[kMaxN];
int t, n, m, k, a[kMaxN], b[kMaxN];

int F(int o, int x) { return b[o] * x + a[o]; }
int Max(int o1, int o2, int x) { return F(o1, x) < F(o2, x) ? o2 : o1; }

class Seg {
  struct V {
    int l, r, o;
  } v[kMaxN * 20];
  int t, u, s[kMaxN];

  void Add(int &p, int l, int r, int o) {
    v[++u] = v[p], p = u;
    if (!v[p].o) {
      v[p].o = o;
      return;
    } else if (l == r) {
      v[p].o = Max(v[p].o, o, l);
      return;
    }
    int mid = l + r >> 1;
    if (F(v[p].o, mid) < F(o, mid)) {
      swap(v[p].o, o);
    }
    if (F(v[p].o, l) < F(o, l)) {
      Add(v[p].l, l, mid, o);
    }
    if (F(v[p].o, r) < F(o, r)) {
      Add(v[p].r, mid + 1, r, o);
    }
  }

  int Ask(int p, int l, int r, int x) {
    if (!v[p].o || l == r) {
      return v[p].o;
    }
    int mid = l + r >> 1, ans = v[p].o;
    if (mid >= x) {
      ans = Max(ans, Ask(v[p].l, l, mid, x), x);
    } else {
      ans = Max(ans, Ask(v[p].r, mid + 1, r, x), x);
    }
    return ans;
  }

 public:
  void Init() { t = u = 0; }
  void Add(int o) { t++, s[t] = s[t - 1], Add(s[t], 1, m, o); }
  int Ask(int t, int x) { return Ask(s[t], 1, m, x); }
} seg1, seg2;

void Divide(int ql, int qr, int l, int r) {
  if (ql > qr) {
    return;
  }
  int mid = l + r >> 1;
  seg1.Init(), seg2.Init();
  for (int i = mid; i >= l; i--) {
    seg1.Add(i);
  }
  for (int i = mid + 1; i <= r; i++) {
    seg2.Add(i);
  }
  int qmid1 = ql;
  for (int i = ql; i <= qr; i++) {
    if (q[i].r < mid) {
      swap(q[i], q[qmid1++]);
    }
  }
  int qmid2 = qmid1;
  for (int i = qmid1; i <= qr; i++) {
    if (q[i].l > mid + 1) {
      swap(q[i], q[qmid2++]);
    }
  }
  for (int i = qmid2; i <= qr; i++) {
    o[q[i].o].o3 = Max(o[q[i].o].o3, seg1.Ask(mid - q[i].l + 1, q[i].o), q[i].o);
    o[q[i].o].o3 = Max(o[q[i].o].o3, seg2.Ask(q[i].r - mid, q[i].o), q[i].o);
  }
  Divide(ql, qmid1 - 1, l, mid);
  Divide(qmid1, qmid2 - 1, mid + 1, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    k = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i] >> b[i];
    }
    seg1.Init(), seg2.Init();
    for (int i = 1; i <= n; i++) {
      seg1.Add(i);
    }
    for (int i = n; i >= 1; i--) {
      seg2.Add(i);
    }
    for (int i = 1; i <= m; i++) {
      o[i].o1 = seg1.Ask(n, i), o[i].o2 = o[i].o3 = 0;
      o[i].o2 = Max(o[i].o2, seg1.Ask(o[i].o1 - 1, i), i);
      o[i].o2 = Max(o[i].o2, seg2.Ask(n - o[i].o1, i), i);
      int x = min(o[i].o1, o[i].o2), y = max(o[i].o1, o[i].o2);
      o[i].o3 = Max(o[i].o3, seg1.Ask(x - 1, i), i);
      o[i].o3 = Max(o[i].o3, seg2.Ask(n - y, i), i);
      if (x + 1 <= y - 1) {
        q[++k] = {x + 1, y - 1, i};
      }
    }
    Divide(1, k, 1, n), f1 = f2 = {0, 0};
    for (int i = 1; i <= m; i++) {
      O o = ::o[i];
      O w = {F(o.o1, i), F(o.o2, i), F(o.o3, i)};
      if (o.o1 != f1.o) {
        if (o.o2 != f1.o && w.o1 == w.o2 || o.o3 != f1.o && w.o1 == w.o3) {
          g1 = {0, f1.w + w.o1};
        } else {
          g1 = {o.o1, f1.w + w.o1};
        }
      } else {
        if (o.o2 != f2.o && w.o1 == w.o2 || o.o3 != f2.o && w.o1 == w.o3) {
          g1 = {0, f2.w + w.o1};
        } else {
          g1 = {o.o1, f2.w + w.o1};
        }
      }
      if (o.o2 != f1.o) {
        if (o.o1 != f1.o && w.o2 == w.o1 || o.o3 != f1.o && w.o2 == w.o3) {
          g2 = {0, f1.w + w.o2};
        } else {
          g2 = {o.o2, f1.w + w.o2};
        }
      } else {
        if (o.o1 != f2.o && w.o2 == w.o1 || o.o3 != f2.o && w.o2 == w.o3) {
          g2 = {0, f2.w + w.o2};
        } else {
          g2 = {o.o2, f2.w + w.o2};
        }
      }
      if (o.o3 != f1.o) {
        if (o.o1 != f1.o && w.o3 == w.o1 || o.o2 != f1.o && w.o3 == w.o2) {
          g3 = {0, f1.w + w.o3};
        } else {
          g3 = {o.o3, f1.w + w.o3};
        }
      } else {
        if (o.o1 != f2.o && w.o3 == w.o1 || o.o2 != f2.o && w.o3 == w.o2) {
          g3 = {0, f2.w + w.o3};
        } else {
          g3 = {o.o3, f2.w + w.o3};
        }
      }
      g1.w < g2.w ? swap(g1, g2) : void();
      g2.w < g3.w ? swap(g2, g3) : void();
      g1.w < g2.w ? swap(g1, g2) : void();
      f1 = g1, f2 = g2;
    }
    cout << f1.w << '\n';
  }
  return 0;
}
