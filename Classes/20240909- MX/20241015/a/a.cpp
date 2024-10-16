#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 3e5 + 2;
int t, n, a[kMaxN];
LL ans, s[kMaxN], f[kMaxN], g[kMaxN];
vector<pair<int, int>> l;

LL Sum(LL l, LL r) { return (l + r) * (r - l + 1) / 2; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], s[i] = s[i - 1] + a[i];
    }
    f[0] = f[1] = 0, l.clear(), l.push_back({a[1] - 1, 1});
    for (int i = 2; i <= n; i++) {
      for (; !l.empty() && l.back().first >= a[i] - i; l.pop_back()) {
      }
      int j = l.empty() ? 0 : l.back().second;
      f[i] = f[j] + s[i] - s[j] - Sum(max(a[i] - i + j + 1, 0), a[i]);
      l.push_back({a[i] - i, i});
    }
    g[n] = g[n + 1] = 0, l.clear(), l.push_back({a[n] + n, n});
    for (int i = n - 1; i >= 1; i--) {
      for (; !l.empty() && l.back().first >= a[i] + i; l.pop_back()) {
      }
      int j = l.empty() ? n + 1 : l.back().second;
      g[i] = g[j] + s[j - 1] - s[i - 1] - Sum(max(a[i] + i - j + 1, 0), a[i]);
      l.push_back({a[i] + i, i});
    }
    ans = a[1] + f[1] + g[1];
    for (int i = 2; i <= n; i++) {
      ans = min(ans, a[i] + f[i] + g[i]);
    }
    cout << ans << '\n';
  }
  return 0;
}
