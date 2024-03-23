#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#define LL long long

using namespace std;

const int kMaxN = 2001;
const double kEps = 1e-6, kPi2 = acos(-1) * 2.0;
struct A {
  int x, y, w;
} a[kMaxN];
struct B {
  int d;
  double t;
  bool o;
};
struct V {
  LL w, t;
} v[kMaxN << 2];
int n, l[kMaxN];
LL m;
double ans = 4e4;
vector<B> h;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int Sqr(int x) { return x * x; }

double Dis(int x, int y) { return sqrt(Sqr(a[x].x - a[y].x) + Sqr(a[x].y - a[y].y)); }

double R(double x) {
  for (; x < 0; x += kPi2) {
  }
  for (; x > kPi2; x -= kPi2) {
  }
  return x;
}

void Tag(int p, LL t) {
  v[p].w += t, v[p].t += t;
}

void Pushdown(int p) {
  if (v[p].t) {
    Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t);
    v[p].t = 0;
  }
}

void Pushup(int p) {
  v[p].w = min(v[p << 1].w, v[p << 1 | 1].w);
}

void Init(int p, int l, int r) {
  v[p].t = 0;
  if (l == r) {
    v[p].w = (m + a[l].w - 1) / a[l].w;
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  Pushup(p);
}

void Add(int p, int l, int r, int x, int k) {
  if (r <= x) {
    Tag(p, k);
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  Add(p << 1, l, mid, x, k);
  if (mid < x) {
    Add(p << 1 | 1, mid + 1, r, x, k);
  }
  Pushup(p);
}

bool Ask() { return v[1].w <= 0; }

bool C(int x, double r) {
  h.clear();
  for (int i = 1; i <= n; i++) {
    if (i != x && Dis(i, x) <= r * 2.0) {
      double mid = atan2(a[i].y - a[x].y, a[i].x - a[x].x);
      double len = acos(Dis(x, i) / (r * 2.0));
      double l = R(mid - len), r = R(mid + len);
      if (l < r) {
        h.push_back({i, l, 1}), h.push_back({i, r, 0});
      } else {
        h.push_back({i, l, 1}), h.push_back({i, kPi2, 0});
        h.push_back({i, 0.0, 1}), h.push_back({i, r, 0});
      }
    }
  }
  sort(h.begin(), h.end(), [](B i, B j) { return i.t < j.t; });
  Init(1, 1, n), Add(1, 1, n, x, -1);
  for (B i : h) {
    if (Ask()) {
      return 1;
    }
    Add(1, 1, n, i.d, i.o ? -1 : 1);
  }
  return Ask();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y >> a[i].w;
    l[i] = i;
  }
  sort(a + 1, a + n + 1, [](A i, A j) { return i.w < j.w; });
  shuffle(l + 1, l + n + 1, Rand);
  for (int o = 1; o <= n; o++) {
    int i = l[o];
    double l = 0, r = ans - kEps;
    if (C(i, r)) {
      while (l < r - kEps) {
        double mid = (l + r) * 0.5;
        (C(i, mid) ? r : l) = mid;
      }
      ans = r;
    }
  }
  if (ans > 3e4) {
    cout << -1 << '\n';
  } else {
    cout << fixed << setprecision(8) << ans << '\n';
  }
  return 0;
}
