#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, s[2], a[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    s[0] = s[1] = 0;
    for (LL i = n; i >= 1; i--) {
      s[(n - i) % 2] += a[i] % 2 == (n - i) % 2 ? a[i] : 0;
    }
    if (s[0] > s[1]) {
      cout << "Alice" << endl;
    } else if (s[0] < s[1]) {
      cout << "Bob" << endl;
    } else {
      cout << "Tie" << endl;
    }
  }
  return 0;
}
