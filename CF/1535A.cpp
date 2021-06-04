#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, a, b, s[5];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    a = b = 0;
    for (int i = 1; i <= 4; i++) {
      cin >> s[i];
    }
    for (int i = 1; i <= 4; i++) {
      if (s[i] > s[a]) {
        b = a, a = i;
      } else if (s[i] > s[b]) {
        b = i;
      }
    }
    cout << (a + b == 3 || a == 3 && b == 4 || a == 4 && b == 3 ? "NO" : "YES") << endl;
  }
  return 0;
}
