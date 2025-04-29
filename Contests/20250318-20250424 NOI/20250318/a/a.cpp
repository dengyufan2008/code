#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMaxM = 1e3;
int n, m;
double s, w, ans, a[kMaxN], f[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1, greater<double>());
  f[0] = 1;
  for (int i = 1; i <= n; i++) {
    int l = max((int)s - kMaxM, 0), r = min((int)s + kMaxM, i - 1);
    for (int j = r + 1; j > l; j--) {
      f[j] = f[j] * (1 - a[i]) + f[j - 1] * a[i];
    }
    f[l] *= 1 - a[i], w = 0;
    for (int j = max(l, i + m + 1 >> 1); j <= r + 1; j++) {
      w += f[j];
    }
    ans = max(ans, w), s += a[i];
  }
  cout << fixed << setprecision(12) << ans << '\n';
  return 0;
}
