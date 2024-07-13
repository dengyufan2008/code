#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 17, kMaxM = kMaxN * kMaxN, kMod = 998244353;
int n, m, e[1 << kMaxN], pop[1 << kMaxN];
LL f[1 << kMaxN], g[1 << kMaxN], pw[kMaxM];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  for (int s = 1; s < 1 << kMaxN; s++) {
    pop[s] = pop[s ^ (s & -s)] + 1;
  }
  cin >> n >> m;
  for (int i = 0, x, y; i < m; i++) {
    cin >> x >> y, x--, y--;
    e[1 << x] |= 1 << y, e[1 << y] |= 1 << x;
  }
  for (int s = 1; s < 1 << n; s++) {
    if (pop[s] == 1) {
      f[s] = g[s] = 2;
    } else {
      int _s = s ^ (s & -s), p = s, c = 0;
      for (int t = s;; t = t - 1 & s) {
        for (int q; p != t; p ^= q) {
          q = (p ^ t) & -(p ^ t);
          if (q & t) {
            c += pop[e[q] & (s ^ p)] - pop[e[q] & p];
          } else {
            c += pop[e[q] & p] - pop[e[q] & (s ^ p)];
          }
        }
        f[s] += pw[c], f[s] >= kMod && (f[s] -= kMod);
        if (!t) {
          break;
        }
      }
      g[s] = f[s];
      for (int _t = _s - 1 & _s;; _t = _t - 1 & _s) {
        int t = _t | (s & -s);
        g[s] -= g[t] * f[s ^ t] % kMod, g[s] < 0 && (g[s] += kMod);
        if (!_t) {
          break;
        }
      }
    }
  }
  cout << g[~(-1 << n)] * 499122177 % kMod << '\n';
  return 0;
}
