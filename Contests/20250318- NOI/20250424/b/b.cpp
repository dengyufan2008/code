#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e6 + 1;
struct E {
  int mx, l;
};
int t, n, a, b, p[kMaxN];
vector<E> v1, v2;
vector<pair<int, int>> ans;

void Solve() {
  for (int m = n; m;) {
    int i = v1.size(), l = 0;
    for (; i && (v2.empty() || v1[i - 1].mx > v2.back().mx) && (i == v1.size() || v1[i].mx > v1[i - 1].mx); i--) {
      l += v1[i - 1].l;
    }
    if (i && !v2.empty() && v1[i - 1].mx == v2.back().mx - v2.back().l) {
      ans.push_back({1, l + v1[i - 1].l});
      v2.back().l += v1[i - 1].l;
      v2.insert(v2.end(), v1.begin() + i, v1.end());
      v1.erase(v1.begin() + i - 1, v1.end());
    } else if (i < v1.size()) {
      ans.push_back({1, l});
      v2.insert(v2.end(), v1.begin() + i, v1.end());
      v1.erase(v1.begin() + i, v1.end());
    } else {
      cout << -1 << '\n';
      return;
    }
    while (!v2.empty() && v2.back().mx == m) {
      ans.push_back({2, v2.back().l});
      m -= v2.back().l;
      v2.pop_back();
    }
  }
  cout << ans.size() << '\n';
  for (auto i : ans) {
    cout << i.first << ' ' << i.second << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) {
      cin >> p[i];
    }
    v1.clear(), v2.clear(), ans.clear();
    for (int i = 1, j = 1; i <= n; i = j = j + 1) {
      for (; j < n && p[j] + 1 == p[j + 1]; j++) {
      }
      v1.push_back({p[j], j - i + 1});
    }
    reverse(v1.begin(), v1.end());
    Solve();
  }
  return 0;
}
