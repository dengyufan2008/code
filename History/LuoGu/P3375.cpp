#include <iostream>
#define LL long long

using namespace std;

int l1, l2, nt[1000001];
string s1, s2;

int main() {
  cin >> s1 >> s2;
  l1 = s1.length(), l2 = s2.length();
  for (int i = 1, l; i < l2 ; i++) {
    for (l = nt[i]; l && s2[l] != s2[i]; l = nt[l]) {
    }
    nt[i + 1] = l + (s2[l] == s2[i]);
  }
  for (int i = -1, j = -1; i < l1 - l2;) {
    for (; s1[j + 1] == s2[j - i] && j - i < l2; j++) {
    }
    if (j - i == l2) {
      cout << i + 2 << endl;
    }
    i = i == j ? ++j : j - nt[j - i];
  }
  for (int i = 1; i <= l2; i++) {
    cout << nt[i] << " ";
  }
  return 0;
}
