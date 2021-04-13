#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> s;
  for (int i = 0, j = 1; i < n; i += j, j++) {
    cout << s[i];
  }
  return 0;
}
