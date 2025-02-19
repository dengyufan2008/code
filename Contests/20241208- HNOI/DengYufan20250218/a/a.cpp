#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 502, kMod = 998244353;
int n, a[kMaxN];
LL c[kMaxN][kMaxN];
LL inv[kMaxN][kMaxN];
LL g, f[kMaxN][kMaxN];  // 只考虑区间内的数, 左右端点活到最后的所有情况的概率的和

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL Win(int x, int y) {
  return a[x] * inv[x][y] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kMaxN; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % kMod;
    }
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i <= n + 1; i++) {
    for (int j = 0; j <= n + 1; j++) {
      inv[i][j] = Pow(a[i] + a[j]);
    }
  }
  for (int i = 0; i <= n; i++) {
    f[i][i + 1] = 1;
  }
  for (int o = 3; o <= n + 1; o++) {
    for (int l = 0, r; (r = l + o - 1) <= n + 1; l++) {
      for (int i = l + 1; i < r; i++) {
        LL w = c[r - l - 2][i - l - 1] * (Win(l, i) + Win(r, i)) % kMod;
        f[l][r] = (f[l][r] + f[l][i] * f[i][r] % kMod * w) % kMod;
      }
    }
  }
  g = 1;
  for (int i = 2; i < n; i++) {
    g = g * i % kMod;
  }
  g = Pow(g);
  for (int i = 1; i <= n; i++) {
    cout << f[0][i] * f[i][n + 1] % kMod * c[n - 1][i - 1] % kMod * g % kMod << '\n';
  }
  return 0;
}
