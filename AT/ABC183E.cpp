#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int M = 1000000007;

int h, w, x[2001][2001], y[2001][2001], z[2001][2001], f[2001][2001];
char s[2001][2001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> s[i][j];
    }
  }
  f[1][1] = 1;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      if (i == 1 && j == 1 || s[i][j] == '#') {
        continue;
      }
      if (i > 0) {
        y[i][j] = (y[i - 1][j] + f[i - 1][j]) % M;
      }
      if (j > 0) {
        x[i][j] = (x[i][j - 1] + f[i][j - 1]) % M;
      }
      if (i > 0 && j > 0) {
        z[i][j] = (z[i - 1][j - 1] + f[i - 1][j - 1]) % M;
      }
      f[i][j] = ((LL)x[i][j] + y[i][j] + z[i][j]) % M;
    }
  }
  cout << f[h][w] << endl;
  return 0;
}
