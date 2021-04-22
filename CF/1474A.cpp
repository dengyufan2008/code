#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n >> s;
    cout << 1, s[0]++;
    for (int i = 1; i < n; i++) {
      cout << (s[i - 1] != s[i] + 1);
      s[i] += s[i - 1] != s[i] + 1;
    }
    cout << endl;
  }
  return 0;
}
