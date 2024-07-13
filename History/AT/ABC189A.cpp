#include <bits/stdc++.h>
#define LL long long

using namespace std;

bool flag = true;
char s[3];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> s;
  for (int i = 0; i < 2; i++) {
    flag = flag && s[i] == s[i + 1];
  }
  cout << (flag ? "Won" : "Lost") << endl;
  return 0;
}
