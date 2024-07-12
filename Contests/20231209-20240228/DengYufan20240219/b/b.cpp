#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 2e5 + 1, kMaxL = 18, kMaxV = 1e9, kInf = kMaxV * kMaxV * 2;
struct Point {
  LL x, y;
  bool operator<(const Point p) const { return x < p.x || x == p.x && y < p.y; }
  void Swap() { swap(x, y); }
} a[kMaxN], d[kMaxN];
struct Q {
  int l, r;
  LL x, y;
} q[kMaxN];
int n, lg[kMaxN];
LL ans;
class H {
  int t, w;
  Point a[kMaxN];

  LL Cross(Point o, Point x, Point y) {
    return (x.x - o.x) * (y.y - o.y) - (x.y - o.y) * (y.x - o.x);
  }

 public:
  H(int _w) : w(_w), t(0) {}
  void Clear() { t = 0; }

  void Insert(Point x) {
    for (; t >= 2 && w * Cross(a[t - 1], a[t], x) >= 0; t--) {
    }
    a[++t] = x;
  }

  LL Ask(int x, int y) {
    int l = 1, r = t;
    while (l <= r) {
      int mid = l + r >> 1;
      if (mid == 1 || x * (a[mid].x - a[mid - 1].x) + y * (a[mid].y - a[mid - 1].y) < 0) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return x * a[r].x + y * a[r].y;
  }
} h1(-1), h2(1);
class T {
  LL d[kMaxL][kMaxN];

 public:
  T() { d[0][1] = kInf; }
  void Set(int x, LL k) { d[0][x] = k; }

  void Calc() {
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = d[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          d[i][j] = min(d[i][j], d[i - 1][j + (1 << i - 1)]);
        }
      }
    }
  }

  LL Min(int l, int r) {
    int t = lg[r - l + 1];
    return min(d[t][l], d[t][r - (1 << t) + 1]);
  }
} t1, t2, t3, t4;

void Swap() {
  for (int i = 1; i <= n; i++) {
    a[i].Swap();
  }
  sort(a + 1, a + n + 1);
}

void SwapY() {
  for (int i = 1; i <= n; i++) {
    a[i].y = kMaxV - a[i].y;
  }
  sort(a + 1, a + n + 1);
}

void Calc1() {
  LL pmn[kMaxN], pmx[kMaxN], smn[kMaxN], smx[kMaxN];
  pmn[1] = pmx[1] = a[1].y, smn[n] = smx[n] = a[n].y;
  for (int i = 2; i <= n; i++) {
    pmn[i] = min(pmn[i - 1], a[i].y);
    pmx[i] = max(pmx[i - 1], a[i].y);
  }
  for (int i = n - 1; i >= 1; i--) {
    smn[i] = min(smn[i + 1], a[i].y);
    smx[i] = max(smx[i + 1], a[i].y);
  }
  for (int i = 1; i < n; i++) {
    LL x = (pmx[i] - pmn[i]) * (a[i].x - a[1].x);
    LL y = (smx[i + 1] - smn[i + 1]) * (a[n].x - a[i + 1].x);
    ans = min(ans, x + y);
  }
}

void Divide(int ql, int qr, int dl, int dr) {
  if (ql > qr) {
    return;
  }
  int dm = dl + dr >> 1, qm1, qm2;
  for (int i = qm1 = ql; i <= qr; i++) {
    if (q[i].r < dm) {
      swap(q[i], q[qm1++]);
    }
  }
  for (int i = qm2 = qm1; i <= qr; i++) {
    if (q[i].l > dm) {
      swap(q[i], q[qm2++]);
    }
  }
  sort(q + qm2, q + qr + 1, [](Q i, Q j) { return i.l > j.l; });
  h1.Clear();
  for (int i = dm, j = qm2; i >= dl; i--) {
    h1.Insert(d[i]);
    for (; j <= qr && q[j].l == i; j++) {
      ans = min(ans, h1.Ask(q[j].x, q[j].y));
    }
  }
  sort(q + qm2, q + qr + 1, [](Q i, Q j) { return i.r < j.r; });
  h2.Clear();
  for (int i = dm, j = qm2; i <= dr; i++) {
    h2.Insert(d[i]);
    for (; j <= qr && q[j].r == i; j++) {
      ans = min(ans, h2.Ask(q[j].x, q[j].y));
    }
  }
  Divide(ql, qm1 - 1, dl, dm - 1);
  Divide(qm1, qm2 - 1, dm + 1, dr);
}

