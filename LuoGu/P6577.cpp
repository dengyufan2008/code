#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kInf = 19980732;
struct V {
  int v, p, b, d;
  vector<pair<int, int>> e;
} v[1001];
int n, m, k, d, ans;

bool T(int x) {
  if (v[x].b != k) {
    v[x].b = k;
    for (auto i : v[x].e) {
      if (v[x].v + v[i.first].v == i.second) {
        v[i.first].b = k;
        if (!v[i.first].p || T(v[i.first].p)) {
          v[i.first].p = x;
          return 1;
        }
      } else {
        v[i.first].d = min(v[i.first].d, i.second - v[x].v - v[i.first].v);
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    v[i].v = -kInf;
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y + n, z}), v[x].v = max(v[x].v, z);
  }
  for (int i = 1; i <= n; i++) {
    while (1) {
      k++, d = kInf;
      for (int j = n + 1; j <= n * 2; j++) {
        v[j].d = kInf;
      }
      if (T(i)) {
        break;
      }
      for (int j = n + 1; j <= n * 2; j++) {
        d = min(d, v[j].b == k ? kInf : v[j].d);
      }
      for (int j = 1; j <= n; j++) {
        v[j].v -= (v[j].b == k) * d;
      }
      for (int j = n + 1; j <= n * 2; j++) {
        v[j].v += (v[j].b == k) * d;
      }
    }
  }
  for (int i = 1; i <= n * 2; i++) {
    ans += v[i].v;
  }
  cout << ans << '\n';
  for (int i = n + 1; i <= n * 2; i++) {
    cout << v[i].p << ' ';
  }
  return 0;
}
