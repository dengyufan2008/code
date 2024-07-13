#include <iostream>
#define LL long long

using namespace std;

int m, n, k, a[10001];
bool f[10001][101];

int main() {
  cin >> m;
  while (m--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    fill(&f[0][0], &f[10000][100] + 1, 0);
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k; j++) {
        f[i + 1][((j + a[i + 1]) % k + k) % k] |= f[i][j];
        f[i + 1][((j - a[i + 1]) % k + k) % k] |= f[i][j];
      }
    }
    cout << (f[n][0] ? "Divisible" : "Not divisible") << endl;
  }
  return 0;
}
