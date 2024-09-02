#include <fstream>

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 3001;
int t, n, m, w[11], a[kMaxN], b[kMaxN], f[kMaxN], g[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    fill(&f[0], &f[kMaxN], 0), fill(&g[0], &g[kMaxN], 0);
    for (int i = 1; i <= 10; i++) {
      cin >> w[i];
    }
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= m - a[i]; j++) {
        f[a[i] + j] = max(f[a[i] + j], f[j] + b[i]);
      }
    }
    for (int i = 1; i <= m; i++) {
      int _w = w[(10 * f[i] + i - 1) / i];
      for (int j = 0; j <= m; j++) {
        g[i + j] = max(g[i + j], g[j] + _w * i);
      }
    }
    cout << g[m] << '\n';
  }
  return 0;
}
