// 显然可以做到单 log, 但我懒
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 2e5 + 1, kMaxM = 40, kInf = 1e18;
int n;
LL s, ans, a[kMaxN];
vector<pair<int, LL>> l[kMaxN], r[kMaxN];

LL Gcd(LL x, LL y) {
  return y ? Gcd(y, x % y) : x;
}

void Input() {
  LL g = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], s += a[i], g = Gcd(g, a[i]);
  }
  n--, s -= g;
  for (int i = 1; i <= n; i++) {
    a[i] = Gcd(a[i], a[i + 1]);
  }
}

void Calc() {
  for (int i = 1; i <= n; i++) {
    LL g = a[i];
    l[i].push_back({i, g});
    for (auto j : l[i - 1]) {
      g = Gcd(g, j.second);
      if (g < l[i].back().second) {
        l[i].push_back({j.first, g});
      }
    }
  }
  for (int i = n; i >= 1; i--) {
    LL g = a[i];
    r[i].push_back({i, g});
    for (auto j : r[i + 1]) {
      g = Gcd(g, j.second);
      if (g < r[i].back().second) {
        r[i].push_back({j.first, g});
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j + 1 < l[i].size(); j++) {
      l[i][j].first = l[i][j].first - l[i][j + 1].first;
    }
    l[i].back().first = l[i].back().first;
    for (int j = 0; j + 1 < r[i].size(); j++) {
      r[i][j].first = r[i][j + 1].first - r[i][j].first;
    }
    r[i].back().first = n - r[i].back().first + 1;
  }
}

LL Dp(int x) {
  static LL g[kMaxM][kMaxM], f[kMaxM][kMaxM];
  vector<pair<int, LL>> &_l = l[x], &_r = r[x];
  g[0][0] = Gcd(_l[0].second, _r[0].second);
  for (int i = 1; i < _l.size(); i++) {
    g[i][0] = Gcd(g[i - 1][0], _l[i].second);
  }
  for (int i = 1; i < _r.size(); i++) {
    g[0][i] = Gcd(g[0][i - 1], _r[i].second);
  }
  for (int i = 1; i < _l.size(); i++) {
    for (int j = 1; j < _r.size(); j++) {
      g[i][j] = Gcd(g[i - 1][j], g[i][j - 1]);
    }
  }
  for (int i = 1; i < _l.size(); i++) {
    f[i][0] = f[i - 1][0] + g[i - 1][0] * _l[i - 1].first;
  }
  for (int i = 1; i < _r.size(); i++) {
    f[0][i] = f[0][i - 1] + g[0][i - 1] * _r[i - 1].first;
  }
  for (int i = 1; i < _l.size(); i++) {
    for (int j = 1; j < _r.size(); j++) {
      f[i][j] = min(f[i - 1][j] + g[i - 1][j] * _l[i - 1].first,
                    f[i][j - 1] + g[i][j - 1] * _r[j - 1].first);
    }
  }
  {
    LL w = g[_l.size() - 1][_r.size() - 1] * (_l.back().first + _r.back().first - 1);
    return f[_l.size() - 1][_r.size() - 1] + w;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Calc();
  if (!n) {
    cout << 0 << '\n';
    return 0;
  }
  ans = kInf;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, Dp(i));
  }
  cout << ans + s << '\n';
  return 0;
}
