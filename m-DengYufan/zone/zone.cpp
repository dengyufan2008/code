#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m, ans;
bool b[8][9], _b[8][9];

void _S(int x, int y, bool c) {
  if (x < 1 || x > n || y < 1 || y > m || b[x][y] != c || _b[x][y]) {
    return;
  }
  _b[x][y] = 1;
  for (int i = 0; i <= 3; i++) {
    _S(x + kMove[i][0], y + kMove[i][1], c);
  }
}

void S(int x, int y) {
  if (x == n + 1 && y == 1) {
    bool flag = 0, _flag = 0, __flag = 0, ___flag = 0;
    fill(&_b[0][0], &_b[n][m] + 1, 0);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (!b[i][j] && !flag) {
          flag = 1;
          _S(i, j, 0);
        }
        if (b[i][j] && !_flag) {
          _flag = 1;
          _S(i, j, 1);
        }
        if (!b[i][j] && !_b[i][j] && flag || b[i][j] && !_b[i][j] && _flag) {
          return;
        }
        if (i == 1 || i == n || j == 1 || j == m) {
          (b[i][j] ? ___flag : __flag) = 1;
        }
      }
    }
    if (__flag && ___flag) {
      ans++;
    }
    return;
  }
  b[x][y] = 1;
  S(x + (y == m), y % m + 1);
  b[x][y] = 0;
  S(x + (y == m), y % m + 1);
}

int main() {
  freopen("zone.in", "r", stdin);
  freopen("zone.out", "w", stdout);
  cin >> n >> m;
  S(1, 1);
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
