#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, ans, f[51][51], _f[51];
string s;

int C(int x, int y) {
  if ((y - x + 1) & 1) {
    return 114514;
  }
  int l = (y - x + 1) / 2;
  for (int i = x; i < x + l; i++) {
    if (s[i] != s[i + l]) {
      return 114514;
    }
  }
  return f[x][x + l - 1];
}

int main() {
  cin >> s;
  n = s.length(), ans = n;
  for (int i = 0; i < n; i++) {
    f[i][i] = 1;
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 0, k; (k = j + i - 1) < n; j++) {
      f[j][k] = min(i, min(f[j][k - 1] + 1, C(j, k) + 1));
    }
  }
  for (int i = 0; i < n; i++) {
    _f[i] = f[0][i];
    for (int j = 0; j < i; j++) {
      _f[i] = min(_f[i], _f[j] + 1 + f[j + 1][i]);
    }
  }
  cout << _f[n - 1] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
