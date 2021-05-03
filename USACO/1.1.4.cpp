/*
ID: dengyuf1
TASK: beads
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, a, b, w, ans;
char s[700], c;

int main() {
  freopen("beads.in", "r", stdin);
  freopen("beads.out", "w", stdout);
  cin >> n >> s;
  copy(&s[0], &s[n - 1] + 1, &s[n]);
  for (int i = 0; i < (n << 1); i++) {
    if (s[i] == 'w') {
      b++;
      w++;
    } else if (s[i] == c) {
      b++;
      w = 0;
    } else {
      ans = max(ans, a + b);
      a = b - w, b = w + 1;
      w = 0;
      c = s[i];
    }
  }
  ans = max(ans, a + b);
  cout << min(ans, n) << endl;
  return 0;
}
