// #include <fstream>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const LL kMaxN = 1e6 + 1;
struct V {
  LL l, *f, *g;  // 深度点数 深度-距离点对
  vector<LL> e;
} v[kMaxN];
LL n, ans, *t, h[kMaxN * 5];

void S(LL f, LL x) {
  v[x].l = 1;
  for (LL &i : v[x].e) {
    S(x, i);
    v[x].l = max(v[x].l, v[i].l + 1);
    if (v[i].l > v[v[x].e[0]].l) {
      swap(i, v[x].e[0]);
    }
  }
}

void T(LL f, LL x, bool b) {
  if (b) {
    v[x].f = t, v[x].g = t + v[x].l * 2 + 1, t += v[x].l * 3 + 2;
  }
  if (!v[x].e.empty()) {
    v[v[x].e[0]].f = v[x].f + 1, v[v[x].e[0]].g = v[x].g - 1;
    T(x, v[x].e[0], 0);
  }
  for (LL i : v[x].e) {
    if (i != v[x].e[0]) {
      T(x, i, 1);
      for (LL j = 0; j <= v[i].l; j++) {
        ans += v[x].g[j + 1] * v[i].f[j];
        if (j) {
          ans += v[x].f[j - 1] * v[i].g[j];
        }
      }
      for (LL j = 0; j <= v[i].l; j++) {
        v[x].g[j + 1] += v[x].f[j + 1] * v[i].f[j];
        if (j) {
          v[x].g[j - 1] += v[i].g[j];
        }
      }
      for (LL j = 0; j <= v[i].l; j++) {
        v[x].f[j + 1] += v[i].f[j];
      }
    }
  }
  v[x].f[0]++, ans += v[x].g[0];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (LL i = 2, x; i <= n; i++) {
    cin >> x;
    v[x].e.push_back(i);
  }
  t = h, S(0, 1), T(0, 1, 1);
  cout << ans;
  return 0;
}
