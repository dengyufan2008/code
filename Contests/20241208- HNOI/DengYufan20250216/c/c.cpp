#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e7 + 1, kMaxL = 9, kMod = 998244353;
LL n, m, k, w[kMaxN], ans[kMaxN * 2];
int o1[kMaxN], o2[kMaxN], mu[kMaxN];

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

void CalcOMuW() {
  static int u, prime[kMaxN], g[kMaxN];
  static bool b[kMaxN];
  static LL t[kMaxL], c[kMaxL][kMaxL];
  for (LL i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    if (j < kMaxN) {
      o1[j] = ++k;
    } else {
      o2[n / j] = ++k;
    }
  }
  for (int i = 0; i < kMaxL; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % kMod;
    }
  }
  b[1] = mu[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    if (!b[i]) {
      prime[++u] = i, g[i] = 1, mu[i] = -1;
    }
    static LL p;
    for (int j = 1; j <= u && (p = 1LL * i * prime[j]) < kMaxN; j++) {
      b[p] = 1;
      if (i % prime[j]) {
        g[p] = g[i] + 1, mu[p] = -mu[i];
      } else {
        g[p] = g[i], mu[p] = 0;
        break;
      }
    }
  }
  for (int i = 0; i < kMaxL; i++) {
    for (int j = 0; j < i; j++) {
      LL o = c[i][j] * Pow(i - j, m) % kMod;
      if (j & 1) {
        t[i] = (t[i] - o + kMod) % kMod;
      } else {
        t[i] = (t[i] + o) % kMod;
      }
    }
  }
  for (int i = 1; i < kMaxN; i++) {
    w[i] = t[g[i]];
  }
}

void Add(LL l, LL r, LL o) {
  l = l < kMaxN ? o1[l] : o2[n / l];
  r = r < kMaxN ? o1[r] : o2[n / r];
  ans[k - l + 1] = (ans[k - l + 1] + o) % kMod;
  ans[k - r] = (ans[k - r] - o + kMod) % kMod;
}

void Print() {
  const static LL kBase = 2024, kMod = 1e9 + 7;
  LL o = 0, w = 1;
  for (int i = 1; i <= k; i++) {
    w = w * kBase % kMod;
    o = (o + w * ans[i]) % kMod;
  }
  cout << o << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, CalcOMuW();
  for (int i = 2; 1LL * i * i <= n; i++) {
    if (!mu[i]) {
      continue;
    }
    for (int j = 1; 1LL * i * i * j * j <= n; j++) {
      LL _j = n / i / i / j;
      Add(j, _j, w[i]);
      Add(j, j, (_j - j) % kMod * w[i] % kMod);
    }
  }
  for (int i = k - 1; i >= 1; i--) {
    ans[i] = (ans[i] + ans[i + 1]) % kMod;
  }
  Print();
  return 0;
}
