// by wls
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, D = 1e5 + 5;
int n;
char s[N];
set<pair<int, int>> st;
int dx[4] = {1, 0, -1, 0},
    dy[4] = {0, 1, 0, -1};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    st.clear();
    cin >> n >> s;
    int x = 0, y = 0, p = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (st.count(make_pair(x, y))) {
        ans = -1;
        break;
      }
      if (s[i] == 'L') {
        st.emplace(x, y);
        (p += 1) %= 4;
        x += dx[p], y += dy[p];
      } else if (s[i] == 'R') {
        st.emplace(x, y);
        (p += 3) %= 4;
        x += dx[p], y += dy[p];
      } else {
        st.emplace(x, y);
        x += dx[p], y += dy[p];
      }
    }
    if (ans != -1 && x == 0 && y == 0 && p == 0) ans = 1;
    cout << ans << '\n';
  }
  return 0;
}
