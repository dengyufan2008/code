#include <algorithm>
#include <vector>

#include "data.h"
#define LL long long

using namespace std;

const int kMaxN = 2e5 + 1, kMaxM = 1e4 + 1, kMaxK = 101;
struct E {
  int x, y;
  Data d;
} e[kMaxN];
struct V {
  int a, b, c;
} v[kMaxM], _v[kMaxM];
struct Q {
  int l, r;
} q[kMaxK];
int n, m, k;
Data ans[kMaxK];

void Calc(Data &ans, int m) {
  static vector<V> l;
  sort(v + 1, v + m + 1, [](V i, V j) {  // 按斜率升序
    return i.a * j.b > i.b * j.a || i.a * j.b == i.b * j.a && i.c * j.b > i.b * j.c;
  });
  l.clear();
  for (int i = 1; i <= m; i++) {
    if (i == 1 || v[i - 1].a * v[i].b > v[i - 1].b * v[i].a) {
      for (; l.size() > 1; l.pop_back()) {
        V l1 = l[l.size() - 2], l2 = l.back(), l3 = v[i];
        LL w1 = l1.c * l2.b - l1.b * l2.c;
        LL w2 = l1.a * l2.b - l1.b * l2.a;
        LL w3 = l2.c * l3.b - l2.b * l3.c;
        LL w4 = l2.a * l3.b - l2.b * l3.a;
        if (w1 * w4 < w3 * w2) {
          break;
        }
      }
      l.push_back(v[i]);
    }
  }
  for (int i = 1, j = 0; i <= n; i++) {
    for (; j + 1 < l.size(); j++) {
      LL w1 = l[j].c * l[j + 1].b - l[j].b * l[j + 1].c;
      LL w2 = l[j].a * l[j + 1].b - l[j].b * l[j + 1].a;
      if (w1 > e[i].x * w2) {
        break;
      }
    }
    if (e[i].x * l[j].a + e[i].y * l[j].b >= l[j].c) {
      ans.add(ans, e[i].d);
    }
  }
}

void Main() {
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.x < j.x;
  });
  for (int i = 1; i <= m; i++) {
    _v[i] = v[i];
  }
  for (int i = 1; i <= k; i++) {
    for (int j = q[i].l; j <= q[i].r; j++) {
      v[j - q[i].l + 1] = _v[j];
    }
    Calc(ans[i], q[i].r - q[i].l + 1);
  }
}

void solve(int n, int xy[][2], Data d[], int m, int abc[][3], int q, int lr[][2], Data ans[]) {
  ::n = n, ::m = m, k = q;
  for (int i = 1; i <= n; i++) {
    e[i].x = xy[i][0], e[i].y = xy[i][1], e[i].d = d[i];
  }
  for (int i = 1; i <= m; i++) {
    v[i].a = abc[i][0], v[i].b = abc[i][1], v[i].c = abc[i][2];
  }
  for (int i = 1; i <= q; i++) {
    ::q[i].l = lr[i][0], ::q[i].r = lr[i][1], ::ans[i].clr();
  }
  Main();
  for (int i = 1; i <= q; i++) {
    ans[i] = ::ans[i];
  }
}
