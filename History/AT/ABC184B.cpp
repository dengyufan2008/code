#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, x;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> x >> s;
  for (int i = 0; i < n; i++) {
    x = max(x + (s[i] == 'o' ? 1 : -1), 0);
  }
  cout << x << endl;
  return 0;
}
