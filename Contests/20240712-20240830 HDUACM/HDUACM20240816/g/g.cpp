// by wls
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
bool flg;
set<int> st;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    flg = 0;
    for (int i = 1, ai; i <= n; i++) {
      cin >> ai;
      if (st.count(ai)) flg = 1;
      st.insert(ai);
    }
    for (int i = 1, bi; i <= n; i++) {
      cin >> bi;
    }
    cout << (flg ? "shuishui" : "sha7dow") << '\n';
    st.clear();
  }
  return 0;
}
