#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("road.in");
ofstream cout("road.out");

const int kMaxN = 1e5 + 1, kMaxM = 5e5 + 1, kMaxL = 17;
struct E {
  int x, y, l, w;
} e[kMaxM];
int n, m, lg[kMaxN], f[kMaxL][kMaxN];
LL ans;

int GetRoot(int x, int l) {
  return f[l][x] == x ? x : f[l][x] = GetRoot(f[l][x], l);
}

void Merge(int x, int y, int l, int w) {
  if (GetRoot(x, l) == GetRoot(y, l)) {
    return;
  }
  f[l][GetRoot(x, l)] = GetRoot(y, l);
  if (!l) {
    ans += w;
  } else {
    Merge(x, y, l - 1, w);
    Merge(x + (1 << l - 1), y + (1 << l - 1), l - 1, w);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].x >> e[i].y >> e[i].l >> e[i].w;
  }
  sort(e + 1, e + m + 1, [](E i, E j) {
    return i.w < j.w;
  });
  for (int i = 0; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = j;
    }
  }
  for (int i = 1, x, y, l, w; i <= m; i++) {
    x = e[i].x, y = e[i].y, l = e[i].l, w = e[i].w;
    Merge(x, y, lg[l], w);
    Merge(x + l - (1 << lg[l]), y + l - (1 << lg[l]), lg[l], w);
  }
  cout << ans << '\n';
  return 0;
}
