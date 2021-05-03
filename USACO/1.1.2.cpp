/*
ID: dengyuf1
TASK: gift1
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, a[11];
string tmp, s[11];

int main() {
  freopen("gift1.in", "r", stdin);
  freopen("gift1.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
  }
  for (int i = 1, m, k; i <= n; i++) {
    cin >> tmp >> m >> k;
    for (int j = 1; j <= n; j++) {
      if (s[j] == tmp) {
        a[j] -= m - (m % max(k, 1));
        break;
      }
    }
    for (int j = 1; j <= k; j++) {
      cin >> tmp;
      for (int l = 1; l <= n; l++) {
        if (s[l] == tmp) {
          a[l] += m / k;
          break;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << s[i] << " " << a[i] << endl;
  }
  return 0;
}
