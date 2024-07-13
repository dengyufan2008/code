#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, _a, ans, a[2001];

int Gcd(int x, int y) {
  return y ? Gcd(y, x % y) : x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    _a = ans = 0;
    cin >> n;
    for (int i = 1, tmp; i <= n; i++) {
      cin >> tmp;
      if (tmp & 1) {
        a[++_a] = tmp;
      } else {
        ans++;
      }
    }
    ans = n * ans - (ans + 1) * ans / 2;
    for (int i = 1; i <= _a; i++) {
      for (int j = i + 1; j <= _a; j++) {
        ans += Gcd(a[i], a[j]) > 1;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
