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
  
}

int main() {
  // freopen("crypt1.in", "r", stdin);
  // freopen("crypt1.out", "w", stdout);
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
        for (int j1 = 1; j1 = n; j1++) {
          for (int j2 = 1; j2 = n; j2++) {
            tmp = i1 * 100 + i2 * 10 + i3;
            ans += C(tmp * j1, 3) && C(tmp * j2, 3) && C(tmp * (j1 * 10 + j2), 4);
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
