#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n;
char s[51];
bool flag, b[26];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    flag = true;
    fill(&b[0], &b[25] + 1, false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> s[i];
    }
    for (int i = 1; i <= n; i++) {
      if (b[s[i] - 'A'] && s[i] != s[i - 1]) {
        flag = false;
      } else {
        b[s[i] - 'A'] = true;
      }
    }
    cout << (flag ? "YES" : "NO") << endl;
  }
  return 0;
}
