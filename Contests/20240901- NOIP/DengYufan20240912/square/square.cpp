#include <fstream>

using namespace std;

ifstream cin("square.in");
ofstream cout("square.out");

const int kMaxN = 501;
int n, m, k, a[kMaxN][kMaxN], c[kMaxN], ans[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  for (int u = 1 - n; u < 0; u++) {
    k = 0, fill(&c[1], &c[n] + 1, 0);
    for (int i1 = 1, j1 = 1 - u, i2 = i1, j2 = j1; j1 <= n; i1++, j1++) {
      for (; j2 <= n && k <= m; i2++, j2++) {
        for (int o = j1; o <= j2; o++) {
          k += !c[a[i2][o]]++;
        }
        for (int o = i1; o < i2; o++) {
          k += !c[a[o][j2]]++;
        }
      }
      ans[i1][j1] = k <= m ? j2 - j1 : j2 - j1 - 1;
      for (int o = j1; o < j2; o++) {
        k -= !--c[a[i1][o]];
      }
      for (int o = i1 + 1; o < i2; o++) {
        k -= !--c[a[o][j1]];
      }
    }
  }
  for (int u = 0; u < n; u++) {
    k = 0, fill(&c[1], &c[n] + 1, 0);
    for (int i1 = 1 + u, j1 = 1, i2 = i1, j2 = j1; i1 <= n; i1++, j1++) {
      for (; i2 <= n && k <= m; i2++, j2++) {
        for (int o = j1; o <= j2; o++) {
          k += !c[a[i2][o]]++;
        }
        for (int o = i1; o < i2; o++) {
          k += !c[a[o][j2]]++;
        }
      }
      ans[i1][j1] = k <= m ? i2 - i1 : i2 - i1 - 1;
      for (int o = j1; o < j2; o++) {
        k -= !--c[a[i1][o]];
      }
      for (int o = i1 + 1; o < i2; o++) {
        k -= !--c[a[o][j1]];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << ans[i][j] << " \n"[j == n];
    }
  }
  return 0;
}
