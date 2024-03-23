#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const LL kMaxN = 1 << 3, kMaxV = 1 << 3, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
int n, m, k, r[kMaxV];
LL ans, f[kMaxV], g[kMaxN], h[kMaxN], fact[kMaxN << 1] = {1}, _fact[kMaxN << 1];

LL Pow(LL x, int y = kMod - 2) {
  y = (y + kMod - 1) % (kMod - 1);
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

const LL kInvMaxV = Pow(kMaxV);

LL C(int x, int y) { return x >= y ? fact[x] * _fact[y] % kMod * _fact[x - y] % kMod : 0; }

void FWT(LL f[]) {
  for (int i = 0; i < kMaxV; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < kMaxV; i <<= 1) {
    for (int j = 0; j < kMaxV; j += i + i) {
      for (int k = j; k < j + i; k++) {
        LL f0 = f[k], f1 = f[k + i];
        f[k] = (f0 + f1) % kMod;
        f[k + i] = (f0 - f1 + kMod) % kMod;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kMaxV; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? kMaxV >> 1 : 0);
  }
  for (int i = 1; i < kMaxN << 1; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[(kMaxN << 1) - 1] = Pow(fact[(kMaxN << 1) - 1]);
  for (int i = (kMaxN << 1) - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m >> k;
  for (int i = 1, x; i <= m; i++) {
    cin >> x;
    f[x]++;
  }
  FWT(f);
  for (int i = 0; i < kMaxV; i++) {
    f[i] = (kMod - f[i] + m) % kMod * kInv2 % kMod;
  }
  g[0] = Pow(2, m - k) - 1;
  for (int i = 1; i < kMaxN; i++) {
    LL _g = (kMod - g[i - 1] + Pow(2, m - k - 1) * C(i - 1 + m - k, i) % kMod) % kMod;
    g[i] = (g[i - 1] + _g * 2 % kMod) % kMod;
  }
  for (int i = 0; i < kMaxN; i++) {
    h[i] = ((k & 1 ? kMod - g[k - i] : g[k - i]) * Pow(2, i) % kMod + (k & 1 ? 1 : kMod - 1)) % kMod;
  }
  for (int i = 0; i < kMaxV; i++) {
    f[i] = h[f[i]];
  }
  FWT(f);
  for (int i = 0; i < kMaxV; i++) {
    f[i] = f[i] * kInvMaxV % kMod;
  }
  // for (int i = 0; i < 1 << n; i++) {
  //   ans ^= f[i] + i;
  // }
  // cout << ans;
  for (int i = 0; i < 1 << n; i++) {
    cout << f[i] << ' ';
  }
  return 0;
}