void Calc2() {
  LL p[kMaxN], s[kMaxN];
  p[1] = a[1].y, s[n] = a[n].y;
  for (int i = 2; i <= n; i++) {
    p[i] = max(p[i - 1], a[i].y);
  }
  for (int i = n - 1; i >= 1; i--) {
    s[i] = min(s[i + 1], a[i].y);
  }
  for (int i = 2, j = 1; i <= n; i++) {
    for (; j + 1 < i && p[j] < s[i]; j++) {
    }
    d[i - 1] = {a[n].x - a[i].x, p[i - 1] - s[1]};
    q[i] = {j, i - 1, p[n] - s[i], a[i - 1].x - a[1].x};
  }
  Divide(2, n, 1, n - 1);
}

void Calc3() {
  LL pmn[kMaxN], pmx[kMaxN], smn[kMaxN], smx[kMaxN];
  pmn[1] = pmx[1] = a[1].y, smn[n] = smx[n] = a[n].y;
  for (int i = 2; i <= n; i++) {
    pmn[i] = min(pmn[i - 1], a[i].y);
    pmx[i] = max(pmx[i - 1], a[i].y);
  }
  for (int i = n - 1; i >= 1; i--) {
    smn[i] = min(smn[i + 1], a[i].y);
    smx[i] = max(smx[i + 1], a[i].y);
  }
  for (int i = 2; i <= n; i++) {
    t1.Set(i, (pmx[n] - pmn[n]) * a[i - 1].x);
    t2.Set(i, (pmx[n] - pmn[n]) * a[i - 1].x - (a[n].x - a[1].x) * smn[i]);
    t3.Set(i, (pmx[n] - pmn[n]) * a[i - 1].x + (a[n].x - a[1].x) * smx[i]);
    t4.Set(i, (pmx[n] - pmn[n]) * a[i - 1].x + (a[n].x - a[1].x) * (smx[i] - smn[i]));
  }
  t1.Calc(), t2.Calc(), t3.Calc(), t4.Calc();
  for (int i = 1, jmn = n, jmx = n; i + 1 < n; i++) {
    for (; jmn - 1 > i && pmn[i] <= smn[jmn]; jmn--) {
    }
    for (; jmx - 1 > i && pmx[i] >= smx[jmx]; jmx--) {
    }
    jmn = max(jmn, i + 1), jmx = max(jmx, i + 1);
    if (max(jmn, jmx) < n) {
      ans = min(ans, t1.Min(max(jmn, jmx) + 1, n) - (pmx[n] - pmn[n]) * a[i + 1].x + (a[n].x - a[1].x) * (pmx[i] - pmn[i]));
    }
    if (jmx < jmn) {
      ans = min(ans, t2.Min(jmx + 1, jmn) - (pmx[n] - pmn[n]) * a[i + 1].x + (a[n].x - a[1].x) * pmx[i]);
    }
    if (jmn < jmx) {
      ans = min(ans, t3.Min(jmn + 1, jmx) - (pmx[n] - pmn[n]) * a[i + 1].x - (a[n].x - a[1].x) * pmn[i]);
    }
    if (i + 1 < min(jmn, jmx)) {
      ans = min(ans, t4.Min(i + 2, min(jmn, jmx)) - (pmx[n] - pmn[n]) * a[i + 1].x);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1, j = 0; i < kMaxN; i++) {
    lg[i] = j;
    if (i == (1 << j + 1)) {
      j++;
    }
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  ans = kInf;
  Swap(), Calc1(), Swap(), Calc1();
  SwapY(), Calc2(), SwapY(), Calc2();
  Calc3();
  cout << ans << '\n';
  return 0;
}
