#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 2e5 + 1, kMaxL = 18;
int o, n, m, k, a[kMaxN], b[kMaxN], d[2][kMaxL][kMaxN], lg[kMaxN];
set<int> s, t;

void Erase(int &x, int l, int mid, int r) {
  x++, t.insert(mid), s.erase(mid);
  for (;;) {
    auto p = s.lower_bound(mid);
    if (p == s.end() || *p > r || p == s.begin() || *--p < l) {
      return;
    }
    auto q = p = t.lower_bound(b[x]);
    Erase(x, *--p, b[x], *q);
  }
}

void Calc(bool o) {
  for (int i = 1; i <= n; i++) {
    a[b[i]] = i;
  }
  s.clear(), t.clear(), t.insert(0), t.insert(n + 1);
  for (int i = 1, j = 1; i <= n; i++) {
    s.size() == k ? Erase(j, 0, b[j], n + 1) : void();
    if (!s.empty()) {
      if (b[i] < *s.begin()) {
        auto p = t.lower_bound(b[i]);
        if (p != t.end() && *p < *s.begin()) {
          for (int u : s) {
            t.insert(u);
          }
          s.clear(), j = i;
        }
      } else if (b[i] > *--s.end()) {
        auto p = t.lower_bound(*--s.end());
        if (p != t.end() && *p < b[i]) {
          for (int u : s) {
            t.insert(u);
          }
          s.clear(), j = i;
        }
      }
    }
    s.insert(b[i]), d[o][0][i] = j - 1;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      d[o][i][j] = d[o][i - 1][d[o][i - 1][j]];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> o;
  while (o--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], b[a[i]] = i;
    }
    reverse(b + 1, b + n + 1), Calc(0);
    reverse(b + 1, b + n + 1), Calc(1);
    cin >> m;
    for (int i = 1, x, y; i <= m; i++) {
      static char c;
      cin >> x >> y >> c;
      if (c == 'H') {
        int z = n - x + 1, ans = 0;
        for (int j = kMaxL - 1; j >= 0; j--) {
          if (d[0][j][z] >= n - y + 1) {
            z = d[0][j][z], ans |= 1 << j;
          }
        }
        cout << ans + 1 << '\n';
      } else {
        int z = y, ans = 0;
        for (int j = kMaxL - 1; j >= 0; j--) {
          if (d[1][j][z] >= x) {
            z = d[1][j][z], ans |= 1 << j;
          }
        }
        cout << ans + 1 << '\n';
      }
    }
  }
  return 0;
}
