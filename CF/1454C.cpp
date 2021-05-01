#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans;

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> a(n);
    for (auto &it : a) {
      cin >> it;
    }
    vector<int> res(n + 1, 1);
    n = unique(a.begin(), a.end()) - a.begin();
    a.resize(n);
    for (int i = 0; i < n; i++) {
      res[a[i]]++;
    }
    res[a[0]] -= 1;
    res[a[n - 1]] -= 1;
    ans = 1e9 + 1;
    for (int i = 0; i < n; ++i) {
      ans = min(ans, res[a[i]]);
    }
    cout << ans << endl;
  }
  return 0;
}
