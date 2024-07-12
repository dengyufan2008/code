#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("jump.in");
ofstream cout("jump.out");

const int kMaxN = 5e5 + 3, kMaxM = 19;
int n, m, t, r[kMaxN], a[kMaxN], b[kMaxN], q[kMaxN], p[2][kMaxM][kMaxN], d[2][kMaxM][kMaxN];
vector<int> e[kMaxN];

int Ask(int x, int y, bool o) {
  int ans = 0;
  for (int i = kMaxM - 1; i >= 0; i--) {
    if (x != y && (LL)(p[o][i][x] - y) * (x - y) >= 0) {
      ans = max(ans, d[o][i][x]), x = p[o][i][x];
    }
  }
  return ans;
}

int main() {
  cin >> n >> m >> r[1];
  for (int i = 1; i <= n; i++) {
    cin >> r[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  n++, r[n] = n;
  for (int i = n; i >= 1; i--) {
    for (; t && (r[q[t]] < r[i] || i == 1); t--) {
      p[0][0][q[t]] = i;
    }
    q[++t] = i;
  }
  t = 0, p[0][0][1] = 1, p[1][0][n] = n;
  for (int i = 1; i <= n; i++) {
    for (; t && r[q[t]] < r[i]; t--) {
      p[1][0][q[t]] = i, e[i].push_back(q[t]);
    }
    q[++t] = i;
  }
  for (int i = 1; i < kMaxM; i++) {
    for (int j = 1; j <= n; j++) {
      p[0][i][j] = p[0][i - 1][p[0][i - 1][j]];
      p[1][i][j] = p[1][i - 1][p[1][i - 1][j]];
    }
  }
  for (int i = 1; i <= n; i++) {
    d[0][0][i] = max(a[i - 1], Ask(i - 1, p[0][0][i], 0));
    for (int j : e[i]) {
      if (j >= p[0][0][i]) {
        d[0][0][i] = min(d[0][0][i], max(b[j], Ask(j, p[0][0][i], 0)));
      }
    }
    for (int j = 1; j < kMaxM; j++) {
      d[0][j][i] = max(d[0][j - 1][i], d[0][j - 1][p[0][j - 1][i]]);
    }
  }
  for (int i = n; i >= 1; i--) {
    d[1][0][i] = min(max(a[i], Ask(i + 1, p[1][0][i], 1)), b[i]);
    for (int j = 1; j < kMaxM; j++) {
      d[1][j][i] = max(d[1][j - 1][i], d[1][j - 1][p[1][j - 1][i]]);
    }
  }
  for (int i = 1, x, y, ans; i <= m; i++) {
    cin >> x >> y;
    ans = 0;
    for (int j = kMaxM - 1; j >= 0; j--) {
      if (p[1][j][x] <= y) {
        ans = max(ans, d[1][j][x]), x = p[1][j][x];
      }
    }
    for (int j = kMaxM - 1; j >= 0; j--) {
      if (p[0][j][y] >= x) {
        ans = max(ans, d[0][j][y]), y = p[0][j][y];
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
