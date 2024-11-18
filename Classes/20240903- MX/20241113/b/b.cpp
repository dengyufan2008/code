#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 201, kMod = 1e9 + 7;
int t, n, a[kMaxN];
LL ans;
LL f[kMaxN][kMaxN];  // 三个子序列分别以 i, j, k 作为开头, 其中 i 一维滚动
LL g[kMaxN][kMaxN];  // 只有 j, k 被转移, i 还在原来的地方, 其中 i 一维滚动
bool e[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        static char c;
        cin >> c, e[i][j] = c == '1', f[i][j] = g[i][j] = 0;
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {  // 对 f_{i-1} 的 j, k 两维做前缀和
        for (int k = 1; k <= n; k++) {
          f[j][k] = (f[j][k] + f[j - 1][k] + f[j][k - 1] - f[j - 1][k - 1] + kMod) % kMod;
        }
      }
      for (int j = 1; j <= n; j++) {  // 将 i-1 加入 g 中, 同时在 i 一维做前缀和
        for (int k = 1; k <= n; k++) {
          if (a[j] == a[k] && e[a[i - 1]][a[j]]) {
            g[j][k] = (g[j][k] + f[j - 1][k - 1]) % kMod;
          }
        }
      }
      for (int j = 1; j <= n; j++) {  // 计算 f_i
        for (int k = 1; k <= n; k++) {
          if (a[i] == a[j] && a[i] == a[k]) {
            f[j][k] = (g[j][k] + 1) % kMod;
            ans = (ans + f[j][k]) % kMod;
          } else {
            f[j][k] = 0;
          }
        }
      }
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
