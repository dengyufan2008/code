#include <iostream>
#define LL long long

using namespace std;

int l1, l2, nt[1000001];
bool flag;
string s1, s2;

int main() {
  freopen("censor.in", "r", stdin);
  freopen("censor.out", "w", stdout);
  cin >> s1 >> s2;
  l1 = s1.length(), l2 = s2.length();
  do {
    flag = 0;
    for (int i = 1, l; i < l2; i++) {
      for (l = nt[i]; l && s2[l] != s2[i]; l = nt[l]) {
      }
      nt[i + 1] = l + (s2[l] == s2[i]);
    }
    for (int i = -1, j = -1; i < l1 - l2;) {
      for (; s1[j + 1] == s2[j - i] && j - i < l2; j++) {
      }
      if (j - i == l2) {
        flag = 1;
        for (int k = i + 1; k < l1 - l2; k++) {
          s1[k] = s1[k + l2];
        }
        l1 -= l2;
        break;
      }
      i = i == j ? ++j : j - nt[j - i];
    }
  } while (flag);
  for (int i = 0; i < l1; i++) {
    cout << s1[i];
  }
  return 0;
}
