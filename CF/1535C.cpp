#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, ans, f[200001][2];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> s;
    for (LL i = 0; i < s.length(); i++) {
      if (s[i] == '?') {
        f[i][0] = f[i][1] = 1;
      } else {
        f[i][s[i] == '1'] = 1, f[i][s[i] != '1'] = 0;
      }
    }
    ans = max(f[0][0], f[0][1]);
    for (LL i = 1; i < s.length(); i++) {
      if (s[i] == '?') {
        f[i][0] += f[i - 1][1], f[i][1] += f[i - 1][0];
      } else {
        f[i][s[i] == '1'] += f[i - 1][s[i] != '1'];
      }
      ans += max(f[i][0], f[i][1]);
    }
    cout << ans << endl;
  }
  return 0;
}
