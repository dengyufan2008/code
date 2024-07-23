// by wls
#include <bits/stdc++.h>
using namespace std;
string s;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> s;
    int p0 = -1, p1 = -1;
    for (int i = 0; i < s.size(); i++) {
      if (s.substr(i, 3) == "://") {
        p0 = i - 1;
        break;
      }
    }
    cout << s.substr(0, p0 + 1) << '\n';
    for (int i = p0 + 4; i < s.size(); i++) {
      if (s[i] == '/') {
        p1 = i - 1;
        break;
      }
    }
    cout << s.substr(p0 + 4, p1 - p0 - 3) << '\n';
    int lst = p1 + 2, p = lst;
    bool flg = 0;
    while (p < s.size()) {
      flg |= (s[p] == '=');
      if (s[p] == '/') {
        if (flg) cout << s.substr(lst, p - lst) << '\n';
        lst = p + 1;
        flg = 0;
      }
      ++p;
    }
  }
  return 0;
}
