#include <fstream>
#define LL long long

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
int o, n, m, k, d, h, t, v, a[kMaxN], b[kMaxN], c[kMaxN], q[kMaxN], nt[kMaxN];
LL ans, fact[kMaxN], _fact[kMaxN];
bool w[kMaxN];

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
  cin >> o;
  while (o--) {
    h = 1, t = v = ans = 0;
    for (int i = 1; i < kMaxN; i++) {
      c[i] = w[i] = q[i] = 0;
    }
    cin >> n >> m >> k >> d;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
      cin >> b[i], w[b[i]] = 1;
    }
    for (int i = k; i >= 1; i--) {
      k -= w[i];
    }
    if (d > k) {
      cout << 0 << '\n';
      continue;
    }
    for (int i = 2, j; i <= m; i++) {
      for (j = nt[i - 1]; j && b[j + 1] != b[i]; j = nt[j]) {
      }
      nt[i] = b[j + 1] == b[i] ? j + 1 : 0;
    }
    for (int i = 1, j = 0, k = 0; j <= n; i++) {
      if (h <= t && i > q[h]) {
        k = nt[m], h = t - nt[m] + 1;
        for (; i < q[h]; i++) {
          v -= !w[a[i]] && !--c[a[i]];
        }
      }
      while (j <= n && k < m) {
        for (j++; j <= n && !w[a[j]]; j++) {
          v += !c[a[j]]++;
        }
        if (j <= n) {
          for (; k && b[k + 1] != a[j]; k = nt[k]) {
          }
          if (b[k + 1] == a[j]) {
            h = t - k + 1, q[++t] = j, k++;
            for (; i <= q[h - 1]; i++) {
              v -= !w[a[i]] && !--c[a[i]];
            }
          } else {
            h = t + 1;
            for (; i <= j; i++) {
              v -= !w[a[i]] && !--c[a[i]];
            }
          }
        }
      }
      if (h <= t) {
        for (; i < q[h]; i++) {
          v -= !w[a[i]] && !--c[a[i]];
        }
      }
      if (k == m && v <= d) {
        ans = (ans + C(::k - v, d - v)) % kMod;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
