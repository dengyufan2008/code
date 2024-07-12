#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("mst.in");
ofstream cout("mst.out");

const LL kMaxN = 3e5 + 1, kMaxM = 19;
LL t, n, ans, s[2][kMaxN], a[2][kMaxN], r[2][kMaxN], h[2][kMaxM][kMaxN], f[kMaxM][kMaxN], lg[kMaxN], w[kMaxN], l[kMaxN];

void Init() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> s[0][i];
    s[1][n - i + 1] = s[0][i];
    for (LL j = 0; j < kMaxM; j++) {
      f[j][i] = i;
    }
  }
  for (LL i = 1; i <= (n >> 1); i++) {
    cin >> w[i];
    l[i] = i;
  }
  ans = 0, sort(l + 1, l + (n >> 1) + 1, [](LL i, LL j) { return w[i] < w[j]; });
}

void CalcSa(bool o) {
  LL b[kMaxN] = {}, c[kMaxN] = {};
  for (LL i = 1; i <= n; i++) {
    a[o][i] = i;
  }
  sort(a[o] + 1, a[o] + n + 1, [o](LL i, LL j) { return s[o][i] < s[o][j]; });
  for (LL i = 1; i <= n; i++) {
    r[o][a[o][i]] = r[o][a[o][i - 1]] + (s[o][a[o][i]] != s[o][a[o][i - 1]]);
  }
  for (LL l = 1; l < n; l <<= 1) {
    for (LL i = 1; i <= l; i++) {
      b[i] = n - l + i;  // not a[n - l + i] !!!
    }
    for (LL i = 1, j = l; i <= n; i++) {
      if (a[o][i] > l) {
        b[++j] = a[o][i] - l;
      }
    }
    fill(&c[1], &c[n] + 1, 0);
    for (LL i = 1; i <= n; i++) {
      c[r[o][i]]++;
    }
    for (LL i = 1; i <= n; i++) {
      c[i] += c[i - 1];
    }
    for (LL i = n; i >= 1; i--) {
      a[o][c[r[o][b[i]]]--] = b[i];  // don't swap left & right !!!
    }
    for (LL i = 1; i <= n; i++) {
      b[a[o][i]] = b[a[o][i - 1]] + (r[o][a[o][i]] != r[o][a[o][i - 1]] || r[o][a[o][i] + l] != r[o][a[o][i - 1] + l]);
    }
    copy(&b[1], &b[n] + 1, &r[o][1]);
  }
}

void CalcH(bool o) {
  for (LL i = 1; i <= n; i++) {
    h[o][0][r[o][i]] = max(h[o][0][r[o][i - 1]] - 1, 0LL);
    for (LL &j = h[o][0][r[o][i]]; j <= n && s[o][i + j] == s[o][a[o][r[o][i] - 1] + j]; j++) {
    }
  }
  for (LL i = 1; i < kMaxM; i++) {
    for (LL j = 1; j <= n; j++) {
      h[o][i][j] = h[o][i - 1][j];
      if (j + (1 << i - 1) <= n) {
        h[o][i][j] = min(h[o][i][j], h[o][i - 1][j + (1 << i - 1)]);
      }
    }
  }
}

LL Lc(LL x, LL y, bool o) {
  if (o) {
    x = r[o][n - x + 1], y = r[o][n - y + 1];
  } else {
    x = r[o][x], y = r[o][y];
  }
  if (x == y) {
    return n - a[o][x] + 1;
  } else if (x > y) {
    swap(x, y);
  }
  LL l = lg[y - x];
  return min(h[o][l][x + 1], h[o][l][y - (1 << l) + 1]);
}

LL GetRoot(LL x, LL l) {
  return f[l][x] == x ? x : f[l][x] = GetRoot(f[l][x], l);
}

void Merge(LL x, LL y, LL l) {
  if (GetRoot(x, l) == GetRoot(y, l)) {
    return;
  }
  f[l][GetRoot(x, l)] = GetRoot(y, l);
  if (!l) {
    ans += w[y - x];
    return;
  }
  Merge(x, y, l - 1);
  if (max(x, y) + (1 << l - 1) <= n) {
    Merge(x + (1 << l - 1), y + (1 << l - 1), l - 1);
  }
}

void CalcAns() {
  for (LL _i = 1; _i <= (n >> 1); _i++) {
    LL i = l[_i];
    for (LL j = i, k; (k = j + i) <= n; j += i) {
      LL p = min(Lc(j, k, 0), i), s = min(Lc(j - 1, k - 1, 1), i - 1);
      if (p + s >= i) {
        LL l = lg[p + s];
        Merge(j - s, k - s, l), Merge(j + p - (1 << l), k + p - (1 << l), l);
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  for (LL i = 1, j = 0; i < kMaxN; i++) {
    lg[i] = j;
    if (i == (1 << j + 1)) {
      j++;
    }
  }
  cin >> t >> t;
  while (t--) {
    Init(), CalcSa(0), CalcH(0), CalcSa(1), CalcH(1), CalcAns();
  }
  return 0;
}
