#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3e3 + 5, C = 3e3 + 5;
int n, c, a[N], b[N];
int ans;
int calc() {
  int maxn = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (i - j < 1 || i + j > n) {
        maxn = max(maxn, 2 * j - 1);
        break;
      }
      if (b[i - j] != b[i + j]) {
        maxn = max(maxn, 2 * j - 1);
        break;
      }
    }
    for (int j = 0; j <= n; j++) {
      if (i - j < 1 || i + j + 1 > n) {
        maxn = max(maxn, 2 * j);
        break;
      }
      if (b[i - j] != b[i + j + 1]) {
        maxn = max(maxn, 2 * j);
        break;
      }
    }
  }
  return maxn;
}
int main() {
  freopen("kanzenkankaku.in", "r", stdin);
  freopen("kanzenkankaku.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = a[i];
  }
  ans = max(ans, calc());
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      b[j] = a[j];
    }
    for (int j = i + 1; j <= n; j++) {
      int p = j;
      while (p > i) {
        if (b[p] < b[p - 1]) {
          swap(b[p], b[p - 1]);
          p--;
        } else {
          break;
        }
      }
      ans = max(ans, calc());
    }
  }
  cout << ans << '\n';
  return 0;
}