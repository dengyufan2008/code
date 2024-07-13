#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, f[100][100];
string s;

int M(int x) {
  int c = 0;
  while (x) {
    c++;
    x /= 10;
  }
  return c;
}

int C(int x, int y, int l) {
  for (int i = x + l; i <= y; i += l) {
    if ((y - x + 1) % l || s.substr(i - l, l) != s.substr(i, l)) {
      return y - x + 1;
    }
  }
  return M((y - x + 1) / l) + f[x][x + l - 1] + 2;
}

int main() {
  cin >> s;
  n = s.length();
  for (int i = 0; i < n; i++) {
    f[i][i] = 1;
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 0, k; (k = j + i - 1) < n; j++) {
      f[j][k] = i;
      for (int l = j; l < k; l++) {
        f[j][k] = min(f[j][k], C(j, k, l - j + 1));
      }
      for (int l = j; l < k; l++) {
        f[j][k] = min(f[j][k], f[j][l] + f[l + 1][k]);
      }
    }
  }
  cout << f[0][n - 1] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
