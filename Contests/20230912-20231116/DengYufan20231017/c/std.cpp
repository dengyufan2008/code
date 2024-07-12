#include <bits/stdc++.h>
#define For(i, l, r) for (int i = l, i##_e = r; i <= i##_e; i++)
#define rFor(i, r, l) for (int i = r, i##_e = l; i >= i##_e; --i)
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long ll;
typedef unsigned long long u64;
typedef array<int, 2> pii;
const int M = 998244353, G = 3;
struct mint {
  int x;
  static mint get(const int &x) {
    mint y;
    y.x = x;
    return y;
  }
  mint(ll x = 0) : x((x % M + M) % M) {}
  mint operator+(const mint &b) const {
    int y = x + b.x;
    return get(y >= M ? y - M : y);
  }
  mint operator-(const mint &b) const {
    int y = x - b.x;
    return get(y < 0 ? y + M : y);
  }
  mint operator*(const mint &b) const {
    ll y = x * b;
    if (y >= (M << 1)) y %= M;
    return get(y >= M ? y - M : y);
  }
  void operator+=(const mint &b) { *this = *this + b; }
  void operator-=(const mint &b) { *this = *this - b; }
  void operator*=(const mint &b) { *this = *this * b; }
  operator ll() const { return x; }
};
typedef vector<mint> poly;
template <class T>
T ksm(T a, int b) {
  T ans = 1;
  for (; b; b >>= 1, a = a * a) b & 1 ? ans = ans * a, 0 : 0;
  return ans;
}
static void NTT(poly &a, const int k) {
  static vector<int> r;
  static vector<mint> w;
  int n = a.size();
  if (n != r.size()) {
    int l = __lg(n);
    r.resize(n);
    For(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
  }
  For(i, 0, n - 1) if (i < r[i]) swap(a[r[i]], a[i]);
  mint wi = ksm(mint(G), (M - 1 >> 1) / n * k + M - 1);
  w.resize(n);
  w[0] = 1;
  For(i, 1, n - 1) w[i] = w[i - 1] * wi;
  for (int m = 1, l = 0; m < n; m <<= 1, ++l)
    for (int i = 0; i < n; i += m + m)
      For(j, 0, m - 1) {
        mint x = a[i + j], y = w[(n >> l) * j] * a[i + j + m];
        a[i + j] = x + y;
        a[i + j + m] = x - y;
      }
  if (k == -1) {
    int inv = ksm(mint(n), M - 2);
    For(i, 0, n - 1) a[i] *= inv;
  }
}
int m, p;
poly operator+(poly &a, poly &b) {
  poly c(max(a.size(), b.size()));
  For(i, 0, c.size() - 1) {
    if (i < a.size()) c[i] += a[i];
    if (i < b.size()) c[i] += b[i];
  }
  return c;
}
void operator+=(poly &a, poly b) { a = a + b; }
poly operator*(poly a, poly b) {
  if (m <= 50) {
    poly c(m + 1);
    For(i, 0, a.size() - 1) For(j, 0, min(m - i, int(b.size() - 1)))
        c[i + j] += a[i] * b[j];
    return c;
  }
  int l = 1 << __lg(m) + 2;
  a.resize(l);
  b.resize(l);
  NTT(a, 1);
  NTT(b, 1);
  For(i, 0, l - 1) a[i] *= b[i];
  NTT(a, -1);
  a.resize(m + 1);
  return a;
}
struct info1 {
  int m, c[60];
  info1 operator+(const info1 &b) {
    info1 res = *this;
    res.m = res.m * b.m % p;
    For(i, 0, p - 1) res.c[i * m % p] += b.c[i];
    return res;
  }
};
info1 solve1(int n) {
  static info1 a, r;
  a.m = 10 % p;
  a.c[1 % p] = 1;
  r.m = 1;
  for (; n; n >>= 1, a = a + a) n & 1 && (r = r + a, 0);
  return r;
}
typedef vector<poly> info;
info operator*(info a, info b) {
  info c(p);
  For(i, 0, p - 1) For(j, 0, p - 1) c[(i + j) % p] += a[i] * b[j];
  return c;
}
poly solve2(int n) {
  poly a(min(m + 1, 10)), r{1};
  For(i, 0, min(m, 9)) a[i] = 1;
  for (; n; n >>= 1, a = a * a) n & 1 && (r = r * a, 0);
  return r;
}
int main() {
#ifdef LOCAL
  freopen(".in", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n >> p >> m;
  info1 cnt = solve1(n);
  info res(p);
  res[0] = {1};
  For(i, 0, p - 1) {
    int c = cnt.c[i];
    auto f = solve2(c);
    f.resize(m + 1);
    info x(p, poly(m + 1));
    For(j, 0, m) x[i * j % p][j] += f[j];
    res = res * x;
  }
  auto ans = res[0];
  ans.resize(m + 1);
  mint s = 0;
  for (auto x : ans) s += x, cout << s << " ";
}
