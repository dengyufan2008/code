#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 5001, kInf = 1e18;
LL n, k, a, b, ans, t[kMaxN], f[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k >> a >> b;
  for (LL i = 1; i <= n; i++) {
    cin >> t[i];
  }
  fill(&f[0][1], &f[kMaxN][0], kInf);
  for (LL i = 1; i <= n; i++) {
    f[i][0] = min(f[i][0], f[i - 1][k - 1] + a);
    for (LL j = 1; j < k; j++) {
      f[i][j] = min(f[i][j], f[i - 1][j - 1]);
    }
    for (LL j = 0; j < k; j++) {
      f[i][j] = min(f[i][j], f[i - 1][j] + min(j, k - j) * b + t[i]);
    }
  }
  ans = f[n][0];
  for (LL i = 1; i < k; i++) {
    ans = min(ans, f[n][i] + a);
  }
  cout << ans;
  return 0;
}
