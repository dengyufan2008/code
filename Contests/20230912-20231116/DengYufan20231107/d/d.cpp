#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const LL kMaxN = 2e6 + 1, kInf = 4e18;
struct V {
  LL x, y;
};
struct Poly {
  int h = 1, t;
  V a[kMaxN];

  LL Cross(V o, V s, V t) {
    return (s.x - o.x) * (t.y - o.y) - (s.y - o.y) * (t.x - o.x);
  }

  LL Sign(LL x) {
    if (x > 0) {
      return 1;
    } else if (x < 0) {
      return -1;
    }
    return 0;
  }

  void Insert(LL x, LL y) {
    for (; t - h >= 1 && Sign(Cross(a[t - 1], a[t], {x, y})) * Sign(a[t - 1].x - a[t].x) >= 0; t--) {
    }
    a[++t] = {x, y};
  }

  bool C(V s, V t, LL k) {
    if (s.x >= t.x) {
      return s.y - t.y >= (s.x - t.x) * k;
    } else {
      return t.y - s.y <= (t.x - s.x) * k;
    }
  }

  V Ask(LL k) {
    for (; t - h >= 1 && C(a[h], a[h + 1], k); h++) {
    }
    return a[h];
  }
} l, r;
LL n, m, a[kMaxN], f[kMaxN];

LL Abs(LL x) { return x > 0 ? x : -x; }

LL L(LL x) { return f[x] - 2LL * x * a[x] + 2LL * a[x]; }

LL R(LL x) { return f[x] - 2LL * x * a[x] + 2LL * n * a[x]; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 2; i <= n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    f[m] += Abs(a[m] - a[i]);
  }
  l.Insert(m, L(m)), r.Insert(m, R(m));
  for (int i = m - 1, j = m + 1; i >= 1 || j <= n;) {
    V lp = l.Ask(-2LL * a[j]), rp = r.Ask(-2LL * a[i]);
    LL lv = kInf, rv = kInf;
    if (i >= 1) {
      lv = rp.y - 2LL * (n - rp.x) * a[i];
    }
    if (j <= n) {
      rv = lp.y + 2LL * (lp.x - 1) * a[j];
    }
    if (lv <= rv) {
      f[i] = lv, l.Insert(i, L(i)), i--;
    } else {
      f[j] = rv, r.Insert(j, R(j)), j++;
    }
  }
  cout << f[1];
  return 0;
}
