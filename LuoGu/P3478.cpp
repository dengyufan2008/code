#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL d, t, n = 1;  // 深度  子树深度和  子树节点数
  vector<LL> e;
} v[1000001];
LL n, mx, ans = 1, d[1000001];

void T(LL f, LL x) {
  v[x].t = v[x].d = v[f].d + 1;
  for (LL i : v[x].e) {
    if (f != i) {
      T(x, i);
      v[x].t += v[i].t, v[x].n += v[i].n;
    }
  }
}

void _T(LL f, LL x) {
  for (LL i : v[x].e) {
    if (f != i) {
      d[i] = d[x] + n - 2 * v[i].n;
      if (d[i] > mx) {
        mx = d[i];
        ans = i;
      } else if (d[i] == mx && ans > i) {
        ans = i;
      }
      _T(x, i);
    }
  }
}

int main() {
  cin >> n;
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  mx = d[1] = v[1].t;
  _T(0, 1);
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
