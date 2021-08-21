#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};  // 下右上左
int n, m, x, y, ans, a[502][502][4];
bool flag, b[502][502];
char ch[502][502];

void S(int x, int y, int s, int d) {
  if (x < 1 || y < 1 || x > n || y > m || s < 0 || flag || b[x][y] || ch[x][y] == '#') {
    return;
  }
  b[x][y] = 1;
  if (ch[x][y] == 'D') {
    flag = 1;
    return;
  }
  S(x + kMove[(d + 1) % 4][0], y + kMove[(d + 1) % 4][1], s, d);
  S(x + kMove[(d + 3) % 4][0], y + kMove[(d + 3) % 4][1], s, d);
  for (int i = 1, _d = (d + i) % 4; i <= 3; i++) {
    _d & 1 ? S(x, a[x][y][_d], s - 1, _d) : S(a[x][y][_d], y, s - 1, _d);
  }
}

int main() {
  // freopen("gravity.in", "r", stdin);
  // freopen("gravity.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> ch[i][j];
      if (ch[i][j] == 'C') {
        x = i, y = j;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k <= 3; k++) {
        int _i = i + kMove[k][0], _j = j + kMove[k][1];
        while (_i >= 1 && _j >= 1 && _i <= n && _j <= m && ch[_i][_j] != '#') {
          _i += kMove[k][0], _j += kMove[k][1];
        }
        a[i][j][k] = ch[_i][_j] == '#' ? (k & 1 ? _j - kMove[k][1] : _i - kMove[k][0]) : -1;
      }
    }
  }
  for (ans = 0; !flag; ans++) {
    fill(&b[0][0], &b[501][501] + 1, 0);
    S(a[x][y][0], y, ans, 0);
  }
  cout << ans - 1 << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
