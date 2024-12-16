// 正确性不会证
#include <algorithm>
#include <fstream>
#define PII pair<int, int>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 1;
int t, n, m, k;
PII a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
    }
    if (k <= a[1].first) {
      cout << "YES\n";
      continue;
    } else if (n == 1 || k > a[1].first + a[1].second) {
      cout << "NO\n";
      continue;
    }
    sort(a + 2, a + n + 1, [](PII i, PII j) {
      return i.first + i.second < j.first + j.second;
    });
    m = a[2].first;
    for (int i = 3; i <= n; i++) {
      m = max(m, min(m, a[i].first) + a[i].second);
      m = max(m, a[i].first);
      m = max(m, a[i - 1].first + a[i - 1].second);
    }
    if (m >= k - a[1].second) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
