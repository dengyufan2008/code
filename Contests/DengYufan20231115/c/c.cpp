#include <iostream>
#include <set>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 2e4 + 1;
int n, m, a[kMaxN], d[kMaxN], ans[kMaxN];
set<int> s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    s.clear(), s.insert(0), s.insert(n + 1);
    for (int j = 1; j <= n; j++) {
      if (!ans[j]) {
        d[j] = 1, s.insert(j);
      } else {
        d[j] = 0;
      }
    }
    for (int j = n; j >= 1; j--) {
      if (!ans[a[j]]) {
        auto o = s.find(a[j]);
        if (d[a[j]]) {
          auto p = o, q = o;
          d[*--p] = 0, d[*++q] = 0;
          ans[a[j]] = i;
        }
        s.erase(o);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
