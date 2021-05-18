#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, _p, _c, p[5001], c[5001], f[5001][5001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, tmp; i <= n; i++) {
    cin >> tmp;
    if (tmp) {
      p[++_p] = i;
    } else {
      c[++_c] = i;
    }
  }
  for (int i = 1; i <= _p; i++) {
    f[i][0] = 1e9;
    for (int j = 1; j <= _c; j++) {
      f[i][j] = min(f[i][j - 1], f[i - 1][j - 1] + abs(p[i] - c[j]));
    }
  }
  cout << f[_p][_c] << endl;
  return 0;
}
