#include <fstream>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 16, kMaxL = 1 << kMaxN, kMod = 1e9 + 7;
int n, m, l, a[kMaxN], pop[kMaxL];
LL ans, fact[kMaxL], _fact[kMaxL];
LL f[kMaxN + 1][kMaxL];

void Add(LL &x, LL y) { x = (x + y) % kMod; }

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
  for (int i = 1; i < kMaxL; i++) {
    pop[i] = pop[i ^ (i & -i)] + 1;
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxL; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxL - 1] = Pow(fact[kMaxL - 1]);
  for (int i = kMaxL - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m, l = 1 << n;
  for (int i = 0; i < m; i++) {
    cin >> a[i];
  }
  f[m][0] = 1;
  for (int i = m; i >= 1; i--) {
    for (int s = 0; s < l; s++) {
      if (f[i][s]) {
        int c = l - a[i - 1] - s, t = s ^ l - 1, w;
        Add(f[i - 1][s], f[i][s]);
        for (; t && (w = t & -t) <= c + 1; t ^= w) {
          LL o = fact[c] * _fact[c - w + 1] % kMod * w % kMod;
          Add(f[i - 1][s | w], f[i][s] * o);
        }
      }
    }
  }
  for (int s = 0; s < l; s++) {
    LL o = f[0][s] * fact[l - s - 1] % kMod;
    Add(ans, pop[s] & 1 ? kMod - o : o);
  }
  cout << ans * l % kMod << '\n';
  return 0;
}
