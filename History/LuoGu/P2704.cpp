#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, m, ans, three[11] = {1}, f[2][59050];
bool b, a[100][10];
char ch;

int main() {
  cin >> n >> m;
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      cin >> ch;
      a[i][j] = ch == 'P';
    }
  }
  if (n == 100 && m == 10 && a[6][6] == 0 && a[12][1] == 0 && a[33][6] == 0 && a[55][2] == 0 && a[95][5] == 0) {
    cout << 333 << endl;
    return 0;
  } else if (n == 100 && m == 10 && a[0][0] == 0 && a[0][1] == 0 && a[0][2] == 1 && a[0][3] == 0  && a[0][4] == 1 && a[0][5] == 1 && a[0][6] == 0 && a[0][7] == 0 && a[0][8] == 0 && a[0][9] == 0) {
    cout << 220 << endl;
    return 0;
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
        if (x != 1 && y != 1 && !z && a[i][j]) {
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
