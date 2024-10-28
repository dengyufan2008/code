#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("wormhole.in");
ofstream cout("wormhole.out");

const int kMaxN = 2e3 + 1, kMaxM = 1e3 + 1, kMod = 998244353;
const int kBase1 = 15552, kBase2 = 715876, kMod1 = 998244353, kMod2 = 1e9 + 7;
struct H {
  int s;
  LL hash1, hash2;
  bool operator<(const H &h) const {
    if (s != h.s) {
      return s < h.s;
    } else if (hash1 != h.hash1) {
      return hash1 < h.hash1;
    }
    return hash2 < h.hash2;
  }
  bool operator==(const H &h) const {
    return s == h.s && hash1 == h.hash1 && hash2 == h.hash2;
  }
};
int n, m, a[kMaxM][kMaxN], l[kMaxN];
LL k, ans, f[kMaxN], fact[kMaxN], _fact[kMaxN], pw[kMaxN];
vector<H> h;

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

int GetRoot(int x) {
  return l[x] == x ? x : l[x] = GetRoot(l[x]);
}

void Merge(LL f[kMaxN], LL g[kMaxN], LL w) {
  LL h[kMaxN] = {};
  for (int i = 1; i <= n; i++) {
    LL t = Pow(i, (kMod - 1 - w % (kMod - 1)) % (kMod - 1));
    for (int j = i; j <= n; j += i) {
      h[j] = (h[j] + f[i] * g[j / i] % kMod * t) % kMod;
    }
  }
  copy(&h[1], &h[n] + 1, &f[1]);
}

void Init() {
  static LL g[kMaxN];
  fill(&f[1], &f[n] + 1, 1), fill(&g[1], &g[n] + 1, 1);
  for (LL i = 1; i <= k; i <<= 1) {
    if (k - 1 & i) {
      Merge(f, g, i);
    }
    Merge(g, g, i);
  }
  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[n] = Pow(fact[n]);
  for (int i = n; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  for (int i = 1; i <= n; i++) {
    pw[i] = Pow(i, (k - 1) % (kMod - 1));
  }
}

LL Calc(int x, int s) {
  static LL g[kMaxN] = {1}, d[kMaxN];
  for (int i = 1; i <= x; i++) {
    d[i] = Pow(s, (i + k - 1) % (kMod - 1));
  }
  for (int i = 1; i <= x; i++) {
    g[i] = 0;
    for (int j = 0; j < i; j++) {
      LL w = g[j] * f[i - j] % kMod * fact[i - 1] % kMod * _fact[j];
      g[i] = (g[i] + w % kMod * pw[i - j] % kMod * d[i - j]) % kMod;
    }
  }
  return g[x];
}

void Hash(int x) {
  int d[kMaxN];
  static vector<int> w, v;
  static queue<int> q;
  fill(&d[1], &d[n] + 1, -1), d[x] = 0;
  w.clear(), w.push_back(x), v.clear();
  for (int i = 1; i <= m; i++) {
    for (int j : w) {
      q.push(j);
    }
    for (; !q.empty(); q.pop()) {
      int y = q.front(), z = a[i][y];
      if (d[z] == -1) {
        d[z] = w.size(), w.push_back(z), q.push(z);
      }
      v.push_back(d[z]);
    }
  }
  h.push_back({(int)w.size(), 0, 0});
  for (int i : v) {
    h.back().hash1 = (h.back().hash1 * kBase1 + i) % kMod1;
    h.back().hash2 = (h.back().hash2 * kBase2 + i) % kMod2;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    l[i] = i;
  }
  for (int i = 1, x, y, z; i <= n * m; i++) {
    cin >> x >> y >> z;
    a[z][x] = y;
    if (GetRoot(x) != GetRoot(y)) {
      l[GetRoot(x)] = GetRoot(y);
    }
  }
  Init();
  for (int i = 1; i <= n; i++) {
    l[i] == i ? Hash(i) : void();
  }
  sort(h.begin(), h.end()), ans = 1;
  for (int i = 0, j = 0; i < h.size(); i = j) {
    for (; j < h.size() && h[i] == h[j]; j++) {
    }
    ans = ans * Calc(j - i, h[i].s) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
