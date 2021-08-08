#include <iostream>
#define LL long long

using namespace std;

LL f[3001][3001], p[3001][3001];
string s, t, ans;

int main() {
  cin >> s >> t;
  for (LL i = 1; i <= s.length(); i++) {
    for (LL j = 1; j <= t.length(); j++) {
      if (s[i - 1] == t[j - 1]) {
        f[i][j] = f[i - 1][j - 1] + 1, p[i][j] = 1;
      } else {
        if (f[i - 1][j] >= f[i][j - 1]) {
          f[i][j] = f[i - 1][j], p[i][j] = 2;
        } else {
          f[i][j] = f[i][j - 1], p[i][j] = 3;
        }
      }
    }
  }
  for (LL x = s.length(), y = t.length(); x || y;) {
    if (p[x][y] == 1) {
      ans = s[--x] + ans, y--;
    } else if (p[x][y] == 2) {
      x--;
    } else {
      y--;
    }
  }
  cout << ans << endl;
  return 0;
}
