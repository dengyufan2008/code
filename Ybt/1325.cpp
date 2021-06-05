#include <bits/stdc++.h>
#define LL long long

using namespace std;

int m, k = 1, l = 1, a[1025][1025];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> m;
  a[1][1] = 1;
  while (k++ <= m) {
    for (int i = 1; i <= l; i++) {
      for (int j = 1; j <= l; j++) {
        a[i][j + l] = a[i][j] + l;
      }
    }
    for (int i = 1; i <= l; i++) {
      for (int j = 1; j <= l; j++) {
        a[i + l][j] = a[i][j + l];
        a[i + l][j + l] = a[i][j];
      }
    }
    l *= 2;
  }
  for (int i = 1; i <= 1 << m; i++) {
    for (int j = 1; j <= 1 << m; j++) {
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
