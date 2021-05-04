/*
ID: dengyuf1
TASK: crypt1
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans, a[11];
bool b[10];

bool C(int x, int d) {
  int k = 0, c[6] = {};
  while (x) {
    c[++k] = x % 10, x /= 10;
  }
  if(k != d) {
    return false;
  }
  for (int i = 1; i <= k; i++) {
    if (!b[c[i]]) {
      return false;
    }
  }
  return true;
}

int main() {
  freopen("crypt1.in", "r", stdin);
  freopen("crypt1.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[a[i]] = true;
  }
  for (int i1 = 1, tmp; i1 <= n; i1++) {
    for (int i2 = 1; i2 <= n; i2++) {
      for (int i3 = 1; i3 <= n; i3++) {
        for (int j1 = 1; j1 <= n; j1++) {
          for (int j2 = 1; j2 <= n; j2++) {
            tmp = a[i1] * 100 + a[i2] * 10 + a[i3];
            ans += C(tmp * a[j1], 3) && C(tmp * a[j2], 3) && C(tmp * (a[j1] * 10 + a[j2]), 4);
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
