#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, ans, f[251][251];

int main() {
  cin >> n;
  fill(&f[0][0], &f[250][250] + 1, -1);
  for (int i = 1; i <= n; i++) {
    cin >> f[i][i];
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      for (int l = j; l < k; l++) {
        if (f[j][l] != -1 && f[l + 1][k] != -1 && f[j][l] == f[l + 1][k]) {
          f[j][k] = max(f[j][k], f[j][l] + 1);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      ans = max(ans, f[j][k]);
    }
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
