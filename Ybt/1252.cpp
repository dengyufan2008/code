#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int r, c, ans = 114514;
char a[41][41];
bool b[41][41];

void S(int x, int y, int s) {
  if (x < 1 || y < 1 || x > r || y > c || a[x][y] == '#' || b[x][y]) {
    return;
  }
  b[x][y] = true;
  for (int i = 0; i <= 3; i++) {
    S(x + kMove[i][0], y + kMove[i][1], s + 1);
  }
  if (x == r && y == c) {
    ans = min(ans, s);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> r >> c;
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      cin >> a[i][j];
    }
  }
  S(1, 1, 1);
  cout << ans << endl;
  return 0;
}
