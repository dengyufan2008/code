/*
ID: dengyuf1
TASK: barn1
LANG: C++                 
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int m, s, c, k, tot, a[201], d[201];

int main() {
  freopen("barn1.in", "r", stdin);
  freopen("barn1.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> m >> s >> c;
  for (int i = 1; i <= c; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + c + 1);
  for (int i = 2; i <= c; i++) {
    if (a[i] - a[i - 1] >= 2) {
      d[++k] = a[i] - a[i - 1] - 1;
    }
  }
  sort(d + 1, d + k + 1);
  for (int i = 1; i <= k - m + 1; i++) {
    tot += d[i];
  }
  cout << tot + c << endl;
  return 0;
}
