#include <fstream>
#define LL long long

using namespace std;

ifstream cin("nene.in");
ofstream cout("nene.out");

const int kMaxN = 5e5 + 1, kMod = 1e9 + 7;
int n, m, a[kMaxN], d[kMaxN];
LL ans, f[kMaxN], fact[kMaxN * 2], _fact[kMaxN * 2];

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

LL C(int x, int y) {
  if (y < 0 || y > x) {
    return 0;
  }
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN * 2; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN * 2 - 1] = Pow(fact[kMaxN * 2 - 1]);
  for (int i = kMaxN * 2 - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m;
  for (int i = 1, x; i <= m; i++) {
    cin >> x, a[i] = x;
    for (int j = x + 1; j <= n; j += j & -j) {
      a[i] += d[j];
    }
    for (int j = x; j >= 1; j -= j & -j) {
      d[j]++;
    }
  }
  f[n] = 1;
  for (int i = m + 1; i < n; i++) {
    f[i] = C(n * 2 - i - m - 1, n - i) - C(n * 2 - i - m - 1, n - i - 1);
    f[i] = (f[i] + kMod) % kMod;
  }
  for (int i = m, p = 0; i >= 1; i--) {
    if (a[i] != i) {
      if (!p) {
        LL w = 0;
        for (int j = a[i]; j <= n; j++) {
          w = (w + f[j]) % kMod;
        }
        fill(&f[1], &f[n] + 1, 0);
        f[a[i] - 1] = w, p = a[i] - 1;
      } else if (p >= a[i]) {
        f[a[i] - 1] = f[p], f[p] = 0, p = a[i] - 1;
      } else {
        f[p] = 0;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = (ans + f[i]) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
