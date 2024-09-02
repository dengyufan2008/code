#include <fstream>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 251, kMod = 998244353;
int n, a[kMaxN];
LL f[kMaxN][kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        f[i][j][k] = (f[i][j][k] + f[i - 1][j][k] + f[i][j - 1][k] + f[i][j][k - 1]) % kMod;
        f[i][j][k] = (f[i][j][k] - f[i - 1][j - 1][k] - f[i - 1][j][k - 1] - f[i][j - 1][k - 1]) % kMod;
        f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k - 1] + kMod) % kMod;
        if (a[i] == a[j] && a[j] == a[k]) {
          f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k - 1] + 1) % kMod;
        }
      }
    }
  }
  cout << f[n][n][n] << '\n';
  return 0;
}
