#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMove[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

int h, w, num, ans;
char a[11][11];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i < h; i++) {
    for (int j = 1; j < w; j++) {
      num = 0;
      for (int k = 0; k <= 3; k++) {
        num += a[i + kMove[k][0]][j + kMove[k][1]] == '#';
      }
      ans += num == 1 || num == 3;
    }
  }
  cout << ans << endl;
  return 0;
}
