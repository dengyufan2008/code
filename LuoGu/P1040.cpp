#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, a[31], f[31][31], s[31][31];

void Print(int l, int r) {
  cout << s[l][r] << " ";
  if (l < s[l][r]) {
    Print(l, s[l][r] - 1);
  }
  if (s[l][r] < r) {
    Print(s[l][r] + 1, r);
  }
}

int main() {
  cin >> n;
  fill(&f[0][0], &f[30][30] + 1, 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[i][i] = a[i];
    s[i][i] = i;
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      for (int l = j; l <= k; l++) {
        if (f[j][k] < f[j][l - 1] * f[l + 1][k] + a[l]) {
          f[j][k] = f[j][l - 1] * f[l + 1][k] + a[l];
          s[j][k] = l;
        }
      }
    }
  }
  cout << f[1][n] << endl;
  Print(1, n);
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
