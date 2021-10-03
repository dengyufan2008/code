#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int d, f[1001][501][501];
string s;

int main() {
  freopen("bbreeds.in", "r", stdin);
  // freopen("bbreeds.out", "w", stdout);
  cin >> s;
  for (int i = 0; i < s.length(); i++) {
    d += s[i] == '(' ? 1 : -1;
  }
  if (d != 0) {
    cout << 0 << endl;
    return 0;
  }
  f[0][1][0] = f[0][0][1] = s[0] == '(';
  for (int i = 1; i < s.length(); i++) {
    for (int j = 0; j < s.length() / 2; j++) {
      for (int k = 0; k < s.length() / 2; k++) {
        if (s[i] == '(') {
          f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k] + f[i - 1][j][k - 1]) % 2012;
        } else {
          f[i][j][k] = (f[i][j][k] + f[i - 1][j + 1][k] + f[i - 1][j][k + 1]) % 2012;
        }
      }
    }
  }
  cout << f[s.length() - 1][0][0] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
