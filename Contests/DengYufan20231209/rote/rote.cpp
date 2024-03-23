#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("rote.in");
ofstream cout("rote.out");

const int kMaxN = 13, kMaxM = 2001, kInf = 1e9;
int t, n, m, a[kMaxN][kMaxM], l[kMaxM], d[kMaxN][1 << kMaxN], f[kMaxN][1 << kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fill(&f[0][1], &f[0][1 << kMaxN], -kInf);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
      }
    }
    for (int i = 1; i <= m; i++) {
      l[i] = i, a[n][i] = 0;
      for (int j = 0; j < n; j++) {
        a[n][i] = max(a[n][i], a[j][i]);
      }
    }
    sort(l + 1, l + m + 1, [](int i, int j) { return a[n][i] > a[n][j]; });
    m = min(m, n);
    for (int i = 1; i <= m; i++) {
      for (int s = 0; s < (1 << n); s++) {
        d[i][s] = f[i][s] = 0;
        for (int j = 0; j < n; j++) {
          int c = 0;
          for (int k = 0; k < n; k++) {
            if (s >> (j + k) % n & 1) {
              c += a[k][l[i]];
            }
          }
          d[i][s] = max(d[i][s], c);
        }
      }
    }
    for (int i = 1; i <= m; i++) {
      for (int s = 0; s < (1 << n); s++) {
        for (int t = s; t < (1 << n); t = t + 1 | s) {
          f[i][t] = max(f[i][t], f[i - 1][s] + d[i][s ^ t]);
        }
      }
    }
    cout << f[m][~(-1 << n)] << '\n';
  }
  return 0;
}
