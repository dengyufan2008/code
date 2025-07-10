#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5001, kMod = 1e9 + 7;
int n, a[kMaxN], b[kMaxN];
LL ans, f0[kMaxN], f1[kMaxN], g0[kMaxN], g1[kMaxN];
LL inv[kMaxN], fact[kMaxN], _fact[kMaxN];

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
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

LL _C(int x, int y) {
  return _fact[x] * fact[y] % kMod * fact[x - y] % kMod;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  inv[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    inv[i] = kMod - kMod / i * inv[kMod % i] % kMod;
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }

  f0[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= a[0]; j++) {
      for (int k = 0; k <= a[i]; k++) {
        Update(g0[j + k], f0[j] * C(a[i], k));
        Update(g1[j + k], (f1[j] + f0[j] * min(k, b[i])) % kMod * C(a[i], k));
      }
    }
    a[0] += a[i];
    for (int j = 0; j <= a[0]; j++) {
      f0[j] = g0[j], g0[j] = 0;
      f1[j] = g1[j], g1[j] = 0;
    }
  }
  for (int i = 0; i <= a[0]; i++) {
    Update(ans, (f0[i] * a[0] - f1[i]) % kMod * _C(a[0], i) % kMod * inv[a[0] - i]);
  }

  fill(&f0[0], &f0[a[0]] + 1, 0);
  fill(&f1[0], &f1[a[0]] + 1, 0);
  a[0] = 0;

  f0[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = b[0]; j <= a[0]; j++) {
      for (int k = b[i]; k <= a[i]; k++) {
        Update(g0[j + k], f0[j] * C(a[i], k));
        Update(g1[j + k], (f1[j] + f0[j] * min(k, b[i])) % kMod * C(a[i], k));
      }
    }
    a[0] += a[i], b[0] += b[i];
    for (int j = b[0]; j <= a[0]; j++) {
      f0[j] = g0[j], g0[j] = 0;
      f1[j] = g1[j], g1[j] = 0;
    }
  }
  for (int i = b[0]; i <= a[0]; i++) {
    Update(ans, -(f0[i] * a[0] - f1[i]) % kMod * _C(a[0], i) % kMod * inv[a[0] - i]);
  }

  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
