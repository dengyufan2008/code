#include <fstream>
#include <map>
#define LL long long

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 2e3 + 1, kMod = 998244353;
struct V {
  int x1, x2, y1, y2;
  int a1, a2, b1, b2;
} v[kMaxN];
int n, p, q, a1[kMaxN << 1], a2[kMaxN << 1];
int c[kMaxN << 1][kMaxN << 1];
LL ans, w[kMaxN], fact[kMaxN], _fact[kMaxN];
map<int, int> mp1, mp2;

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
  if (y < 0 || y > x) {
    return 0;
  }
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
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
    mp1[v[i].x1] = mp1[v[i].x2] = 0;
    mp2[v[i].y1] = mp2[v[i].y2] = 0;
  }
  for (auto &i : mp1) {
    i.second = ++p, a1[p] = i.first;
  }
  for (auto &i : mp2) {
    i.second = ++q, a2[q] = i.first;
  }
  for (int i = 1; i <= n; i++) {
    v[i].a1 = mp1[v[i].x1], v[i].a2 = mp1[v[i].x2];
    v[i].b1 = mp2[v[i].y1], v[i].b2 = mp2[v[i].y2];
  }
  for (int i = 1; i <= n; i++) {
    c[v[i].a1][v[i].b1]++, c[v[i].a1][v[i].b2]--;
    c[v[i].a2][v[i].b1]--, c[v[i].a2][v[i].b2]++;
  }
  for (int i = 1; i <= p; i++) {
    for (int j = 1; j <= q; j++) {
      c[i][j] += c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];
    }
  }
  for (int i = 1; i < p; i++) {
    for (int j = 1; j < q; j++) {
      w[c[i][j]] = (w[c[i][j]] + 1LL * (a1[i + 1] - a1[i]) * (a2[j + 1] - a2[j])) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = 0;
    for (int j = 1; j <= n; j++) {
      ans = (ans + w[j] * (C(n, i) - C(n - j, i) + kMod)) % kMod;
    }
    ans = ans * _fact[n] % kMod * fact[i] % kMod * fact[n - i] % kMod;
    cout << ans << '\n';
  }
  return 0;
}
