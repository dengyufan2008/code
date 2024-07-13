#include <iostream>

using namespace std;

int a[4];
bool b[7], _b[7];
string s[7];

bool C(string t) {
  for (int i = 1; i < 7; i++) {
    if (!_b[i] && t == s[i]) {
      _b[i] = 1;
      return 1;
    }
  }
  return 0;
}

bool C() {
  string t;
  copy(&b[0], &b[7], &_b[0]);
  for (int i = 0; i < 3; i++) {
    t = "";
    for (int j = 1; j < 4; j++) {
      t += s[a[j]][i];
    }
    if (!C(t)) {
      return 0;
    }
  }
  return 1;
}

bool S(int x) {
  if (x == 4) {
    bool b = C();
    if (b) {
      for (int i = 1; i < 4; i++) {
        cout << s[a[i]] << '\n';
      }
    }
    return b;
  }
  for (int i = 1; i < 7; i++) {
    if (!b[i]) {
      a[x] = i, b[i] = 1;
      if (S(x + 1)) {
        return 1;
      }
      b[i] = 0;
    }
  }
  return 0;
}

int main() {
  for (int i = 1; i < 7; i++) {
    cin >> s[i];
  }
  if (!S(1)) {
    cout << 0;
  }
  return 0;
}
