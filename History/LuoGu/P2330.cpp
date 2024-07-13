#include <algorithm>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL x, y, v;
  bool operator<(const E &e) const {
    return v < e.v;
  }
} e[100001];
LL n, m, c, ans, f[301];

LL GetRoot(LL x) {
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= m; i++) {
    cin >> e[i].x >> e[i].y >> e[i].v;
  }
  sort(e + 1, e + m + 1);
  for (LL i = 1; i <= 300; i++) {
    f[i] = i;
  }
  for (LL i = 1; i <= m; i++) {
    LL x = GetRoot(e[i].x), y = GetRoot(e[i].y);
    if (x != y) {
      c++, ans = e[i].v;
      f[x] = y;
    }
  }
  cout << c << " " << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
