#include <bits/stdc++.h>
#define LL long long

using namespace std;

int k, ans;
string s;

bool C(int x) {
  bool b[10] = {};
  b[x % 10] = b[x / 10 % 10] = b[x / 100 % 10] = b[x / 1000] = true;
  for (int i = 0; i <= 9; i++) {
    if (s[i] == 'o' && !b[i] || s[i] == 'x' && b[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> s;
  for (int i = 0; i <= 9; i++) {
    k += s[i] == 'o';
  }
  for (int i = 0; i <= 9999; i++) {
    ans += C(i);
  }
  cout << ans;
  return 0;
}
