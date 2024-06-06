#include <bits/stdc++.h>
#define base 233
#define mod 998244353
#define ull unsigned int
#define N 1000005
#define K 1005
using namespace std;

int n, m, k;
int s1[N], s2[N];
long long hash1[N], hash2[N], pw[N];
int dp[K][K << 1], tr[K][K << 1];

bool check(int x, int y, int len) {
  if ((x + len - 1 > n) || (y + len - 1 > m)) return 0;
  if ((hash1[x + len - 1] - hash1[x - 1] * pw[len] % mod + mod) % mod == (hash2[y + len - 1] - hash2[y - 1] * pw[len] % mod + mod) % mod) {
    return 1;
  }
  return 0;
}

int sol(int x, int y) {
  int l = 0, r = N;
  while (l + 1 < r) {
    int mid = l + r >> 1;
    if (check(x, x + y, mid))
      l = mid;
    else
      r = mid;
  }
  return l;
}

void print(int x, int y) {
  if (!x) return;
  int z = tr[x][y];
  print(x - 1, z);
  int id = dp[x - 1][z] + z - k;
  if (z == y) {
    printf("REPLACE %d ", id + 1);
    cout << (char)(s2[id + 1] - 1 + 'a') << endl;
  }
  if (z == y + 1) {
    printf("DELETE %d\n", id + 1);
  }
  if (z == y - 1) {
    printf("INSERT %d ", id + 1);
    cout << (char)(s2[id + 1] - 1 + 'a') << endl;
  }
}
void DP() {
  for (int i = 0; i <= k; ++i)
    for (int j = 0; j <= (k << 1); ++j) dp[i][j] = tr[i][j] = -1;
  dp[0][k] = 0;
  int ans = -1;
  for (int i = 0; i <= k; ++i) {
    for (int j = 0; j <= (k << 1); ++j) {
      if (dp[i][j] == -1) continue;
      dp[i][j] = dp[i][j] + sol(dp[i][j] + 1, j - k);
      if ((dp[i][j] + 1 <= n) && (dp[i + 1][j] + 1 + j - k <= m) && dp[i + 1][j] < dp[i][j] + 1) {
        dp[i + 1][j] = dp[i][j] + 1;
        tr[i + 1][j] = j;
      }
      if ((j != (1 << k)) && (dp[i + 1][j] + 1 + j - k <= m) && dp[i + 1][j + 1] < dp[i][j]) {
        dp[i + 1][j + 1] = dp[i][j];
        tr[i + 1][j + 1] = j;
      }
      if ((dp[i][j] + 1 <= n) && (j != 0) && dp[i + 1][j - 1] < dp[i][j] + 1) {
        dp[i + 1][j - 1] = dp[i][j] + 1;
        tr[i + 1][j - 1] = j;
      }
    }
    if (dp[i][k - n + m] == n) {
      ans = i;
      break;
    }
  }
  if (ans == -1) {
    printf("NO\n");
    return;
  }
  printf("YES\n%d\n", ans);
  print(ans, k - n + m);
}

void solve() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    char c;
    cin >> c;
    s1[i] = c - 'a' + 1;
  }
  for (int i = 1; i <= m; ++i) {
    char c;
    cin >> c;
    s2[i] = c - 'a' + 1;
  }
  for (int i = 1; i <= n; ++i) hash1[i] = (hash1[i - 1] * base + s1[i]) % mod;
  for (int i = 1; i <= m; ++i) hash2[i] = (hash2[i - 1] * base + s2[i]) % mod;
  if (k < abs(n - m)) {
    printf("NO\n");
    return;
  }
  DP();
}
signed main() {
  freopen("c.in", "r", stdin);
  freopen("c.ans", "w", stdout);
  int T;
  scanf("%d", &T);
  pw[0] = 1;
  for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * base % mod;
  while (T--) solve();
  return 0;
}
