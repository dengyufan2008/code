#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, l, ans, b[100001];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> s;
    ans = 0, l = s.length();
    for (int i = 0; i < l - 1; i++) {
      if (s[i] == s[i + 2] && b[i] != t + 1) {
        ans++;
        b[i + 2] = t + 1;
      } else if (s[i] == s[i + 1] && b[i] != t + 1) {
        ans++;
        b[i + 1] = t + 1;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
