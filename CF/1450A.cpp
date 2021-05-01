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
    sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++) {
      cout << s[i];
    }
    cout << endl;
  }
  return 0;
}
