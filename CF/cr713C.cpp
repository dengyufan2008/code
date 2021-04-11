#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, a, b, n[2], s[400001];
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> a >> b;
    n[0] = a, n[1] = b;
    for (int i = 1; i <= a + b; i++) {
      cin >> ch;
      s[i] = (ch == '?' ? -1 : ch - '0');
      n[s[i]]--;
    }
    if (a % 2 && b % 2) {
      cout << -1 << endl;
      continue;
    }
    for (int i = 1; i <= (a + b) / 2; i++) {
      if (s[i] == -1 && s[a + b - i + 1] != -1) {
        s[i] = s[a + b - i + 1];
        n[s[i]]--;
      }
      if (s[i] != -1 && s[a + b - i + 1] == -1) {
        s[a + b - i + 1] = s[i];
        n[s[i]]--;
      }
      if (s[i] != -1 && s[a + b - i + 1] != -1 && s[i] != s[a + b - i + 1]) {
        n[0] = -1;
        break;
      }
    }
    if (n[0] < 0 || n[1] < 0) {
      cout << -1 << endl;
      continue;
    }
    for (int i = 1; i <= (a + b) / 2; i++) {
      if (s[i] == -1) {
        s[i] = s[a + b - i + 1] = n[0] < 2;
        n[s[i]] -= 2;
      }
    }
    if ((a + b) % 2 && s[(a + b) / 2 + 1] == -1) {
      s[(a + b) / 2 + 1] = n[1];
    }
    for (int i = 1; i <= a + b; i++) {
      cout << s[i];
    }
    cout << endl;
  }
  return 0;
}
