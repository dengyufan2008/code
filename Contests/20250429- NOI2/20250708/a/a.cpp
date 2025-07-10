#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 8001, kMod = 998244353;
int t, o, n, k, a[kMaxN], c[kMaxN];
bool b[kMaxN];
LL f[kMaxN];
LL fact[kMaxN], _fact[kMaxN];

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

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void Solve() {
  fill(&b[1], &b[n] + 1, 0);
  fill(&c[1], &c[n] + 1, 0);
  fill(&f[1], &f[n] + 1, 0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i] && (b[a[i]] = 1);
  }
  for (int i = 1; i < n - k; i++) {
    for (int j = i; j <= n; j++) {
      c[i] += a[j] && a[j] <= i + k;
    }
  }
  f[1] = 1;
  for (int i = 1; i < n - k; i++) {
    if (!a[i]) {
      if (c[i] <= k) {
        Update(f[i + 1], f[i] * (k + 1 - c[i]));
      }
      for (int j = 1, g = 0; j - g <= k + 2 - c[i] && i + j <= n - k; j++) {
        if (!b[i + j + k]) {
          Update(f[i + j], f[i] * fact[k + 1 - c[i]] % kMod * _fact[k - j + 2 - c[i] + g]);
        }
        if (a[i + j] && a[i + j] > i + k) {
          break;
        }
        g += !!a[i + j];
      }
    } else if (a[i] <= i + k) {
      Update(f[i + 1], f[i]);
    } else {
      int p = a[i] - i - k, g = 0;
      bool u = 1;
      for (int j = 1; j < p; j++) {
        if (a[i + j] && a[i + j] > i + k) {
          u = 0;
        }
        g += !!a[i + j];
      }
      if (u && p - g <= k + 2 - c[i]) {
        Update(f[i + p], f[i] * fact[k + 1 - c[i]] % kMod * _fact[k - p + 2 - c[i] + g]);
      }
    }
  }
  int g = 0;
  for (int i = n - k; i <= n; i++) {
    g += !!a[i];
  }
  cout << f[n - k] * fact[k + 1 - g] % kMod << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> t >> o;
  while (t--) {
    Solve();
  }
  return 0;
}
