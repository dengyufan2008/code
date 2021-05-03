/*
ID: dengyuf1
TASK: beads
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans;
char s[351];

int M(int i) {
  int x = 0, d = 0;
  char c = 'a';
  for (; d <= 2; i++) {
    if (s[i] != c && s[i] != 'w') {
      d++;
    }
    c = s[i] == 'w' ? c : s[i];
    ans++;
  }
  return ans;
}

int main() {
  // freopen("beads.in", "r", stdin);
  // freopen("beads.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
  }
  for (int i = 1; i <= n; i++) {
    ans = max(ans, M(i));
  }
  cout << ans << endl;
  return 0;
}
