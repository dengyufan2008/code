#include <iostream>
#include <cstring>
#define LL long long

using namespace std;

const int kN[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
struct E {
  int d, px, py;
  bool f;
  char ch;
} e[3001][3001];
int t, n, m;
string ans;

int C(int x, int y, int _x, int _y) {
  if (!x && !y && !_x && !_y) {
    return 1;
  } else if (C(e[x][y].px, e[x][y].py, e[_x][_y].px, e[_x][_y].py) == 2) {
    return 2;
  } else if (C(e[x][y].px, e[x][y].py, e[_x][_y].px, e[_x][_y].py) == 1) {
    if (e[x][y].ch < e[_x][_y].ch) {
      return 0;
    } else if (e[x][y].ch == e[_x][_y].ch) {
      return 1;
    } else {
      return 2;
    }
  } else {
    return 0;
  }
}

string M(int x, int y) {
  return e[x][y].ch + (x || y ? M(e[x][y].px, e[x][y].py) : "");
}

int main() {
  // freopen("stick.in", "r", stdin);
  // freopen("stick.out", "w", stdout);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    fill(&e[0][0], &e[3000][3000] + 1, (E){0, 0, 0, 0, ' '});
    ans = "", e[0][0].f = 1;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 9; k >= 0; k--) {
          if (e[i][j].f && i + kN[k] <= n) {
            int _i = i + kN[k], _j = (j * 10 + k) % m;
            e[_i][_j].f = 1;
            if (e[e[_i][_j].px][e[_i][_j].py].d > e[i][j].d || e[e[_i][_j].px][e[_i][_j].py].d == e[i][j].d && !C(e[_i][_j].px, e[_i][_j].py, i, j) || e[e[_i][_j].px][e[_i][_j].py].d == e[i][j].d && C(e[_i][_j].px, e[_i][_j].py, i, j) == 1 && e[_i][_j].ch == k + '0') {
              e[_i][_j].px = i;
              e[_i][_j].py = j;
              e[_i][_j].d = e[i][j].d + 1;
              e[_i][_j].ch = '0' + k;
            }
          }
        }
      }
    }
    for (int i = 0; i <= n; i++) {
      string _ans = M(i, 0);
      if (e[i][0].d > ans.length() || e[i][0].d == ans.length() && strcmp(ans.c_str(), _ans.c_str()) == -1) {
        ans = _ans;
      }
    }
    cout << (ans == "" ? "-1" : ans) << endl;
  }
  return 0;
}
