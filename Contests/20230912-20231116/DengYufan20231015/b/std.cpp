#include <cstdio>
#include <iostream>
#define N 5000
using namespace std;
const long long inf = (long long)(1e18);
int read() {
  char c = 0;
  int sum = 0;
  while (c < '0' || c > '9') c = getchar();
  while ('0' <= c && c <= '9') sum = sum * 10 + c - '0', c = getchar();
  return sum;
}
int n, k, A, B, t[N + 1];
long long dp[N + 1][N + 1];
int main() {
  freopen("b.in", "r", stdin);
  freopen("b.ans", "w", stdout);
  n = read(), k = read(), A = read(), B = read();
  for (int i = 1; i <= n; ++i) t[i] = read();
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= n; ++j)
      dp[i][j] = inf;
  for (int i = 0; i <= n; ++i) dp[0][i] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + t[j] + 1ll * B * abs(i - j));
    if (i - k >= 0) {
      for (int j = 0; j <= n; ++j) dp[i][j] = min(dp[i][j], dp[i - k][j] + A);
      dp[i][0] = min(dp[i][0], 1ll * (i + k - 1) / k * A);
    }
    for (int j = 1; j <= n; ++j) dp[i][j] = min(dp[i][j], dp[i][j - 1]);
  }
  printf("%lld\n", dp[n][n]);
  return 0;
}
