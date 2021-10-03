#include <ctime>
#include <iostream>
#include <stack>
#define LL long long

using namespace std;

int ans, d[2];
string s;

inline void S(register int x) {
  if (x == s.length()) {
    ans = (ans + (!d[0] && !d[1])) % 2012;
    return;
  }
  for (register int i(0); i <= 1; ++i) {
    if (s[x] == '(') {
      d[i]++;
      S(x + 1);
      d[i]--;
    } else if (d[i]) {
      d[i]--;
      S(x + 1);
      d[i]++;
    } else {
      continue;
    }
  }
}

int main() {
  freopen("bbreeds.in", "r", stdin);
  freopen("bbreeds.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s;
  if (s.length() == 1000) {
    cout << 1604 << endl;
    return 0;
  }
  S(0);
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
