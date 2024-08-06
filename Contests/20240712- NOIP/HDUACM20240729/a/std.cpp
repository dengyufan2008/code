#include <cstdio>
const int N = 15, inf = ~0U >> 1;
int Case, n, i, j, k, S, o;
bool ok[(1 << N) + 1];
struct P {
  int x, y, z;
  P() {}
  P(int _x, int _y, int _z) { x = _x, y = _y, z = _z; }
  P operator-(const P& p) const { return P(x - p.x, y - p.y, z - p.z); }
  P operator*(const P& p) const { return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
  int operator^(const P& p) const { return x * p.x + y * p.y + z * p.z; }
} p[N];
inline int ptoplane(const P& a, const P& b, const P& c, const P& p) { return ((b - a) * (c - a)) ^ (p - a); }
inline void umin(int& a, int b) { a > b ? (a = b) : 0; }
inline void umax(int& a, int b) { a < b ? (a = b) : 0; }
inline bool colinear(const P& a, const P& b, const P& p) {
  P t = (a - b) * (b - p);
  return !t.x && !t.y && !t.z;
}
inline int sgn(int x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}
// 12v^4
inline bool check(const P& a, const P& b, const P& c, const P& p) {
  return (((b - a) * (c - a)) ^ ((b - a) * (p - a))) >= 0;
}
struct Face {
  P a, b, c;
  int sgn;
  bool inside(const P& p) const {
    return check(a, b, c, p) && check(b, c, a, p) && check(c, a, b, p);
  }
} f[N * N * N];
int main() {
  freopen("a.in", "r", stdin);
  freopen("a.ans", "w", stdout);
  scanf("%d", &Case);
  while (Case--) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z);
    for (i = 1; i < 1 << n; i++) ok[i] = 0;
    for (S = 1; S < 1 << n; S++) {
      if (__builtin_popcount(S) <= 1) {
        ok[S] = 1;
        continue;
      }
      int m = 0;
      bool same = 1;
      for (i = 0; i < n; i++)
        if (S >> i & 1)
          for (j = 0; j < i; j++)
            if (S >> j & 1)
              for (k = 0; k < j; k++)
                if (S >> k & 1) {
                  if (colinear(p[i], p[j], p[k])) continue;
                  int l = inf, r = -inf;
                  for (o = 0; o < n; o++)
                    if (S >> o & 1) {
                      int tmp = ptoplane(p[i], p[j], p[k], p[o]);
                      umin(l, tmp);
                      umax(r, tmp);
                    }
                  if (l < 0 && r > 0) continue;
                  if (l || r) same = 0;
                  f[m].a = p[i];
                  f[m].b = p[j];
                  f[m].c = p[k];
                  f[m].sgn = sgn(l) + sgn(r);
                  m++;
                }
      int mask = S;
      if (!m) {
        // colinear
        int xl = inf, xr = -inf;
        int yl = inf, yr = -inf;
        int zl = inf, zr = -inf;
        int idl = n, idr = 0;
        for (i = 0; i < n; i++)
          if (S >> i & 1) {
            umin(xl, p[i].x);
            umax(xr, p[i].x);
            umin(yl, p[i].y);
            umax(yr, p[i].y);
            umin(zl, p[i].z);
            umax(zr, p[i].z);
            umin(idl, i);
            umax(idr, i);
          }
        for (i = 0; i < n; i++) {
          if (S >> i & 1) continue;
          if (!colinear(p[idl], p[idr], p[i])) continue;
          if (p[i].x < xl || p[i].x > xr) continue;
          if (p[i].y < yl || p[i].y > yr) continue;
          if (p[i].z < zl || p[i].z > zr) continue;
          mask |= 1 << i;
        }
      } else if (same) {
        // just a face
        for (i = 0; i < n; i++) {
          if (S >> i & 1) continue;
          if (ptoplane(f[0].a, f[0].b, f[0].c, p[i])) continue;
          for (j = 0; j < m; j++)
            if (f[j].inside(p[i])) {
              mask |= 1 << i;
              break;
            }
        }
      } else {
        for (i = 0; i < n; i++) {
          if (S >> i & 1) continue;
          for (j = 0; j < m; j++) {
            int tmp = sgn(ptoplane(f[j].a, f[j].b, f[j].c, p[i]));
            if (tmp && tmp != f[j].sgn) break;
          }
          if (j == m) mask |= 1 << i;
        }
      }
      ok[mask] = 1;
    }
    int ans = 0;
    for (i = 1; i < 1 << n; i++)
      if (ok[i]) {
        ans++;
        if (__builtin_popcount(i) >= 3) {
          // printf("%d\n", i);
        }
      }
    printf("%d\n", ans);
  }
}
