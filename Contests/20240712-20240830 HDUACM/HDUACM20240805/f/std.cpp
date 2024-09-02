#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
i64 ksm(i128 x, i64 tp, const i64 p, i64 s = 1) {
  for (; tp; x = x * x % p, tp >>= 1)
    if (tp & 1) s = x * s % p;
  return s;
}
bool check(i64 x, i64 p) {
  return ksm(x, (p - 1) / 2, p) == 1;
}
struct F {
  i64 d, p;
  F(i64 d = 0, i64 p = 0) : d(d), p(p) {}
  struct D {
    i64 r, i;
    D(i64 r = 0, i64 i = 0) : r(r), i(i) {}
  };
  D mult(D x, D y) {
    return D(((i128)x.r * y.r + (i128)x.i * y.i % p * d) % p,
             ((i128)x.r * y.i + (i128)x.i * y.r) % p);
  }
  D ksm(D x, i64 tp, D s = D(1, 0)) {
    for (; tp; x = mult(x, x), tp >>= 1)
      if (tp & 1) s = mult(s, x);
    return s;
  }
};
i64 residue(i64 x, i64 p) {
  mt19937_64 rnd(114514);
  i64 a;
  do {
    a = rnd() % p;
  } while (check(((i128)a * a - x + p) % p, p));
  F f = F(((i128)a * a - x + p) % p, p);
  return f.ksm(F::D(a, 1), (p + 1) / 2).r;
}
i128 reduce(i128 x, i128 y) {
  i128 t = x < 0 ? -1 : 1;
  x *= t;
  return (x / y + (x % y * 2 >= y)) * t;
}
void solve() {
  i64 p, q;
  scanf("%lld %lld", &p, &q);
  if (!check(q - p, q)) {
    puts("-1");
    return;
  }
  i128 a[2][2];
  a[0][0] = 1;
  a[0][1] = residue(q - p, q);
  a[1][0] = 0;
  a[1][1] = q;
  while (1) {
    i128 x = 0, y = 0, z = 0;
    for (int i = 0; i < 2; i++) {
      x += a[0][i] * a[0][i];
      y += a[1][i] * a[1][i];
      z += a[0][i] * a[1][i];
    }
    if (x > y) {
      swap(a[0], a[1]);
      swap(x, y);
    }
    i128 c = reduce(z, x);
    if (c == 0) break;
    for (int i = 0; i < 2; i++)
      a[1][i] -= c * a[0][i];
  }
  i64 rx = abs((i64)a[0][1]), ry = abs((i64)a[0][0]);
  if ((i128)rx * rx + (i128)p * ry * ry == q)
    printf("%lld %lld\n", rx, ry);
  else
    puts("-1");
}
int main() {
  freopen("f.in", "r", stdin);
  freopen("f.ans", "w", stdout);
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}
