#include <fstream>
#include <set>
#include <vector>
#define LL long long
#define PLL pair<LL, LL>

using namespace std;

ifstream cin("graph.in");
ofstream cout("graph.out");

const LL kMaxN = 5e5 + 1;
struct V {
  vector<PLL> e, w;
} v[kMaxN];
LL t, n, m, q, k;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (LL i = 1; i <= n; i++) {
      v[i].e.clear(), v[i].w.clear();
    }
    cin >> n >> m >> q >> k;
    for (LL i = 1, x, y, z; i <= m; i++) {
      cin >> x >> y >> z;
      v[y].e.push_back({x, z});
    }
    v[1].w.push_back({0, 0});
    for (LL i = 2; i <= n; i++) {
      for (auto j : v[i].e) {
        vector<PLL> w;
        for (LL p = 0, q = 0; p < v[i].w.size() || q < v[j.first].w.size();) {
          if (p < v[i].w.size()) {
            if (q >= v[j.first].w.size() || v[i].w[p].first < v[j.first].w[q].first + j.second * (k - 1)) {
              if (w.size() && w.back().second >= v[i].w[p].first - 1) {
                w.back().second = max(w.back().second, v[i].w[p].second);
              } else {
                w.push_back(v[i].w[p]);
              }
              p++;
            } else {
              if (w.size() && w.back().second >= v[j.first].w[q].first + j.second * (k - 1) - 1) {
                w.back().second = max(w.back().second, v[j.first].w[q].second + j.second * k);
              } else {
                w.push_back({v[j.first].w[q].first + j.second * (k - 1), v[j.first].w[q].second + j.second * k});
              }
              q++;
            }
          } else {
            if (w.size() && w.back().second >= v[j.first].w[q].first + j.second * (k - 1) - 1) {
              w.back().second = max(w.back().second, v[j.first].w[q].second + j.second * k);
            } else {
              w.push_back({v[j.first].w[q].first + j.second * (k - 1), v[j.first].w[q].second + j.second * k});
            }
            q++;
          }
        }
        v[i].w = w;
      }
    }
    for (LL i = 1, x, y; i <= q; i++) {
      cin >> x >> y;
      LL l = 0, r = v[x].w.size() - 1;
      while (l <= r) {
        LL mid = l + r >> 1;
        if (v[x].w[mid].first <= y * k) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      cout << (r >= 0 && v[x].w[r].second >= y * k);
    }
    cout << '\n';
  }
  return 0;
}
