#include <iostream>
#define LL long long

using namespace std;

LL n, w, s, ans = -1145141919810, a[5001], lg[5001], d[10001][14], f[2][5001];

int main() {
  cin >> n >> w >> s;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1, p = 0; i <= 5000; i++) {
    lg[i] = p += i == 1 << p + 1;
  }
  for (LL i = 1; i <= n; i++) {
    fill(&f[1][0], &f[1][w] + 1, -1145141919810);
    for (LL j = 1; j <= min(i, w); j++) {
      f[1][j] = max(d[j - 1][lg[min(i - j, s) + 1]], d[j + min(i - j, s) - (1 << lg[min(i - j, s) + 1])][lg[min(i - j, s) + 1]]) + a[i] * j;
    }
    fill(&d[0][0], &d[5000][13] + 1, -1145141919810);
    copy(&f[1][0], &f[1][w] + 1, &f[0][0]);
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
