#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, m, ans, three[11] = {1}, f[2][59050];
bool b;
char a[100][10];

int main() {
  cin >> n >> m;
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (LL i = 1; i <= 10; i++) {
    three[i] = three[i - 1] * 3;
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      fill(&f[b][0], &f[b][three[m]], 0);
      b ^= 1;
      for (LL k = 0; k < three[m]; k++) {
        LL x = (j > 1) * k / three[max(j - 2, 0LL)] % 3, y = (j > 0) * k / three[max(j - 1, 0LL)] % 3, z = k / three[j] % 3;
        f[b ^ 1][k - (z - (z == 1) * 2) * three[j]] = max(f[b ^ 1][k - (z - (z == 1) * 2) * three[j]], f[b][k]);
        if (x != 1 && y != 1 && !z && a[i][j] == 'P') {
          f[b ^ 1][k - (z - 1) * three[j]] = max(f[b ^ 1][k - (z - 1) * three[j]], f[b][k] + 1);
        }
      }
    }
  }
  for (LL i = 0; i < three[m]; i++) {
    ans = max(ans, f[b ^ 1][i]);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
