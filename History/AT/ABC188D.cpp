#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, c, s, p, ans;
map<int, LL> q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> c;
  for (int i = 1, x, y, z; i <= n; i++) {
    cin >> x >> y >> z;
    q[x] += z;
    q[y + 1] -= z;
  }
  for (auto it : q) {
    ans += min(s, c) * (it.first - p);
    s += it.second;
    p = it.first;
  }
  cout << ans << endl;
  return 0;
}
