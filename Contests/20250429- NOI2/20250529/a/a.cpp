#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

const int kMaxN = 1.2e5 + 1;
struct Point {
  int x, y;
} a[kMaxN << 1];
int t, n, m, p[kMaxN];
LLL ans;
vector<int> v[kMaxN];

class Uni {
  int f[kMaxN];

 public:
  void Init(int n) {
    for (int i = 1; i <= n; i++) {
      f[i] = i;
    }
  }

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

  bool Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    return x != y ? f[x] = y, 1 : 0;
  }
} uni;

void Print(LLL x) {
  if (x > 9) {
    Print(x / 10);
  }
  putchar(x % 10 + 48);
}

LL Dis(int x, int y) {
  return 1LL * (a[x].x - a[y].x) * (a[x].x - a[y].x) +
         1LL * (a[x].y - a[y].y) * (a[x].y - a[y].y);
}

bool C() {
  static int o[kMaxN];
  m = 0;
  for (int i = 1; i <= n; i++) {
    o[i] = 0, v[i].clear();
  }
  for (int i = 1; i <= n; i++) {
    int x = uni.GetRoot(i);
    !o[x] && (o[x] = ++m);
    v[o[x]].push_back(i);
  }
  return m > 1;
}

void Divide(int *q, int *d, int ql, int qr, int dl, int dr) {
  if (ql > qr || dl == dr) {
    for (int i = ql; i <= qr; i++) {
      if (!p[q[i]] || Dis(q[i], p[q[i]]) < Dis(q[i], d[dl])) {
        p[q[i]] = d[dl];
      }
    }
    return;
  }
  int mid = ql + qr >> 1, ans = 0;
  for (int i = dl; i <= dr; i++) {
    if (q[mid] < d[i] && (!ans || Dis(q[mid], d[ans]) < Dis(q[mid], d[i]))) {
      ans = i;
    }
  }
  if (!p[q[mid]] || Dis(q[mid], p[q[mid]]) < Dis(q[mid], d[ans])) {
    p[q[mid]] = d[ans];
  }
  Divide(q, d, ql, mid - 1, dl, ans);
  Divide(q, d, mid + 1, qr, ans, dr);
}

void Solve(int l, int r) {
  static int d1[kMaxN << 1], d2[kMaxN << 1];
  if (l == r) {
    return;
  }
  int mid = l + r >> 1, k1 = 0, k2 = 0;
  for (int i = l; i <= mid; i++) {
    for (int j : v[i]) {
      d1[++k1] = j;
    }
  }
  sort(d1 + 1, d1 + k1 + 1);
  for (int i = 1; i <= k1; i++) {
    d1[i + k1] = d1[i] + n;
  }
  for (int i = mid + 1; i <= r; i++) {
    for (int j : v[i]) {
      d2[++k2] = j;
    }
  }
  sort(d2 + 1, d2 + k2 + 1);
  for (int i = 1; i <= k2; i++) {
    d2[i + k2] = d2[i] + n;
  }
  Divide(d1, d2, 1, k1, 1, k2 * 2);
  Divide(d2, d1, 1, k2, 1, k1 * 2);
  Solve(l, mid), Solve(mid + 1, r);
}

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y, a[i + n] = a[i];
    }
    uni.Init(n), ans = 0;
    while (C()) {
      for (int i = 1; i <= n; i++) {
        p[i] = 0;
      }
      Solve(1, m);
      for (int i = 1; i <= n; i++) {
        p[i] > n && (p[i] -= n);
      }
      for (int i = 1; i <= m; i++) {
        int t = 0;
        LL w = 0;
        for (int j : v[i]) {
          if (w < Dis(j, p[j])) {
            w = Dis(j, p[j]), t = p[j];
          }
        }
        if (uni.Merge(v[i][0], t)) {
          ans += w;
        }
      }
    }
    Print(ans), putchar(10);
  }
  return 0;
}
