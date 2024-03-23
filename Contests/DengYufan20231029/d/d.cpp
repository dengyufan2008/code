#include <algorithm>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 5e5 + 1, kMod = 1e9 + 7;
struct A {
  int b, p, x, d;
  LL w;
} a[kMaxN << 2];
struct V {
  int f, s;
  vector<int> e;
} v[kMaxN];
struct E {
  int x, y;
  LL w;
} e[kMaxN];
int n, m, k;
LL ans;
priority_queue<pair<int, int>> q;

int R(int x) { return v[x].f == x ? x : v[x].f = R(v[x].f); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    a[i << 1] = {0, 0, x, y, z}, v[x].e.push_back(i << 1);
    a[i << 1 | 1] = {0, 0, y, x, z}, v[y].e.push_back(i << 1 | 1);
    if (abs(x - y) == 1 || abs(x - y) == n - 1) {
      a[i << 1].b = a[i << 1 | 1].b = 1;
      q.push({-z, i << 1 | (y == 1 || y - x == 1)});
    }
  }
  for (int i = 1; i <= n; i++) {
    v[i].f = i, v[i].s = 1;
    sort(v[i].e.begin(), v[i].e.end(), [](int i, int j) { return a[i].d < a[j].d; });
    for (int j = 0; j < v[i].e.size(); j++) {
      a[v[i].e[j] ^ 1].p = v[i].e[(j + 1) % v[i].e.size()];
    }
  }
  for (int x; !q.empty();) {
    x = q.top().second, q.pop();
    if (a[x].b < 2) {
      a[x].b++, a[x ^ 1].b++;
      for (int y = a[x].p; y != x; y = a[y].p) {
        a[y].b++, a[y ^ 1].b++;
        a[y].w += a[x].w, a[y ^ 1].w += a[x].w;
        a[y].b == 1 ? q.push({-a[y].w, y ^ 1}) : void(e[++k] = {a[y].x, a[y].d, a[y].w});
      }
    }
  }
  sort(e + 1, e + n, [](E i, E j) { return i.w > j.w; });
  for (int i = 1; i < n; i++) {
    ans = (ans + e[i].w % kMod * v[R(e[i].x)].s % kMod * v[R(e[i].y)].s % kMod) % kMod;
    v[R(e[i].x)].s += v[R(e[i].y)].s, v[R(e[i].y)].f = R(e[i].x);
  }
  cout << ans;
  return 0;
}
