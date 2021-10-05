#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, a[1001], f[1001][1001];

int main() {
  cin >> n;
  fill(&f[0][0], &f[1000][1000] + 1, 0x7fffffff);
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1, k; (k = j + i - 1) <= n; j++) {
      LL _j = j, _k = k;
      while (a[_j] == a[_k] && _j <= _k) {
        _j++, _k--;
      }
      if (_j > _k) {
        f[j][k] = 1;
      } else {
        for (LL l = _j; l < _k; l++) {
          f[j][k] = min(f[j][k], f[_j][l] + f[l + 1][_k]);
        }
      }
    }
  }
  cout << f[1][n] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
