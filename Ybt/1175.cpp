#include <bits/stdc++.h>
#define LL long long

using namespace std;

short a[101], s[101];
string n;

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  a[0] = n.length();
  for (int i = 0; i < a[0]; i++) {
    a[i + 1] = n[i] - '0';
  }
  for (int i = 1; i <= a[0]; i++) {
    s[i] = a[i] / 13;
    a[i + 1] += a[i] % 13 * 10;
  }
  int i;
  for (i = 1; !s[i]; i++)
    ;
  for (; i <= a[0]; i++) {
    cout << s[i];
  }
  cout << "\n"
       << a[a[0]] % 13 << "\n";
  return 0;
}
