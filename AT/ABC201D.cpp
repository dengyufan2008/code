#include <bits/stdc++.h>
#define LL long long

using namespace std;

int h, w, a[2002][2002], f[2002][2002];
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> ch;
      a[i][j] = (ch == '+' ? 1 : -1);
    }
  }
  for (int i = h; i >= 1; i--) {
    for (int j = w; j >= 1; j--) {
      if ((i + j) & 1) {
        f[i][j] = min(f[i + 1][j] - a[i + 1][j], f[i][j + 1] - a[i][j + 1]);
      } else {
        f[i][j] = max(f[i + 1][j] + a[i + 1][j], f[i][j + 1] + a[i][j + 1]);
      }
    }
  }
  if (f[1][1] > 0) {
    cout << "Takahashi" << endl;
  } else if (f[1][1] < 0) {
    cout << "Aoki" << endl;
  } else {
    cout << "Draw" << endl;
  }
  return 0;
}
