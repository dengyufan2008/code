#include <bitset>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 15, kMaxM = 5e4 + 1, kMod = 998244353, kMem = 512 << 20;
int o, n, m, pop[1 << kMaxN];
LL w[kMaxM][kMaxN + 1], fact[kMaxN + 1], _fact[kMaxN + 1];
vector<int> v[kMaxM];

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

void Init() {
  int k = 0, a[kMaxM], c[kMaxM], e[kMaxM], d[kMaxM] = {};
  bool b[kMaxM] = {}, t[kMaxM] = {};
  bitset<kMaxM> h[1 << kMaxN];
  e[0] = 0, cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    cin >> a[i], b[a[i]] = 1;
  }
  for (int i = 1; i <= m; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> e[i];
  }
  for (int i = 1; i <= m; i++) {
    v[i].clear();
    if (!b[i]) {
      for (int j = i; j; j = a[j]) {
        t[j] = 1, h[1 << k].set(c[j]);
      }
      k++;
    }
  }
  for (int s = 1; s < 1 << n; s++) {
    if (s != (s & -s)) {
      h[s] = h[s ^ (s & -s)] | h[s & -s];
    }
    v[h[s].count()].push_back(s);
  }
  for (int i = 1; i <= m; i++) {
    if (!t[i]) {
      for (int j = i; !t[j]; j = a[j]) {
        t[j] = 1, h[0].set(c[j]);
      }
      d[h[0].count()]++, h[0].reset();
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      w[i][j] = e[j + d[i]];
    }
  }
}

void Calc() {
  LL ans = 0, f[1 << kMaxN][kMaxN + 1] = {}, g[kMaxN + 1];
  f[0][0] = 1;
  for (int i = 1; i <= m; i++) {
    if (v[i].empty()) {
      ans = (ans + w[i][0] * fact[n]) % kMod;
    } else {
      g[0] = fact[n];
      for (int j = 1; j <= n; j++) {
        g[j] = 0;
      }
      for (int s : v[i]) {
        LL r = fact[pop[s] - 1];
        for (int t = s; t < 1 << n; t = t + 1 | s) {
          for (int j = 1; j <= n; j++) {
            if (f[t ^ s][j - 1]) {
              f[t][j] = (f[t][j] + f[t ^ s][j - 1] * r) % kMod;
            }
          }
        }
      }
      for (int s : v[i]) {
        for (int t = s; t < 1 << n; t = t + 1 | s) {
          for (int j = 1; j <= n; j++) {
            if (f[t][j]) {
              g[j] = (g[j] + f[t][j] * fact[n - pop[t]]) % kMod;
              f[t][j] = 0;
            }
          }
        }
      }
      for (int j = n; j >= 0; j--) {
        for (int k = j + 1; k <= n; k++) {
          g[j] = (g[j] - g[k] * C(k, j)) % kMod;
        }
        g[j] < 0 && (g[j] += kMod);
        ans = (ans + w[i][j] * g[j]) % kMod;
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  __asm__("movq %0, %%rsp\n" ::"r"((char *)malloc(kMem) + kMem));
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int s = 1; s < 1 << kMaxN; s++) {
    pop[s] = pop[s ^ (s & -s)] + 1;
  }
  fact[0] = 1;
  for (int i = 1; i <= kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN] = Pow(fact[kMaxN]);
  for (int i = kMaxN; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> o;
  while (o--) {
    Init(), Calc();
  }
  exit(0);
}
