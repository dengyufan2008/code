#include <algorithm>
#include <iostream>
#include <vector>
#define RF(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

using namespace std;
using LL = long long;
using Pii = pair<int, int>;
using Pll = pair<LL, LL>;

const int kN = 1001;

int tt, n, m, k, c[kN];

int main() {
  RF("medrcy");
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--; ) {
    cin >> n >> m >> k;
    fill_n(c + 1, n, m);
    for (int i = 1, x, y; i <= m; ++i) {
      cin >> x >> y;
      --c[x], --c[y];
    }
    bool f = 1;
    for (int i = 1, p = 1; i <= k; ++i) {
      vector<int> ans;
      for (int j = 1; j <= n; ++j) {
        if (c[j] < p) {
          ans.push_back(j);
        }
      }
      if (ans.empty()) {
        p = (p * n + n - 3) / (n - 2);
      } else {
        cout << i << ' ' << ans.size() << '\n';
        for (int j : ans) {
          cout << j << ' ';
        }
        cout << '\n';
        f = 0;
        break;
      }
    }
    if (f) {
      cout << "-1\n";
    }
  }
  return 0;
}
/*
4 11 2
1 3
1 3
1 3
4 3
1 3
1 3
4 3
1 3
4 1
1 3
1 3
2 1

1 10 1 8

2 3
1 3 4 
*/