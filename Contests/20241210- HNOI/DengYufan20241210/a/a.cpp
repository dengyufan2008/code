#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 1, kMaxM = 401, kMod = 998244353;
struct V {
  LL f[2];
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m, k, s, _s, _ms;
LL ans, f[kMaxM];
LL fact[kMaxN], _fact[kMaxN], s2[kMaxM][kMaxM];

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

void Init(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    Init(x, i);
  }
}

void Dp(int x) {
  v[x].f[0] = v[x].b ? 0 : s, v[x].f[1] = m - s;
  for (int i : v[x].e) {
    Dp(i);
    LL f0 = (v[i].f[0] * (1 - _s + kMod) + v[i].f[1]) % kMod;
    v[x].f[0] = v[x].f[0] * f0 % kMod;
    LL f1 = (v[i].f[0] + v[i].f[1] * (1 - _ms + kMod)) % kMod;
    v[x].f[1] = v[x].f[1] * f1 % kMod;
  }
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
  s2[0][0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    for (int j = 1; j <= i; j++) {
      s2[i][j] = (s2[i - 1][j - 1] + s2[i - 1][j] * j) % kMod;
    }
  }
  cin >> n >> m >> k >> s;
  for (int i = 1, x; i <= s; i++) {
    cin >> x, v[x].b = 1;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Init(0, 1);
  for (s = 0; s <= k; s++) {  // i 个 0
    _s = Pow(s), _ms = Pow(m - s), Dp(1);
    f[s] = (v[1].f[0] + v[1].f[1]) % kMod;
  }
  for (int i = 1; i <= k; i++) {  // i 个 1, j 个 0
    for (int j = 0; j <= k; j++) {
      f[j] = (f[j] - f[j + 1] + kMod) % kMod;
    }
    LL g = f[0] * C(m, i) % kMod;          // 每个方案的贡献是 {颜色数 \choose s}
    LL h = g * s2[k][i] % kMod * fact[i];  // 每个方案的贡献是 {颜色数^k}
    ans = (ans + h) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
