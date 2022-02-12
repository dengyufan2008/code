#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const LL kInf = 19980732;
struct V {
  LL v, l, _l, b, d, _d, p;
  vector<pair<LL, LL>> e;
} v[1001];
LL n, m, k, ans;

bool T(LL x) {
  if (v[x].b != k) {
    v[x].b = k;
    for (auto i : v[x].e) {
      if (v[x].v + v[i.first].v == i.second) {
        v[i.first].b = k, v[i.first].p = v[i.first].p ? v[i.first].p : x;
        if (!v[i.first].l || T(v[i.first].l)) {
          v[i.first]._l = v[i.first].l, v[x]._l = v[x].l;
          v[i.first].l = x, v[x].l = i.first;
          return 1;
        }
      } else if (v[i.first].d >= v[x].v + v[i.first].v - i.second) {
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
  for (LL i = 1, x = 1; i <= n; x = ++i) {
    k++;
    while (1) {
      for (LL j = n + 1; j <= n * 2; j++) {
        v[j].d = kInf * n;
      }
      if (T(x)) {
        if (x == i) {
          break;
        }
        x = v[x]._l;
        while (1) {
          v[v[x].p].p = x, x = v[x].p;
          v[x].l = v[x].p, v[v[x].p].l = x;
          if (x == i) {
            break;
          }
          x = v[x].l;
        }
        break;
      }
      for (LL j = n + 1; j <= n * 2; j++) {
        if (v[j].b != k && (x == i || v[x].d > v[j].d)) {
          x = j;
        }
      }
      for (LL j = 1; j <= n; j++) {
        v[j].v -= (v[j].b == k) * v[x].d;
      }
      for (LL j = n + 1; j <= n * 2; j++) {
        v[j].v += (v[j].b == k) * v[x].d;
      }
      v[x = v[x]._d].b = 0;
    }
    for (int i = n + 1; i <= n * 2; i++) {
      v[i].p = 0;
    }
  }
  for (LL i = 1; i <= n * 2; i++) {
    ans += v[i].v;
  }
  cout << ans << '\n';
  for (LL i = n + 1; i <= n * 2; i++) {
    cout << v[i].l << ' ';
  }
  return 0;
}
