#include <iostream>
#define LL long long

using namespace std;

int n, m;
string s, t;

bool C() {
  for (int i = 0, j = 0; i < n || j < m;) {
    if (s[i] != t[j]) {
      return 0;
    }
    if (s[i] != s[i + 1]) {
      i++, j++;
    } else {
      int _i = i, _j = j;
      while (s[_i] == t[j]) {
        _i++;
      }
      while (s[i] == t[_j]) {
        _j++;
      }
      if (_i - i > _j - j) {
        return 0;
      }
      i = _i, j = _j;
    }
  }
  return 1;
}

int main() {
  cin >> s >> t;
  n = s.size(), m = t.size();
  cout << (C() ? "Yes" : "No");
  return 0;
}
