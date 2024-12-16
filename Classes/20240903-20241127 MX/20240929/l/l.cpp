#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 2e5 + 1, kMaxL = 18;
int n, m, ans, d[2][kMaxN];
int a[kMaxN], r[kMaxN], l[kMaxL][kMaxN], lg[kMaxN];
string s[2], t;

void CalcD(bool o) {
  t = "~";
  for (char c : s[o]) {
    t += c, t += '~';
  }
  for (int i = 0, j, k = 0; i < m; i++) {
    if (i < k && i + d[o][(j << 1) - i] < k) {
      d[o][i] = d[o][(j << 1) - i];
      continue;
    }
    for (j = i; k < m && k <= (j << 1) && t[k] == t[(j << 1) - k]; k++) {
    }
    d[o][i] = k - j, ans = max(ans, k - j - 1);
  }
}

void CalcSA() {
  static int b[kMaxN] = {}, c[kMaxN] = {};
  t = s[0], reverse(t.begin(), t.end()), t += s[1], t += '~';
  for (int i = 0; i < m; i++) {
    a[i] = i;
  }
  sort(a, a + m, [](int i, int j) { return t[i] < t[j]; });
  r[a[0]] = 0;
  for (int i = 1; i < m; i++) {
    r[a[i]] = r[a[i - 1]] + (t[a[i]] != t[a[i - 1]]);
  }
  for (int h = 1; h < m; h <<= 1) {
    for (int i = 0; i < h; i++) {
      b[i] = m - h + i;
    }
    for (int i = 0, j = h; i < m; i++) {
      if (a[i] >= h) {
        b[j++] = a[i] - h;
      }
    }
    fill(&c[0], &c[m], 0);
    for (int i = 0; i < m; i++) {
      c[r[i]]++;
    }
    for (int i = 1; i < m; i++) {
      c[i] += c[i - 1];
    }
    for (int i = m - 1; i >= 0; i--) {
      a[--c[r[b[i]]]] = b[i];
    }
    b[a[0]] = 0;
    for (int i = 1; i < m; i++) {
      b[a[i]] = b[a[i - 1]];
      if (r[a[i]] != r[a[i - 1]]) {
        b[a[i]]++;
      } else if (r[a[i] + h] != r[a[i - 1] + h]) {
        b[a[i]]++;
      }
    }
    copy(&b[0], &b[m], &r[0]);
  }
}

void CalcLen() {
  for (int i = 0; i < m; i++) {
    if (r[i] + 1 < m) {
      l[0][r[i]] = max(l[0][r[i - 1 + !i]] - 1, 0);
      for (int &j = l[0][r[i]]; t[i + j] == t[a[r[i] + 1] + j]; j++) {
      }
    }
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 0; j + 1 < m; j++) {
      l[i][j] = l[i - 1][j];
      if (j + (1 << i - 1) < m) {
        l[i][j] = min(l[i][j], l[i - 1][j + (1 << i - 1)]);
      }
    }
  }
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
}

int Lcp(int x, int y) {
  if (x == y) {
    return m - x;
  } else {
    x = r[x], y = r[y];
    x > y ? swap(x, y) : void();
    int o = lg[y - x];
    return min(l[o][x], l[o][y - (1 << o)]);
  }
}

void CalcAns() {
  for (int i = 0; i < n; i++) {
    ans = max(ans, Lcp(n - i - 1, n + i) * 2);
  }
  for (int i = 0, l, r; i < m; i++) {
    l = i - d[0][i] + 1 >> 1, r = i + d[0][i] - 3 >> 1;
    if (l > 0 && l <= r && r < n) {
      int lcp = min(Lcp(n - l, n + r), min(l, n - r));
      ans = max(ans, lcp * 2 + r - l + 1);
    }
    l = i - d[1][i] + 1 >> 1, r = i + d[1][i] - 3 >> 1;
    if (l >= 0 && l <= r && r + 1 < n) {
      int lcp = min(Lcp(n - l - 1, n + r + 1), min(l + 1, n - r - 1));
      ans = max(ans, lcp * 2 + r - l + 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s[0] >> s[1], m = n << 1 | 1;
  CalcD(0), CalcD(1);
  CalcSA(), CalcLen(), CalcAns();
  cout << ans << '\n';
  return 0;
}
