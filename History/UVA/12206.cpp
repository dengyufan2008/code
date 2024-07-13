#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

LL n, m, l, r, ans1, ans2;
unsigned LL d[40001] = {1}, t[40001];
pair<unsigned LL, LL> a[40001];
string s;

LL C(LL x) {
  LL ans = -1;
  for (LL i = 0; i + x - 1 < n; i++) {
    a[i] = {t[i + x - 1] - t[i - 1] * d[x], i};
  }
  sort(a, a + n - x + 1);
  for (LL i = 0, j = 0; i < n - x + 1; i++) {
    j = (a[i].first == a[i - 1].first) * j + 1;
    if (j >= m) {
      ans = max(ans, a[i].second);
    }
  }
  return ans;
}

int main() {
  for (LL i = 1; i <= 40000; i++) {
    d[i] = d[i - 1] * 131;
  }
  cin >> m;
  while (m) {
    cin >> s;
    n = s.size(), l = 1, r = n, ans2 = -1;
    for (LL i = 0; i < n; i++) {
      t[i] = t[i - 1] * 131 + s[i];
    }
    while (l <= r) {
      LL mid = l + r >> 1, c = C(mid);
      if (c >= 0) {
        l = mid + 1, ans1 = mid, ans2 = c;
      } else {
        r = mid - 1;
      }
    }
    if (ans2 >= 0) {
      cout << ans1 << ' ' << ans2 << '\n';
    } else {
      cout << "none\n";
    }
    cin >> m;
  }
  return 0;
}
