// 自己想的做法, 枚举 i 算 i > j, p_i < p_j 的排列数
// 显然可以莫队线段树矩阵乘法做到 $O(4^3 n \sqrt n \log n)$
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 2e5 + 1, kMod = 1e9 + 7;
int n, a[kMaxN], c[kMaxN], s[kMaxN];
LL ans, f[kMaxN][4];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], c[a[i]]++;
  }
  for (int i = n, j = 0; i >= 1; i--) {
    j += c[i], s[i] = j, j--, c[i] = 0;
  }
  f[n][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = n; j > a[i]; j--) {
      f[j - 1][0] = f[j][0] * s[j] % kMod;
      f[j - 1][1] = (f[j][0] * c[j] + f[j][1]) % kMod * (s[j] - 1) % kMod;
      f[j - 1][2] = (f[j][0] * c[j] + f[j][1] + f[j][2] * s[j]) % kMod;
      f[j - 1][3] = 0;
    }
    for (int j = a[i]; j >= 1; j--) {
      f[j - 1][0] = f[j][0] * (s[j] - 1) % kMod;
      f[j - 1][1] = (f[j][0] * c[j] + f[j][1]) % kMod * (s[j] - 2) % kMod;
      f[j - 1][2] = (f[j][0] * c[j] + f[j][1] + f[j][2] * (s[j] - 1)) % kMod;
      f[j - 1][3] = (f[j][2] + f[j][3] * s[j]) % kMod;
    }
    ans = (ans + f[0][3]) % kMod, c[a[i]]++;
  }
  cout << ans << '\n';
  return 0;
}
