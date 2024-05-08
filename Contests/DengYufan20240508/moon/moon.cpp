#include <fstream>

using namespace std;

ifstream cin("moon.in");
ofstream cout("moon.out");

const int kMaxN = 501;
const double kEps = 1e-6;
int n, m, ans1, ans2, a[kMaxN];
double d[kMaxN][kMaxN], w[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    w[i][i] = 1;
    for (int j = 1, x; j <= a[i]; j++) {
      cin >> x, d[i][x] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= m; j++) {
      if (abs(d[j][i]) > kEps) {
        swap(d[i], d[j]), swap(w[i], w[j]);
        break;
      }
    }
    if (abs(d[i][i]) <= kEps) {
      continue;
    }
    for (int j = 1; j <= m; j++) {
      w[i][j] /= d[i][i];
    }
    for (int j = n; j >= i; j--) {
      d[i][j] /= d[i][i];
    }
    for (int j = i + 1; j <= m; j++) {
      for (int k = 1; k <= m; k++) {
        w[j][k] -= d[j][i] * w[i][k];
      }
      for (int k = n; k >= i; k--) {
        d[j][k] -= d[j][i] * d[i][k];
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (abs(w[n + 1][i]) > kEps) {
      w[n + 1][i] > 0 ? ans1++ : ans2++;
    }
  }
  cout << ans1 << ' ' << ans2 << '\n';
  for (int i = 1; i <= m; i++) {
    if (abs(w[n + 1][i]) > kEps && w[n + 1][i] > 0) {
      cout << i << ' ';
    }
  }
  cout << '\n';
  for (int i = 1; i <= m; i++) {
    if (abs(w[n + 1][i]) > kEps && w[n + 1][i] < 0) {
      cout << i << ' ';
    }
  }
  cout << '\n';
  return 0;
}
