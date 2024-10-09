#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2001;
struct V {
  LL f, ff, g, gg;
  vector<int> e;
} v[kMaxN];
int n, p;
LL s[kMaxN], t[kMaxN], f[kMaxN];
LL fact[kMaxN], _fact[kMaxN];

LL Pow(LL x, int y) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % p;
    }
    x = x * x % p;
  }
  return ans;
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % p * _fact[x - y] % p;
}

void R(int fa, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != fa) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    R(x, i);
  }
}

void S(int x) {
  LL f = v[x].f;
  v[x].f = 1;
  for (int i : v[x].e) {
    S(i);
    v[x].f = v[x].f * (v[i].gg + v[i].g) % p;
    v[x].g = (v[x].g + v[i].g * v[i].ff) % p;
  }
  v[x].g = (v[x].g + v[x].f) % p;
}

void T(int x) {
  v[x].gg = (v[x].gg + v[x].g) % p, v[x].g = 0;
  for (int i : v[x].e) {
    T(i);
  }
  if (!v[x].e.empty()) {
    int m = v[x].e.size() - 1;
    s[0] = t[m] = 1;
    for (int i = 0; i < m; i++) {
      s[i + 1] = s[i] * v[v[x].e[i]].gg % p;
    }
    for (int i = m; i > 0; i--) {
      t[i - 1] = t[i] * v[v[x].e[i]].gg % p;
    }
    for (int i = 0; i <= m; i++) {
      v[v[x].e[i]].ff = (v[v[x].e[i]].ff + s[i] * t[i]) % p;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> p;
  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i % p;
  }
  _fact[n] = Pow(fact[n], p - 2);
  for (int i = n; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % p;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  R(0, 1);
  for (int i = 1; i < n; i++) {
    S(1), T(1), f[i] = v[1].f;
    for (int j = 1; j < i; j++) {
      f[i] = (f[i] - f[j] * C(i, j)) % p;
    }
    f[i] = (f[i] + p) % p;
  }
  for (int i = 1; i < n; i++) {
    cout << f[i] << " \n"[i == n - 1];
  }
  return 0;
}
