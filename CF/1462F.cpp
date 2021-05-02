#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans, l[200001], r[200001];
vector<int> _l, _r;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    _l.clear(), _r.clear();
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> l[i] >> r[i];
      _l.push_back(l[i]), _r.push_back(r[i]);
    }
    ans = 1e9 + 1;
    sort(_l.begin(), _l.end()), sort(_r.begin(), _r.end());
    for (int i = 1, tmp1, tmp2; i <= n; i++) {
      tmp1 = upper_bound(_l.begin(), _l.end(), r[i]) - _l.begin();
      tmp2 = lower_bound(_r.begin(), _r.end(), l[i]) - _r.begin();
      ans = min(ans, n - tmp1 + tmp2);
    }
    cout << ans << endl;
  }
  return 0;
}
