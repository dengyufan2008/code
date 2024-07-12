#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const LL kMaxN = 1e5 + 2, kMaxL = 18, kInf = 1e18;
struct V {
  int l, r;
} v[kMaxN];
int n, m, a[kMaxN], l[kMaxN], lg[kMaxN];
LL ans = -kInf, s[kMaxN], d[2][kMaxL][kMaxN];

LL Ask(int x, int y, bool b) {
  int l = lg[y - x + 1];
  if (b) {
    return max(d[1][l][x], d[1][l][y - (1 << l) + 1] + s[y - (1 << l)] - s[x - 1]);
  } else {
    return max(d[0][l][y], d[0][l][x + (1 << l) - 1] + s[y] - s[x + (1 << l) - 1]);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    l[i] = i, v[i].l = i - 1, v[i].r = i + 1;
    s[i] = s[i - 1] + a[i], d[0][0][i] = d[1][0][i] = a[i];
  }
  v[0].r = 1, v[n + 1].l = n;
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      d[0][i][j] = d[0][i - 1][j];
      if (j - (1 << i - 1) >= 1) {
        d[0][i][j] = max(d[0][i][j], d[0][i - 1][j - (1 << i - 1)] + s[j] - s[j - (1 << i - 1)]);
      }
      d[1][i][j] = d[1][i - 1][j];
      if (j + (1 << i - 1) <= n) {
        d[1][i][j] = max(d[1][i][j], d[1][i - 1][j + (1 << i - 1)] + s[j + (1 << i - 1) - 1] - s[j - 1]);
      }
    }
  }
  for (int i = 1, j = 0; i <= n; i++) {
    lg[i] = j;
    if (i == (1 << j + 1)) {
      j++;
    }
  }
  sort(l + 1, l + n + 1, [](int i, int j) { return a[i] < a[j]; });
  if (m == 0) {
    for (int i = 1; i <= n; i++) {
      ans = max(ans, d[0][kMaxL - 1][i]);
    }
  } else {
    for (int i = 1, j; i <= n - m + 1; i++) {
      int p = l[i], q = l[i];
      LL c = a[l[i]];
      for (j = 1; j < m && p >= 1; j++) {
        p = v[p].l, c += a[p];
      }
      if (!p) {
        c -= a[p], p = v[p].r, j--;
      }
      for (; j < m && q <= n; j++) {
        q = v[q].r, c += a[q];
      }
      for (; j >= 1 && q <= n; j--) {
        ans = max(ans, Ask(v[p].l + 1, p, 0) + Ask(q, v[q].r - 1, 1) + s[q - 1] - s[p] - c);
        c -= a[p], p = v[p].r, q = v[q].r, c += a[q];
      }
      v[v[l[i]].l].r = v[l[i]].r, v[v[l[i]].r].l = v[l[i]].l;
    }
  }
  cout << ans;
  return 0;
}
