#include <fstream>

using namespace std;

ifstream cin("o.in");
ofstream cout("o.ans");

const int kMaxN = 1001, kInf = 1e9;
int n, m, d[kMaxN][kMaxN];
long long ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      d[i][j] = kInf;
    }
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    d[x][y] = d[y][x] = z;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      ans += d[i][j];
    }
  }
  cout << ans << '\n';
  return 0;
}
