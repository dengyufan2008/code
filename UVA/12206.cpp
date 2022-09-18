#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

LL n, m, l, r, ans;
pair<unsigned LL, LL> a[40001];
string s;

unsigned LL Pow(unsigned LL a, LL x) {
  unsigned LL ans = 1;
  for (LL i = 1; i <= x; i <<= 1) {
    if (i & x) {
      ans = ans * a;
    }
    a = a * a;
  }
  return ans;
}

LL C(LL x) {
  unsigned LL h = 0, t = Pow(26, x - 1);
  LL ans = -1;
  for (LL i = 0; i < x; i++) {
    h = h * 26 + s[i] - 'a';
  }
  a[1] = {h, 0};
  for (LL i = x; i < n; i++) {
    a[i - x + 2] = {h = (h - t * (s[i - x] - 'a')) * 26 + s[i] - 'a', i - x + 1};
  }
  sort(a + 1, a + n - x + 2);
  for (LL i = 1, j = 0; i <= n - x + 1; i++) {
    if (a[i].first == a[i - 1].first) {
      if (++j >= m) {
        ans = max(ans, a[i].second);
      }
    } else {
      j = 1;
    }
  }
  return ans;
}

int main() {
  cin >> m;
  while (m) {
    cin >> s;
    n = s.size(), l = 0, r = n, ans = -1;
    while (l <= r) {
      LL mid = l + r >> 1, c = C(mid);
      if (c >= 0) {
        l = mid + 1, ans = c;
      } else {
        r = mid - 1;
      }
    }
    if (ans >= 0) {
      cout << r << ' ' << ans << '\n';
    } else {
      cout << "none\n";
    }
    cin >> m;
  }
  return 0;
}
