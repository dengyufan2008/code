#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n;
char s[201];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> s[i];
    }
    cout << (s[1] == '2' && s[2] == '0' && s[3] == '2' && s[4] == '0' || s[1] == '2' && s[2] == '0' && s[3] == '2' && s[n] == '0' || s[1] == '2' && s[2] == '0' && s[n - 1] == '2' && s[n] == '0' || s[1] == '2' && s[n - 2] == '0' && s[n - 1] == '2' && s[n] == '0' || s[n - 3] == '2' && s[n - 2] == '0' && s[n - 1] == '2' && s[n] == '0' ? "YES" : "NO") << endl;
  }
  return 0;
}
