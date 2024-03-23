#include <fstream>
#include <vector>

using namespace std;

ifstream cin("medrcy.in");
ofstream cout("medrcy.out");

const int kMaxN = 1001, kMaxM = 3001;
int t, n, m, k, d[kMaxN];
pair<int, int> a[kMaxM];
vector<int> ans;

namespace Sub1 {

int main() {
  for (int i = 1; i <= n; i++) {
    if (m - d[i] < 2) {
      ans.push_back(i);
    }
  }
  if (k >= 2 && !ans.empty()) {
    cout << 2 << ' ' << ans.size() << " \n";
    for (int i : ans) {
      cout << i << ' ';
    }
    cout << '\n';
    return 0;
  }
  cout << -1 << " \n";
  return 0;
}
}  // namespace Sub1

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
      cin >> a[i].first >> a[i].second;
      if (a[i].first > a[i].second) {
        swap(a[i].first, a[i].second);
      }
    }
    ans.clear();
    for (int i = 1; i <= n; i++) {
      d[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
      d[a[i].first]++, d[a[i].second]++;
    }
    bool shit = 0;
    for (int j = 1; j <= k; j++) {
      for (int i = 1; i <= n; i++) {
        if (m - d[i] < j) {
          ans.push_back(i);
        }
      }
      if (!ans.empty()) {
        cout << j << ' ' << ans.size() << " \n";
        for (int i : ans) {
          cout << i << ' ';
        }
        cout << '\n';
        shit = 1;
        break;
      }
    }
    if (!shit) {
      cout << "-1 \n";
    }
  }
  return 0;
}
