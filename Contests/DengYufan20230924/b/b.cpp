// #include <fstream>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 5e3 + 1, kMod = 998244353, kInf = 1e9;
struct E {
  int p, d;
} e[kMaxN << 1];
struct V {
  int et, s;
  LL f[kMaxN];
} v[kMaxN];
int n, m;
LL fact[kMaxN] = {1}, _fact[kMaxN];

LL Pow(LL x, int y) {
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

void T(int x) {
  LL f[kMaxN] = {1}, g[kMaxN] = {};
  for (int o = v[x].et; o; o = e[o].p) {
    int i = e[o].d;
    T(i);
    for (int j = 0; j <= v[x].s; j++) {
      for (int k = 0; k <= v[i].s; k++) {
        g[j + k] = (g[j + k] + f[j] * v[i].f[k] % kMod * C(j + k, k) % kMod * C(v[x].s + v[i].s - j - k, v[i].s - k) % kMod) % kMod;
      }
    }
    v[x].s += v[i].s;
    copy(&g[0], &g[v[x].s] + 1, &f[0]), fill(&g[0], &g[v[x].s] + 1, 0);
  }
  v[x].s++;
  for (int i = 1; i <= v[x].s; i++) {
    f[i] = (f[i] + f[i - 1]) % kMod;
  }
  for (int i = 0; i <= v[x].s; i++) {
    v[x].f[i] = ((i ? f[i - 1] % kMod * m % kMod : 0) + (v[x].s - i) * (f[i] - (i ? f[i - 1] : 0) + kMod) % kMod) % kMod;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 2, x; i <= n; i++) {
    cin >> x;
    e[i] = {v[x].et, i}, v[x].et = i;
  }
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[n] = Pow(fact[n], kMod - 2);
  for (int i = n; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  T(1);
  cout << v[1].f[n];
  return 0;
}
