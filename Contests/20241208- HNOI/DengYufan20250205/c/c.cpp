#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 302, kInf = 1e9;
int n, m, l[kMaxN], u[kMaxN], x[kMaxN], y[kMaxN];
int c[kMaxN][kMaxN], f[kMaxN][kMaxN];
bool a[kMaxN][kMaxN];
vector<int> v[kMaxN];

int C(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2) {
    return 0;
  }
  int ans = c[x2][y2] - c[x1 - 1][y2] - c[x2][y1 - 1] + c[x1 - 1][y1 - 1];
  ans -= x[x2] * (y2 - y1 + 1) + y[y2] * (x2 - x1 + 1) - x[x2] * y[y2];
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j], a[i][j] && (l[i] = j, u[j] = i);
      c[i][j] = c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1] + !a[i][j];
    }
  }
  for (int i = n; i >= 1; i--) {
    v[l[i]].push_back(i);
    for (int k = i; k <= n; k++) {
      x[k] = k - i + 1;
    }
    for (int k = 1; k <= m; k++) {
      y[k] = 0;
    }
    for (int j = m; j >= 1; j--) {
      for (int t : v[j]) {
        for (int k = t; k <= n; k++) {
          x[k]--;
        }
      }
      if (u[j] < i) {
        for (int k = j; k <= m; k++) {
          y[k]++;
        }
      }
      f[i][j] = kInf;
      for (int k = n + 1, p = j; k >= i; k--) {
        p = max(p, l[k] + 1);
        f[i][j] = min(f[i][j], f[k][j] + f[i][p] + C(i, j, k - 1, p - 1));
        f[i][j] = min(f[i][j], f[k][j] + C(i, j, k - 1, m));
      }
      for (int k = m + 1, p = i; k >= j; k--) {
        p = max(p, u[k] + 1);
        f[i][j] = min(f[i][j], f[i][k] + f[p][j] + C(i, j, p - 1, k - 1));
        f[i][j] = min(f[i][j], f[i][k] + C(i, j, n, k - 1));
      }
    }
  }
  cout << f[1][1] << '\n';
  return 0;
}
