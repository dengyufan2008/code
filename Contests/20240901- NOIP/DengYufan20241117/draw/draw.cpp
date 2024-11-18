#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long
#define Vec vector<pair<LL, LL>>

using namespace std;

ifstream cin("draw.in");
ofstream cout("draw.out");

const int kMod = 1e9 + 7;
LL n, k, ans, a[4], l[16], r[16];
vector<Vec> v[5];

LL C(LL x, int y) {
  const static LL _fact[9] = {0, 1, 500000004, 166666668, 41666667,
                              808333339, 301388891, 900198419, 487524805};
  LL ans = _fact[y];
  for (int i = 1; i <= y; i++) {
    ans = ans * (x - i + 1) % kMod;
  }
  return ans;
}

void S(int s) {
  static Vec d;
  if (!s) {
    return v[d.size()].push_back(d);
  }
  for (int t = s; t; t = t - 1 & s) {
    d.push_back({l[t], r[t]}), S(s ^ t), d.pop_back();
  }
}

bool Empty(Vec x) {
  for (auto i : x) {
    if (i.first > i.second) {
      return 1;
    }
  }
  return 0;
}

Vec Merge(Vec x, Vec y) {
  Vec ans;
  for (int i = 0; i < x.size(); i++) {
    ans.push_back({max(x[i].first, y[i].first), min(x[i].second, y[i].second)});
  }
  return ans;
}

void T(int x, int o, Vec d) {
  if (Empty(d)) {
    return;
  } else if (x == v[d.size()].size()) {
    LL w = 0;
    for (int s = 0; s < 1 << d.size(); s++) {
      LL g = n + 1;
      for (int i = 0; i < d.size(); i++) {
        g -= (s >> i & 1 ? d[i].second : d[i].first - 1);
      }
      if (g >= (int)d.size() << 1) {
        if (__builtin_popcount(s) & 1) {
          w = (w - C(g, d.size() << 1) + kMod) % kMod;
        } else {
          w = (w + C(g, d.size() << 1)) % kMod;
        }
      }
    }
    ans = (ans + o * w) % kMod;
    return;
  }
  T(x + 1, o, d), T(x + 1, kMod - o, Merge(d, v[d.size()][x]));
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    cin >> a[i];
  }
  sort(a, a + k);
  for (int s = 0; s < 1 << k; s++) {
    for (int i = 0; i < k; i++) {
      if (s >> i & 1) {
        l[s] = a[i];
      }
    }
    for (int i = 0; i < k; i++) {
      if (s >> i & 1) {
        r[s] += a[i];
      }
    }
  }
  S((1 << k) - 1);
  for (int i = 1; i <= k; i++) {
    for (int j = 0; j < v[i].size(); j++) {
      T(j + 1, 1, v[i][j]);
    }
  }
  cout << ans << '\n';
  return 0;
}
