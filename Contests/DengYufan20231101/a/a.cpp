#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e6 + 1;
int n, m, a[kMaxN][4], lg[16];
LL ans, mx[16], s[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < 4; i++) {
    lg[1 << i] = i;
  }
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      s[i] += a[i][j];
    }
    for (int j = 0; j < (1 << m); j++) {
      LL w = s[i];
      for (int k = j; k; k ^= (k & -k)) {
        w -= a[i][lg[k & -k]] << 1;
      }
      mx[j] = max(mx[j], w);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < (1 << m); j++) {
      LL w = s[i];
      for (int k = j; k; k ^= (k & -k)) {
        w -= a[i][lg[k & -k]] << 1;
      }
      ans = max(ans, w + mx[~(-1 << m) ^ j]);
    }
  }
  cout << ans;
  return 0;
}
