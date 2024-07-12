#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long
#define PLL pair<LL, LL>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 2e5 + 1;
struct V {
  LL f[2];  // 0: < k, 1: >= k
  vector<PLL> e;
} v[kMaxN];
LL n, k, ans;

void T(LL f, LL x) {
  for (auto &i : v[x].e) {
    if (i.first != f) {
      T(x, i.first);
    } else {
      swap(i, v[x].e.front());
    }
  }
  if (f) {
    swap(v[x].e.front(), v[x].e.back()), v[x].e.pop_back();
  }
  if (!v[x].e.empty()) {
    sort(v[x].e.begin(), v[x].e.end(), [](PLL i, PLL j) {
      return v[i.first].f[0] + i.second > v[j.first].f[0] + j.second;
    });
    if (v[x].e.size() < k) {
      for (LL i = 0; i < v[x].e.size(); i++) {
        v[x].f[0] += v[v[x].e[i].first].f[0] + v[x].e[i].second;
      }
      v[x].f[1] = v[x].f[0];
      for (LL i = 0; i < v[x].e.size(); i++) {
        v[x].f[1] = max(v[x].f[1], v[x].f[0] - v[v[x].e[i].first].f[0] + v[v[x].e[i].first].f[1]);
      }
      ans = max(ans, v[x].f[1]);
    } else {
      for (LL i = 0; i < k - 1; i++) {
        v[x].f[0] += v[v[x].e[i].first].f[0] + v[x].e[i].second;
      }
      LL s = v[x].f[0];
      for (LL i = 0; i < k - 1; i++) {
        s = max(s, v[x].f[0] - v[v[x].e[i].first].f[0] + v[v[x].e[i].first].f[1]);
      }
      ans = max(ans, s + v[v[x].e[k - 1].first].f[0] + v[x].e[k - 1].second);
      v[x].f[1] = s, s = 0;
      for (LL i = k - 1; i < v[x].e.size(); i++) {
        s = max(s, v[x].f[0] - (v[v[x].e[k - 2].first].f[0] + v[x].e[k - 2].second) + (v[v[x].e[i].first].f[1] + v[x].e[i].second));
      }
      ans = max(ans, s + v[v[x].e[k - 2].first].f[0] + v[x].e[k - 2].second);
      v[x].f[1] = max(v[x].f[1], s), s = 0;
      for (LL i = 0; i < v[x].e.size(); i++) {
        s += v[v[x].e[i].first].f[0] + v[x].e[i].second;
      }
      ans = max(ans, s), v[x].f[1] = max(v[x].f[1], s);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (LL i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  if (!k) {
    cout << 0;
    return 0;
  } else if (k == 1) {
    for (LL i = 1; i <= n; i++) {
      LL s = 0;
      for (auto j : v[i].e) {
        s += j.second;
      }
      ans = max(ans, s);
    }
  } else {
    T(0, 1);
  }
  cout << ans;
  return 0;
}
