#include <iostream>
#define LL long long

using namespace std;

LL n, w, s, ans = -1145141919810, a[5001], d[10001][14], f[2][5001];

int main() {
  cin >> n >> w >> s;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1; i <= n; i++) {
    fill(&f[1][0], &f[1][5000] + 1, -1145141919810);
    for (LL j = 1; j <= min(i, w); j++) {
      LL c = -1145141919810;
      for (LL k = 13, p = j - 1; k >= 0; k--) {
        if (p + (1 << k) <= j + min(i - j, s)) {
          c = max(c, d[p][k]), p += 1 << k;
        }
      }
      f[1][j] = c + a[i] * j;
    }
    fill(&d[0][0], &d[5000][14], -1145141919810);
    copy(&f[1][0], &f[1][5000] + 1, &f[0][0]);
    for (LL j = 0; j <= min(i, w); j++) {
      d[j][0] = f[1][j];
    }
    for (LL j = 1; j <= 13; j++) {
      for (LL k = 0; k <= min(i, w); k++) {
        d[k][j] = max(d[k][j - 1], d[k + (1 << (j - 1))][j - 1]);
      }
    }
  }
  for (LL i = 0; i <= w; i++) {
    ans = max(ans, f[1][i]);
  }
  cout << ans << endl;
  return 0;
}
