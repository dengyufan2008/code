#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "data.h"
static char ib[30000000], *ip = ib;
static int read(int L, int R) {
  int x = 0, f = 1;
  while (*ip < 48) {
    if (*ip == '-') f = -1;
    ++ip;
  }
  while (*ip > 47) x = x * 10 + *ip++ - 48;
  x *= f;
  assert(L <= x && x <= R);
  return x;
}
static unsigned int t1 = 0, o_hash = 0;
static struct IO {
  IO() {
    fread(ib, 1, sizeof(ib), stdin)[ib] = 0;
  }
  ~IO() {
    printf("%u\n", o_hash);
    fprintf(stderr, ">>> %u\n", t1);
  }
} _io;
static const unsigned short e1 = 1237, e2 = 2341, e3 = 34531, e4 = 23423;
static const unsigned int mt1 = 4e7;
void Data::add(const Data &a, const Data &b) {
  t1 += 1;
  if (t1 > mt1) exit(1);
  x1 = a.x1 + b.x1 - e1;
  x2 = a.x2 + b.x2 - e2;
  x3 = a.x3 ^ b.x3 ^ e3;
  x4 = a.x4 ^ b.x4 ^ e4;
}
void Data::sub(const Data &a, const Data &b) {
  t1 += 1;
  if (t1 > mt1) exit(1);
  x1 = a.x1 - b.x1 + e1;
  x2 = a.x2 - b.x2 + e2;
  x3 = a.x3 ^ b.x3 ^ e3;
  x4 = a.x4 ^ b.x4 ^ e4;
}
void Data::clr() {
  x1 = e1;
  x2 = e2;
  x3 = e3;
  x4 = e4;
}
int main() {
  unsigned seed = 0;
  auto read_data = [&](Data &d) {
    d.x1 = read(1, 10000) + (++seed);
    d.x2 = d.x1 * 33333;
    d.x3 = d.x1;
    d.x4 = d.x2;
  };
  auto write_data = [&](const Data &d) {
    o_hash = o_hash * 1234577 + d.x1;
    o_hash = o_hash * 1234577 + d.x2;
    o_hash = o_hash * 1234577 + d.x3;
    o_hash = o_hash * 1234577 + d.x4;
    printf("%d %d %d %d\n", d.x1, d.x2, d.x3, d.x4);
  };
  const int N = 5e5 + 7;
  int n = read(1, 5e5);
  static int xy[N][2];
  static Data d[N];
  for (int i = 1; i <= n; ++i) {
    xy[i][0] = read(-1e5, 1e5);
    xy[i][1] = read(-1e5, 1e5);
    read_data(d[i]);
  }
  int m = read(1, 5e5);
  static int abc[N][3];
  for (int i = 1; i <= m; ++i) {
    abc[i][0] = read(-1e4, 1e4);
    abc[i][1] = read(1, 1e4);
    abc[i][2] = read(-1e5, -1);
  }
  int q = read(1, 5e5);
  static int lr[N][2];
  static Data ans[N];
  for (int i = 1; i <= q; ++i) {
    lr[i][0] = read(1, m);
    lr[i][1] = read(lr[i][0], m);
    ans[i].clr();
  }
  solve(n, xy, d, m, abc, q, lr, ans);
  for (int i = 1; i <= q; ++i) write_data(ans[i]);
  return 0;
}