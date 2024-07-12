#include <algorithm>
#include <iostream>
#define LL __int128_t
#define Point pair<LL, LL>
#define Line pair<Point, Point>

using namespace std;

const int kMaxN = 1e6 + 1;
const LL kInf = (LL)1e18 * (LL)1e18;
struct V {
  LL a, b;

  LL Gcd(LL x, LL y) {
    for (; y; swap(x, y), y %= x) {
    }
    return max(x, (LL)1);
  }

  void Init(LL x, LL y) {
    LL z = Gcd(x, y);
    a = x / z, b = y / z;
  }

  bool operator<(const V v) const {
    LL a0 = a & ~((LL)-1 << 63), a1 = a >> 63,
       b0 = b & ~((LL)-1 << 63), b1 = b >> 63,
       c0 = v.a & ~((LL)-1 << 63), c1 = v.a >> 63,
       d0 = v.b & ~((LL)-1 << 63), d1 = v.b >> 63;
    LL l0 = a0 * d0, l1 = a0 * d1 + a1 * d0, l2 = a1 * d1;
    LL r0 = b0 * c0, r1 = b0 * c1 + b1 * c0, r2 = b1 * c1;
    l1 += l0 >> 63, l0 &= ~((LL)-1 << 63);
    l2 += l1 >> 63, l1 &= ~((LL)-1 << 63);
    r1 += r0 >> 63, r0 &= ~((LL)-1 << 63);
    r2 += r1 >> 63, r1 &= ~((LL)-1 << 63);
    if (l2 != r2) {
      return l2 < r2;
    } else if (l1 != r1) {
      return l1 < r1;
    } else {
      return l0 < r0;
    }
  }

  V operator/(const int x) const {
    V t = *this;
    if (!(a % x)) {
      t.a /= x;
    } else {
      t.b *= x;
    }
    return t;
  }
} ans = {kInf, 1};
int n, m;
Point a[kMaxN], p[kMaxN];

LL Cross(Point o, Point x, Point y) {
  return (LL)(x.first - o.first) * (y.second - o.second) - (LL)(x.second - o.second) * (y.first - o.first);
}

LL Dis(Point x, Point y) {
  return (LL)(x.first - y.first) * (x.first - y.first) + (LL)(x.second - y.second) * (x.second - y.second);
}

V Dis(Line l, Point x) {
  LL s = Cross(x, l.first, l.second);
  V dis;
  dis.Init(s * s, Dis(l.first, l.second));
  return dis;
}

LL Read() {
  LL x = 0;
  int c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

void Write(LL x) {
  if (x > 9) {
    Write(x / 10);
  }
  putchar(x % 10 + 48);
}

int main() {
  // freopen("c.in", "r", stdin);
  // freopen("c.out", "w", stdout);
  n = Read();
  for (int i = 1; i <= n; i++) {
    a[i].first = Read(), a[i].second = Read();
  }
  sort(a + 1, a + n + 1);
  for (int i = 1, _m = m; i <= n; i++) {
    for (; m > _m + 1 && Cross(p[m - 1], p[m], a[i]) <= 0; m--) {
    }
    p[++m] = a[i];
  }
  m--;
  for (int i = n, _m = m; i >= 1; i--) {
    for (; m > _m + 1 && Cross(p[m - 1], p[m], a[i]) <= 0; m--) {
    }
    p[++m] = a[i];
  }
  m--;
  if (m <= 2) {
    cout << "0/1";
    return 0;
  }
  for (int x = 1, i = 2; x <= m; x++) {
    int y = x % m + 1, j = i % m + 1;
    V disi = Dis({p[x], p[y]}, p[i]), disj = Dis({p[x], p[y]}, p[j]);
    for (; disi < disj; i = j, j = j % m + 1, disi = disj, disj = Dis({p[x], p[y]}, p[j])) {
    }
    disi = disi / 2 / 2, ans = min(ans, disi);
  }
  Write(ans.a), putchar(47), Write(ans.b);
  return 0;
}
