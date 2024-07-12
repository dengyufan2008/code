#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long
 
using namespace std;
 
const LL kMaxN = 402, kInf = 1e18;
struct V {
  int a, b, c;
};
int o, n, t[kMaxN];
LL ans, f[2][kMaxN][kMaxN], sf[kMaxN][kMaxN], d[kMaxN][kMaxN];
vector<V> v[kMaxN];
 
void Update(LL &x, LL y) { x = max(x, y); }
 
int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o >> o;
  while (o--) {
    fill(&v[1], &v[n] + 1, v[0]);
    cin >> n;
    for (int i = 1, a, b, c, w; i <= n; i++) {
      cin >> a >> b >> c >> w;
      v[w].push_back({a, b, c});
    }
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        f[0][j][k] = (j || k) * -kInf;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (v[i].empty()) {
        for (int j = 0; j <= n; j++) {
          for (int k = 0; k <= n; k++) {
            f[i & 1][j][k] = f[i & 1 ^ 1][j][k];
          }
        }
        continue;
      }
      int m = v[i].size();
      sort(v[i].begin(), v[i].end(), [](V x, V y) { return x.a < y.a; });
      for (int j = 0; j < m; j++) {
        t[j] = j;
      }
      sort(t, t + m, [i](int x, int y) {
        return v[i][x].c - v[i][x].b < v[i][y].c - v[i][y].b;
      });
      for (int j = 0; j <= n; j++) {
        for (int k = 0; k <= n; k++) {
          f[i & 1][j][k] = -kInf;
        }
      }
      for (int j = 0; j <= n; j++) {
        sf[j][0] = f[i & 1 ^ 1][j][0];
        for (int k = 1; k <= n; k++) {
          sf[j][k] = max(sf[j][k - 1], f[i & 1 ^ 1][j][k]);
        }
      }
      for (int j = 0; j <= m; j++) {
        for (int k = 0; k <= n; k++) {
          for (int l = 0; l <= n; l++) {
            d[k][l] = -kInf;
          }
        }
        for (int k = 0; k < m; k++) {  // lamax = v[i][k].a, ramax = v[i][m - 1].a
          int _j = j - (j > 0);
          LL s = j > 0 ? v[i][k].b : v[i][k].c;
          for (int l = k + 1; l < m; l++) {
            s += v[i][l].c;
          }
          for (int l = 0; l < m; l++) {
            if (t[l] < k) {
              s += _j > 0 ? _j--, v[i][t[l]].b : v[i][t[l]].c;
            }
          }
          if (!_j) {
            Update(d[max((j > 0 ? v[i][k].a : 0) - j + 1, 0)][max(v[i][m - 1].a - m + 1, 0)], s);
          }
        }
        for (int k = 0; k < m; k++) {  // lamax = v[i][m - 1].a, ramax = v[i][k].a
          int _j = j - m + k + (j < m);
          LL s = j < m ? v[i][k].c : v[i][k].b;
          for (int l = k + 1; l < m; l++) {
            s += v[i][l].b;
          }
          for (int l = 0; l < m; l++) {
            if (t[l] < k) {
              s += _j > 0 ? _j--, v[i][t[l]].b : v[i][t[l]].c;
            }
          }
          if (!_j) {
            Update(d[max(v[i][m - 1].a - j + 1, 0)][max((j < m ? v[i][k].a : 0) - m + 1, 0)], s);
          }
        }
        for (int k = 0; k <= n; k++) {  // k - left <= ramax - m + 1
          for (int l = 0; l <= n; l++) {
            k ? Update(d[k][l], d[k - 1][l]) : void();
            if (k + j >= m) {
              Update(f[i & 1][k][l], sf[k - m + j][min(l + j, n)] + d[k][l]);
            }
          }
        }
        for (int k = 0; k <= n; k++) {  // k - left >= ramax - m + 1
          for (int l = 0; l <= n; l++) {
            l ? Update(d[k][l], d[k][l - 1]) : void();
            if (k + j >= m && l + j <= n) {
              Update(f[i & 1][k][l], f[i & 1 ^ 1][k - m + j][l + j] + d[k][l]);
            }
          }
        }
      }
    }
    ans = -1;
    for (int i = 0; i <= n; i++) {
      ans = max(ans, f[n & 1][i][0]);
    }
    cout << ans << '\n';
  }
  return 0;
}
