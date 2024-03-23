#include <fstream>

using namespace std;

ifstream cin("biology.in");
ofstream cout("biology.out");

const int kMaxN = 1001, kMove[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
int n, m, a[kMaxN][kMaxN], b[kMaxN][kMaxN];
char c;

inline void S(int x, int y, int x1, int y1, int x2, int y2, int t) {
  b[x][y] = t;
  for (int i = 0; i < 4; i++) {
    int _x = x + kMove[i][0], _y = y + kMove[i][1];
    if (_x >= x1 && _x <= x2 && _y >= y1 && _y <= y2 && a[x][y] == a[_x][_y] && b[_x][_y] != t) {
      S(_x, _y, x1, y1, x2, y2, t);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c;
      a[i][j] = c - 'a';
    }
  }
  cin >> m;
  for (int i = 1, o, x1, y1, x2, y2, ans; i <= m; i++) {
    cin >> o >> x1 >> y1;
    if (o == 1) {
      cin >> c;
      a[x1][y1] = c - 'a';
    } else {
      cin >> x2 >> y2;
      ans = 0;
      for (int j = x1; j <= x2; j++) {
        for (int k = y1; k <= y2; k++) {
          if (b[j][k] != i) {
            ans++, S(j, k, x1, y1, x2, y2, i);
          }
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
