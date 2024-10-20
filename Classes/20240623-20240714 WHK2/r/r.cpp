#include <fstream>
#define LL long long

using namespace std;

ifstream cin("r.in");
ofstream cout("r.out");

const int kMaxN = 51, kMod = 1e9 + 7;
int n, m, t, a[kMaxN][kMaxN];
LL f[kMaxN][kMaxN];

void Dp(int x, int y) {
  for (int i = 1; i < x; i++) {
    for (int j = 0; j <= x - i; j++) {
      f[i][j] = 0;
    }
  }
  f[x][0] = 1;
  for (int i = x; i >= 2; i--) {
    for (int j = 0; j <= x - i; j++) {
      for (int k = 1; k <= m; k++) {
        if (a[x][y] + t * (j + 1) > a[i - 1][k]) {
          f[i - 1][j + 1] = (f[i - 1][j + 1] + f[i][j]) % kMod;
        } else {
          f[i - 1][j] = (f[i - 1][j] + f[i][j]) % kMod;
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> t;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    LL ans = 0;
    for (int j = 1; j <= m; j++) {
      Dp(i, j);
      for (int k = 1; k <= i - 1; k++) {
        ans = (ans + f[1][k] * k) % kMod;
      }
    }
    for (int j = i + 1; j <= n; j++) {
      ans = ans * m % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}
