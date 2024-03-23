#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

LL n, ans;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s;
  n = s.size(), s = '~' + s, ans = -1;
  for (int i = 1; i <= n; ans++) {
    int c = s[i] + s[i + 1] - 96;
    if (c > 9) {
      s[i] = c / 10 + 48, s[i + 1] = c % 10 + 48;
    } else {
      s[++i] = c + 48;
    }
  }
  cout << ans;
  return 0;
}
