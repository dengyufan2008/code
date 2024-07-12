#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

const int kMaxN = 5e5 + 1, kMaxM = kMaxN << 2, kMaxL = 21, kMod = 998244353;
struct V {
  int f[kMaxL];
} v[kMaxN];
int n, m, l[kMaxM], r[kMaxM], nt[kMaxM];
pair<int, int> a[kMaxN], q[kMaxN];

void Init() {
  int k = 0;
  LL d[kMaxM] = {}, p[kMaxM] = {}, w[kMaxM] = {};
  cin >> n >> m;
  for (int i = 1; i <= n + m; i++) {
    cin >> d[i * 2 - 1] >> d[i * 2];
  }
  k = n + m << 1;
  for (int i = 1; i <= k; i++) {
    p[i] = i;
  }
  sort(p + 1, p + k + 1, [&](int i, int j) { return d[i] < d[j]; });
  for (int i = 1; i <= k; i++) {
    w[p[i]] = w[p[i - 1]] + (i == 1 || d[p[i - 1]] != d[p[i]]);
  }
  for (int i = m; i >= 1; i--) {
    q[i].second = w[k--], q[i].first = w[k--];
  }
  for (int i = n; i >= 1; i--) {
    a[i].second = w[k--], a[i].first = w[k--];
  }
  sort(a + 1, a + n + 1), k = n;
  for (int i = n, j = n + m << 1 | 1; i >= 1; i--) {
    if (a[i].second < j && a[i].first != a[i - 1].first) {
      a[k--] = a[i], j = a[i].second;
    }
  }
  copy(&a[k + 1], &a[n] + 1, &a[1]);
  for (int i = 1; i <= n - k; i++) {
    l[a[i].first] = r[a[i].second] = i;
  }
  for (int i = n + m << 1, j = 0; i >= 1; i--) {
    if (r[i]) {
      v[r[i]].f[0] = j;
      for (int l = 1; l < kMaxL; l++) {
        v[r[i]].f[l] = v[v[r[i]].f[l - 1]].f[l - 1];
      }
    }
    nt[i] = j, l[i] && (j = l[i]);
  }
  n -= k;
}

int Ans(int x, int y) {
  int z = nt[x], _z = z, _x = x;
  x = l[x];
  if (a[x].second == y) {
    return kMod - 1;
  } else if (!x || !z || max(a[x].second, a[z].second) > y || a[z].first > a[x].second) {
    return 0;
  }
  for (int l = kMaxL - 1; l >= 0; l--) {
    if (v[x].f[l] && a[v[x].f[l]].second <= y) {
      x = v[x].f[l];
    }
    if (v[z].f[l] && a[v[z].f[l]].second <= y) {
      z = v[z].f[l];
    }
  }
  if (x == z || max(a[x].second, a[z].second) < y) {
    return 0;
  }
  return a[x].second == y ? kMod - 1 : 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  for (int i = 1; i <= m; i++) {
    cout << Ans(q[i].first, q[i].second) << '\n';
  }
  return 0;
}
