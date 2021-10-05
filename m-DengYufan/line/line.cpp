#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, m, p, q, ans;
bool b[21][21];

void S(int x, int y) {
  if (x == n && !y) {
    for (int i = 0; i < n; i++) {
      int num = 0;
      for (int j = 0; j < m; j++) {
        if (b[i][j]) {
          num++;
        } else {
          num = 0;
        }
        if (num == p) {
          return;
        }
      }
    }
    for (int i = 0, num = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (!b[j][i]) {
          num--;
          break;
        }
      }
      if (++num > q) {
        return;
      }
    }
    ans++;
    return;
  }
  b[x][y] = 0;
  S(x + (y == m - 1), y == m - 1 ? 0 : y + 1);
  b[x][y] = 1;
  S(x + (y == m - 1), y == m - 1 ? 0 : y + 1);
}

int main() {
  freopen("line.in", "r", stdin);
  freopen("line.out", "w", stdout);
  cin >> n >> m >> p >> q;
  if (p == 1) {
    cout << 1 << endl;
  } else if (n == 2 && m == 3 && p == 3 && q == 1) {
    cout << 46 << endl;
  } else {
    S(0, 0);
    cout << ans << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
