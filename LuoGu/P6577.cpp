#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const LL kInf = 19980732;
struct V {
  LL v, p, b, d, _d, l;
  vector<pair<LL, LL>> e;
} v[1001];
LL n, m, k = 1, ans;

bool T(LL x) {
  if (v[x].b != k) {
    v[x].b = k;
    for (auto i : v[x].e) {
      if (v[x].v + v[i.first].v == i.second) {
        v[i.first].b = k;
        if (v[x].p != i.first) {
          v[x].l = i.first;
          if (!v[i.first].p || T(v[i.first].p)) {
            return 1;
          }
        }
      } else if (v[i.first].d > v[x].v + v[i.first].v - i.second) {
        v[i.first].d = v[x].v + v[i.first].v - i.second, v[i.first]._d = x;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= n; i++) {
    v[i].v = -kInf;
  }
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y + n, z}), v[x].v = max(v[x].v, z);
  }
  for (LL i = 1, d, x; (x = i) <= n; i++, k++) {
    while (1) {
      d = kInf * n;
      for (LL j = n + 1; j <= n * 2; j++) {
        v[j].d = kInf * n;
      }
      if (T(x)) {
        for (LL j = i; j;) {
          LL t = v[v[j].l].p;
          v[v[j].l].p = j, v[j].p = v[j].l, v[j].l = 0, j = t;
        }
        break;
      }
      for (LL j = n + 1; j <= n * 2; j++) {
        if (v[j].b != k && v[j].d < d) {
          d = v[j].d, x = v[j]._d;
        }
      }
      for (LL j = 1; j <= n; j++) {
        v[j].v -= (v[j].b == k) * d;
      }
      for (LL j = n + 1; j <= n * 2; j++) {
        v[j].v += (v[j].b == k) * d;
      }
      v[x].b = 0;
    }
  }
  for (LL i = 1; i <= n * 2; i++) {
    ans += v[i].v;
  }
  cout << ans << '\n';
  for (LL i = n + 1; i <= n * 2; i++) {
    cout << v[i].p << ' ';
  }
  return 0;
}
