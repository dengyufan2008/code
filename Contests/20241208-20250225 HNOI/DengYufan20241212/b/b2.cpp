#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.ans");

const LL kMaxN = 3001, kInf = 2e18;
struct E {
  LL w, ans;
} l[kMaxN][kMaxN], r[kMaxN][kMaxN];
int t, n;
LL a[kMaxN], b[kMaxN];
LL f[kMaxN][kMaxN], g[kMaxN][kMaxN], sf[kMaxN][kMaxN], sg[kMaxN][kMaxN];
vector<pair<int, LL>> p, q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
      b[i] = a[i + 1] - a[i];
    }
    for (int i = 1; i < n; i++) {
      for (int j = i + 1; j <= n; j++) {
        LL x = b[j - 1] - l[j - 1][i].w;
        if (l[j - 1][i].ans >= 0 && (j == n || x <= b[j])) {
          l[j][i] = {x, l[j - 1][i].ans + x * x};
        } else {
          l[j][i] = {kInf, -kInf};
        }
      }
    }
    for (int i = n; i > 1; i--) {
      for (int j = i - 1; j >= 1; j--) {
        LL x = b[j] - r[j + 1][i].w;
        if (r[j + 1][i].ans >= 0 && (j == 1 || x <= b[j - 1])) {
          r[j][i] = {x, r[j + 1][i].ans + x * x};
        } else {
          r[j][i] = {kInf, -kInf};
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < i; j++) {
        f[i][j] = g[i][j] = sf[i][j] = sg[i][j] = 0;
      }
    }
    LL w = 0;
    p.clear(), q.clear();
    for (int i = 3; i <= n; i++) {
      i & 1 ? w += b[i - 1] : w -= b[i - 1];
      q.push_back({w, i});
    }
    sort(q.begin(), q.end());
    for (int i = 2; i <= n; i++) {
      LL maxf = 0, maxg = 0, maxh = 0;
      for (int j = 1; j < i; j++) {
        sf[i][j] = max(sf[i][j], sf[i - 1][j]);
        f[i][j] = max(f[i][j], sf[i][j]);
        sg[i][j] = max(sg[i][j], sg[i - 1][j]);
        g[i][j] = max(g[i][j], sg[i][j]);
        f[i][j] += l[i][j].ans;
        g[i][j] += r[j][i].ans;
        maxf = max(maxf, f[i][j]);
        maxg = max(maxg, g[i][j]);
      }
      if (i + 1 <= n) {
        // -> + <-
        sf[i + 1][i] = max(sf[i + 1][i], maxg);
        if (i + 2 <= n) {
          // -> + <-
          sf[i + 2][i + 1] = max(sf[i + 2][i + 1], maxg);
          // <- + <-
          sf[i + 2][i + 1] = max(sf[i + 2][i + 1], maxf);
          // -> + ->
          sg[i + 2][i + 1] = max(sg[i + 2][i + 1], maxg);
        }
      }
      // <- + ->
      reverse(p.begin(), p.end());
      for (auto &v : p) {
        v.first = b[i - 1] - v.first;
      }
      if (p.empty() || p.back().first < b[i - 1]) {
        p.push_back({b[i - 1], i - 1});
      } else {
        for (int j = 0; j < p.size(); j++) {
          if (p[j].first >= b[i - 1]) {
            p.insert(p.begin() + j, {b[i - 1], i - 1});
            break;
          }
        }
      }
      reverse(q.begin(), q.end());
      for (auto &v : q) {
        v.first = b[i] - v.first;
      }
      for (int j = 0; j < q.size(); j++) {
        if (q[j].second == i + 1) {
          q.erase(q.begin() + j);
          break;
        }
      }
      if (!q.empty()) {
        for (int j = 0, k = q.size() - 1; k >= 0; k--) {
          for (; j < p.size() && p[j].first + q[k].first <= a[i + 1] - a[i]; j++) {
            maxh = max(maxh, f[i][p[j].second]);
          }
          g[q[k].second][i + 1] = max(g[q[k].second][i + 1], maxh);
        }
      }
    }
    cout << f[n][n - 1] << '\n';
  }
  return 0;
}
