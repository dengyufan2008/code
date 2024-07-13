#include <bits/stdc++.h>
#define LL long long

using namespace std;

int l, d[10];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> s;
  l = s.length();
  if (l == 1) {
    cout << (!(stoi(s) % 8) ? "Yes" : "No") << endl;
  } else if (l == 2) {
    if (!(stoi(s) % 8)) {
      cout << "Yes" << endl;
      return 0;
    }
    swap(s[0], s[1]);
    cout << (!(stoi(s) % 8) ? "Yes" : "No") << endl;
  } else {
    for (int i = 0; i < l; i++) {
      d[s[i] - '0']++;
    }
    for (int i = 104; i <= 996; i += 8) {
      int _d[10] = {};
      _d[i / 100]++, _d[i / 10 % 10]++, _d[i % 10]++;
      for (int j = 0; j <= 9; j++) {
        if (d[j] >= _d[j]) {
          cout << "Yes" << endl;
          return 0;
        }
      }
    }
    cout << "No" << endl;
  }
  return 0;
}
