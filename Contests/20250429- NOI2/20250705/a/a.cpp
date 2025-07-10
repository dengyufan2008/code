#include <algorithm>
#include <fstream>
#include <set>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 2, kMaxL = 17;
int n, m, a[kMaxN], b[kMaxN], c[kMaxN];

void Init() {
  static int f[kMaxN], g[kMaxN];
  static pair<int, int> t[kMaxN];
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> f[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> g[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> t[i].first;
  }
  for (int i = 1; i <= n; i++) {
    cin >> t[i].second;
  }
  sort(t + 1, t + n + 1);
  for (int i = 1; i <= n; i++) {
    int x = lower_bound(t + 1, t + n + 1, make_pair(f[i], 0)) - t;
    int y = lower_bound(t + 1, t + n + 1, make_pair(g[i] + 1, 0)) - t - 1;
    x <= n && (a[x]++), y >= 1 && (b[y]++);
    c[i] = t[i].second;
  }
  for (int i = 1; i <= n; i++) {
    a[i] += a[i - 1];
  }
  for (int i = n; i >= 1; i--) {
    b[i] += b[i + 1];
  }
  m = n;
  for (int i = 0; i <= n; i++) {
    m = min(m, a[i] + b[i + 1]);
  }
}

LL Calc(int m) {
  static multiset<int> s;
  LL ans = 0;
  s.clear();
  for (int i = 1, j = 0; i <= n; i++) {
    int l = m - b[i + 1], r = a[i];
    s.insert(c[i]);
    if (j > r) {
      return 0;
    }
    while (j + (int)s.size() > r) {
      s.erase(s.begin());
    }
    if (j + (int)s.size() < l) {
      return 0;
    }
    for (; j < l; j++) {
      ans += *s.rbegin(), s.erase(--s.end());
    }
  }
  return ans;
}

int main() {
  Init();
  LL ans = 0;
  for (int i = kMaxL - 1, x = 0; i >= 0; i--) {
    if (x + (1 << i) <= m) {
      LL _ans = Calc(x + (1 << i));
      if (ans < _ans) {
        x += 1 << i, ans = _ans;
        continue;
      }
    }
    if (x - (1 << i) >= 0) {
      LL _ans = Calc(x - (1 << i));
      if (ans < _ans) {
        x -= 1 << i, ans = _ans;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
