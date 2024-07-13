/*
ID: dengyuf1
TASK: prefix
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

int n;
bool f[200001] = {1};
string tot = " ", tmp, s[251];

int main() {
  freopen("prefix.in","r",stdin);
  freopen("prefix.out","w",stdout);
  while (1) {
    cin >> s[++n];
    if (s[n] == ".") {
      break;
    }
  }
  while (cin >> tmp) {
    tot += tmp;
  }
  for (int i = 1; i <= tot.size() - 1; i++) {
    for (int j = 1; j < n; j++) {
      f[i] |= (i - s[j].size() >= 0 && f[i - s[j].size()] && tot.substr(i + 1 - s[j].size(), s[j].size()) == s[j]);
    }
  }
  for (int i = tot.size() - 1; i >= 0; i--) {
    if (f[i]) {
      cout << i << endl;
      break;
    }
  }
  return 0;
}
