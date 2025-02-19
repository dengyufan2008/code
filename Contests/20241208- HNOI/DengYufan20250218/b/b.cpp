#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1;
int n, m, a[kMaxN], l[kMaxN], r[kMaxN];

class Seg {
  struct E {
    int s;   // sum a_i
    int mx;  // l_i - s_i
    int mn;  // r_i - s_i
    int t;   // 0 进来 t 出来
    int w;   // 0 进来 右边的贡献
  };
  struct V {
    E e[2];
    bool b;
  } v[kMaxN << 2];

  void Calc(int p, int l, int r, int &t, int &w, bool o) {
    if (l == r) {
      if (t < v[p].e[o].mx) {
        w += v[p].e[o].mx - t, t = v[p].e[o].mx;
      } else if (t > v[p].e[o].mn) {
        w += t - v[p].e[o].mn, t = v[p].e[o].mn;
      }
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (v[p << 1].e[o].mx <= v[p << 1].e[o].mn) {
      if (t < v[p << 1].e[o].mx) {
        w += v[p << 1].e[o].mx - t, t = v[p << 1].e[o].mx;
      } else if (t > v[p << 1].e[o].mn) {
        w += t - v[p << 1].e[o].mn, t = v[p << 1].e[o].mn;
      }
      t += v[p << 1].e[o].s;
      Calc(p << 1 | 1, mid + 1, r, t, w, o);
      t -= v[p << 1].e[o].s;
    } else {
      Calc(p << 1, l, mid, t, w, o);
      t = v[p].e[o].t, w += v[p].e[o].w;
    }
  }

  void Tag(int p) {
    v[p].b ^= 1, swap(v[p].e[0], v[p].e[1]);
  }

  void Pushdown(int p) {
    if (v[p].b) {
      Tag(p << 1), Tag(p << 1 | 1), v[p].b = 0;
    }
  }

  void Pushup(int p, int l, int r) {
    int mid = l + r >> 1;
    for (int o : {0, 1}) {
      E &ans = v[p].e[o];
      E &x = v[p << 1].e[o], &y = v[p << 1 | 1].e[o];
      ans.s = x.s + y.s;
      ans.mx = max(x.mx, y.mx - x.s);
      ans.mn = min(x.mn, y.mn - x.s);
      ans.t = x.t + x.s, ans.w = 0;
      Calc(p << 1 | 1, mid + 1, r, ans.t, ans.w, o);
      ans.t -= x.s;
    }
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      for (int o : {0, 1}) {
        v[p].e[o].s = a[l] ^ o;
        v[p].e[o].mx = ::l[l] - (a[l] ^ o);
        v[p].e[o].mn = ::r[l] - (a[l] ^ o);
      }
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    Pushup(p, l, r);
  }

  void Flip(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return Tag(p);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Flip(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      Flip(p << 1 | 1, mid + 1, r, _l, _r);
    }
    Pushup(p, l, r);
  }

 public:
  void Init() { Init(1, 1, n); }
  void Flip(int x, int y) { Flip(1, 1, n, x, y); }

  int Ask() {
    int t = 0, w = 0;
    Calc(1, 1, n, t, w, 0);
    return w;
  }
} seg;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> l[i], l[i] = max(l[i], 0);
  }
  for (int i = 1; i <= n; i++) {
    cin >> r[i], r[i] = min(r[i], i);
  }
  for (int i = 2; i <= n; i++) {
    l[i] = max(l[i], l[i - 1]);
    r[i] = min(r[i], r[i - 1] + 1);
  }
  for (int i = n - 1; i >= 1; i--) {
    l[i] = max(l[i], l[i + 1] - 1);
    r[i] = min(r[i], r[i + 1]);
  }
  seg.Init(), cout << seg.Ask() << '\n';
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, seg.Flip(x, y);
    cout << seg.Ask() << '\n';
  }
  return 0;
}
