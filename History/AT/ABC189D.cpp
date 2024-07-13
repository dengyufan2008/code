#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, f[61][2];
string s[61];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  fill(&f[0][0], &f[60][1] + 1, 1);
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    f[i][0] = f[i - 1][0] + (f[i - 1][0] + f[i - 1][1]) * (s[i] == "AND");
    f[i][1] = f[i - 1][1] + (f[i - 1][0] + f[i - 1][1]) * (s[i] == "OR");
  }
  cout << f[n][1] << endl;
  return 0;
}
