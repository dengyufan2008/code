#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#define LL long long

using namespace std;

ifstream cin("shiro.in");
ofstream cout("shiro.out");

const LL kMaxN = 3e5 + 1, kInf = 4e18;
struct A {
  LL h, v, l;
} a[kMaxN];
int n;
LL w1[kMaxN], w2[kMaxN];
double f[kMaxN];

int LowB(LL x) {
  int l = 1, r = n - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (w2[mid] >= x) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

class Seg1 {
  const static LL kTreeV = 3e18, kSegV = 2e18;
  struct F {
    double a;
    LL b;
    F() : a(kInf), b(kInf) {}
    F(double _a, LL _b) : a(_a), b(_b) {}
  };
  struct V {
    int l, r;
    F f;
  } v[kMaxN * 20];
  int m, s[kMaxN];

  long double Val(F f, LL x) {
    return x <= f.b ? f.a + sqrt(f.b - x) : 1e12L * (f.b - x) + f.a;
  }

  void Add(int &p, int l, int r, F f) {
    !p && (p = ++m);
    if (v[p].f.a == kInf && v[p].f.b == kInf) {
      v[p].f = f;
      return;
    } else if (l == r) {
      if (Val(v[p].f, w1[l]) > Val(f, w1[l])) {
        v[p].f = f;
      }
      return;
    }
    int mid = l + r >> 1;
    if (Val(v[p].f, w1[mid]) > Val(f, w1[mid])) {
      swap(v[p].f, f);
    }
    if (Val(v[p].f, w1[l]) > Val(f, w1[l])) {
      Add(v[p].l, l, mid, f);
    } else if (Val(v[p].f, w1[r]) > Val(f, w1[r])) {
      Add(v[p].r, mid + 1, r, f);
    }
  }

  double Ask(int p, int l, int r, int x) {
    if (!p) {
      return kInf;
    } else if (l == r) {
      return Val(v[p].f, w1[x]);
    }
    int mid = l + r >> 1;
    double ans = kInf;
    if (mid >= x) {
      ans = Ask(v[p].l, l, mid, x);
    } else {
      ans = Ask(v[p].r, mid + 1, r, x);
    }
    if (v[p].f.a != kInf || v[p].f.b != kInf) {
      ans = min(ans, (double)Val(v[p].f, w1[x]));
    }
    return ans;
  }

 public:
  void Add(LL t, double a) {
    for (int i = LowB(t); i < n; i += i & -i) {
      Add(s[i], 1, n - 1, F(a, t));
    }
  }

  double Ask(LL t, int x) {
    double ans = kInf;
    for (LL i = LowB(t); i >= 1; i -= i & -i) {
      ans = min(ans, Ask(s[i], 1, n - 1, x));
    }
    return ans;
  }
} seg1;

class Seg2 {
  const static LL kSegV = 3e18;
  struct F {
    double a;
    LL b;
    F() : a(kInf), b(kInf) {}
    F(double _a, LL _b) : a(_a), b(_b) {}
  };
  struct V {
    int l, r;
    F f;
  } v[kMaxN * 20];
  int s, m;

  double Val(F f, LL x) { return f.a - sqrt(x - f.b); }

  void Add(int &p, int l, int r, F f) {
    !p && (p = ++m);
    if (v[p].f.a == kInf && v[p].f.b == kInf) {
      v[p].f = f;
      return;
    } else if (l == r) {
      if (Val(v[p].f, w2[l]) > Val(f, w2[l])) {
        v[p].f = f;
      }
      return;
    }
    int mid = l + r >> 1;
    if (Val(v[p].f, w2[mid]) > Val(f, w2[mid])) {
      swap(v[p].f, f);
    }
    if (Val(v[p].f, w2[l]) > Val(f, w2[l])) {
      Add(v[p].l, l, mid, f);
    } else if (Val(v[p].f, w2[r]) > Val(f, w2[r])) {
      Add(v[p].r, mid + 1, r, f);
    }
  }

  void Add(int &p, int l, int r, int _l, int _r, F f) {
    !p && (p = ++m);
    if (l >= _l && r <= _r) {
      return Add(p, l, r, f);
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(v[p].l, l, mid, _l, _r, f);
    }
    if (mid < _r) {
      Add(v[p].r, mid + 1, r, _l, _r, f);
    }
  }

  double Ask(int p, int l, int r, int x) {
    if (!p) {
      return kInf;
    } else if (l == r) {
      return Val(v[p].f, w2[x]);
    }
    int mid = l + r >> 1;
    double ans = kInf;
    if (mid >= x) {
      ans = Ask(v[p].l, l, mid, x);
    } else {
      ans = Ask(v[p].r, mid + 1, r, x);
    }
    if (v[p].f.a != kInf || v[p].f.b != kInf) {
      ans = min(ans, Val(v[p].f, w2[x]));
    }
    return ans;
  }

 public:
  void Add(double a, LL b, LL c) {
    int l = LowB(b), r = LowB(c + 1) - 1;
    if (l <= r) {
      Add(s, 1, n - 1, l, r, F(a, b));
    }
  }

  double Ask(int x) { return Ask(s, 1, n - 1, x); }
} seg2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].h >> a[i].v >> a[i].l;
  }
  for (int i = 1; i < n; i++) {
    w1[i] = 2 * a[i].h, w2[i] = a[i].l * a[i].l + 2 * a[i].h;
  }
  sort(w2 + 1, w2 + n);
  for (int i = n - 1; i >= 1; i--) {
    seg1.Add(a[i + 1].v * a[i + 1].v + 2 * a[i + 1].h, f[i + 1] - a[i + 1].v);
    seg2.Add(f[i + 1], 2 * a[i + 1].h, a[i + 1].v * a[i + 1].v + 2 * a[i + 1].h);
    f[i] = seg1.Ask(a[i].l * a[i].l + 2 * a[i].h, i);
    f[i] = min(f[i], seg2.Ask(LowB(a[i].l * a[i].l + 2 * a[i].h)) + a[i].l);
  }
  if (f[1] > 1e17) {
    cout << -1 << '\n';
  } else {
    cout << fixed << setprecision(6) << f[1] << '\n';
  }
  return 0;
}
// 800ms, 460MiB
