#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, v[10][4], s[10];
char c[2001][2001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < 10; i++) {
      v[i][0] = v[i][1] = n;
      v[i][2] = v[i][3] = 0;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> c[i][j];
        c[i][j] -= '0';
        v[c[i][j]][0] = min(v[c[i][j]][0], i);
        v[c[i][j]][1] = min(v[c[i][j]][1], j);
        v[c[i][j]][2] = max(v[c[i][j]][2], i);
        v[c[i][j]][3] = max(v[c[i][j]][3], j);
      }
    }
    fill(s, s + 10, 0);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        s[c[i][j]] = max(s[c[i][j]], max(j - 1, n - j) * max(i - v[c[i][j]][0], v[c[i][j]][2] - i));
        s[c[i][j]] = max(s[c[i][j]], max(i - 1, n - i) * max(j - v[c[i][j]][1], v[c[i][j]][3] - j));
      }
    }
    for (int i = 0; i < 10; i++) {
      cout << s[i] << " ";
    }
    cout << endl;
  }
  return 0;
}
