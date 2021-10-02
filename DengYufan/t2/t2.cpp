#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}};
int n, b = -1, a[16][16];  // 1:Alice -1:Bob

int main() {
  freopen("t2.in", "r", stdin);
  freopen("t2.out", "w", stdout);
  cin >> n;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    b = -b, a[x][y] = b;
    for (int j = 0; j <= 3; j++) {    // Dir
      for (int k = 0; k <= 4; k++) {  // Turn
        int _x = x - kMove[j][0] * k, _y = y - kMove[j][1] * k, flag = 1;
        for (int l = 1; l <= 5; l++, _x += kMove[j][0], _y += kMove[j][1]) {  // Place
          if (a[_x][_y] != b) {
            flag = 0;
            break;
          }
        }
        if (flag) {
          cout << (b == 1 ? "A " : "B ") << i << endl;
          return 0;
        }
      }
    }
  }
  cout << "Tie" << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
