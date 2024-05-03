#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMaxM = 3001, kMod = 998244353;
int n, m, a[kMaxN];
LL w1, w2, inv[kMaxM * 2], f[kMaxM][kMaxM];
bool b[kMaxN];

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

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] ? w1 = (w1 + a[i]) % kMod : w2 = (w2 + a[i]) % kMod;
  }
  for (int i = 0; i <= m * 2; i++) {
    inv[i] = Pow(w1 + w2 + i - m);
  }
  for (int i = m; i >= 0; i--) {
    for (int j = m; j >= 0; j--) {
      if (i + j < m) {
        f[i][j] = (f[i + 1][j] + 1) * (w1 + i) % kMod * inv[i - j + m] % kMod;
        f[i][j] = (f[i][j] + f[i][j + 1] * (w2 - j) % kMod * inv[i - j + m]) % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (b[i]) {
      cout << (a[i] + f[0][0] * a[i] % kMod * Pow(w1)) % kMod << '\n';
    } else {
      cout << (a[i] - (m - f[0][0]) * a[i] % kMod * Pow(w2) % kMod + kMod) % kMod << '\n';
    }
  }
  return 0;
}
