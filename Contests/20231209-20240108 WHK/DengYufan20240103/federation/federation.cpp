#include <fstream>
#define LL long long

using namespace std;

ifstream cin("federation.in");
ofstream cout("federation.out");

const int kMaxN = 1 << 20, kMod = 998244353, kG = 3;
int n, m, r[kMaxN];
LL ans, f[kMaxN];

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
  cin >> m;
  n = 1 << m, f[0] = ans = 1;
  for (int i = 1; i < n; i++) {
    cin >> f[i];
    f[0] = (f[0] + f[i]) % kMod;
    f[i] = (kMod - f[i]) % kMod;
  }
  for (int i = 0; i < n; i++) {
    r[i] = r[i >> 1] >> 1 | (i & 1) << m - 1;
  }
  for (int i = 0; i < n; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    LL g = Pow(kG, (kMod - 1) / (i + i));
    for (int j = 0; j < n; j += i + i) {
      LL w = 1;
      for (int k = j; k < j + i; k++) {
        LL f0 = f[k], f1 = f[k + i];
        f[k] = (f0 + f1 * w % kMod + kMod) % kMod;
        f[k + i] = (f0 - f1 * w % kMod + kMod) % kMod;
        w = w * g % kMod;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    ans = ans * f[i] % kMod;
  }
  cout << ans << '\n';
  return 0;
}
