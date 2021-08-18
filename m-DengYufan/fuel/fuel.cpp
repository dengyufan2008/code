#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL x, v;
} e[50002];

int main() {
  freopen("fuel.in", "r", stdin);
  freopen("fuel.out", "w", stdout);
  register LL n, g, b, d, f[2][1000001];
  cin >> n >> g >> b >> d;
  for (register LL i(1); i <= n; ++i) {
    cin >> e[i].x >> e[i].v;
  }
  fill(&f[0][0], &f[1][1000001] + 1, 1145141919810);
  fill(&f[0][0], &f[0][b] + 1, 0);
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.x < j.x;
  });
  e[0].v = 1145141919810, e[++n].x = d;
  for (register LL i(1); i <= n; ++i) {
    for (register LL j(0); j + e[i].x - e[i - 1].x <= g; ++j) {
      for (register LL k(0); k <= j + e[i].x - e[i - 1].x; ++k) {
        f[1][j] = min(f[1][j], f[0][k] + (j + e[i].x - e[i - 1].x - k) * e[i - 1].v);
      }
    }
    copy(&f[1][0], &f[1][1000000] + 1, &f[0][0]);
    fill(&f[1][0], &f[1][1000000] + 1, 1145141919810);
  }
  cout << (f[0][0] == 1145141919810 ? -1 : f[0][0]) << '\n';
  return 0;
}
