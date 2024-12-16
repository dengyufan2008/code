#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 2003, kMaxM = 2e5 + 1, kMaxL = 23, kMod = 1e9 + 7;
int n, s, g[kMaxN];
LL ans, f[kMaxN][kMaxL], fact[kMaxM], _fact[kMaxM];
pair<int, int> a[kMaxN];

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
  int x, y;
  bool h = 0, t = 0;
  cin >> x >> y >> n >> s;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
    if (a[i] == make_pair(1, 1)) {
      h = 1;
    } else if (a[i] == make_pair(x, y)) {
      t = 1;
    }
  }
  !h ? a[++n] = {1, 1}, s <<= 1 : 0;
  !t ? a[++n] = {x, y}, s <<= 1 : 0;
  sort(a + 1, a + n + 1);
  f[1][1] = Pow(C(x + y - 2, x - 1)), g[1] = 1;
  for (int i = 2; i <= n; i++) {
    g[i] = kMaxL;
  }
}

void Dp() {
  for (int i = 1; i <= n; i++) {
    for (int j = g[i]; j + 1 < kMaxL; j++) {
      f[i][j] = (f[i][j] - f[i][j + 1] + kMod) % kMod;
    }
    for (int j = i + 1; j <= n; j++) {
      if (a[i].second <= a[j].second) {
        g[j] = min(g[j], g[i] + 1);
        for (int k = g[i]; k + 1 < kMaxL; k++) {
          int x = a[j].first - a[i].first, y = a[j].second - a[i].second;
          f[j][k + 1] = (f[j][k + 1] + f[i][k] * C(x + y, x)) % kMod;
        }
      }
    }
  }
  for (int i = 1; i < kMaxL; i++) {
    s = s + 1 >> 1;
    ans = (ans + f[n][i] * s) % kMod;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxM - 1] = Pow(fact[kMaxM - 1]);
  for (int i = kMaxM - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  Init(), Dp();
  return 0;
}
