#include <cstring>
#include <iostream>
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

string M(int x, int y) {
  return (x || y ? M(e[x][y].px, e[x][y].py) + e[x][y].ch : "");
}

int main() {
  cin >> t;
  while (t--) {
    cin >> n >> m;
    fill(&e[0][0], &e[3000][3000] + 1, (E){0, 0, 0, 0, ' '});
    e[0][0].f = 1, ans = "";
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 9; k >= 0; k--) {
          if (e[i][j].f && i + kN[k] <= n) {
            int _i = i + kN[k], _j = (j * 10 + k) % m;
            e[_i][_j].f = 1;
            if (!e[_i][_j].d || e[_i][_j].d - 1 < e[i][j].d || e[_i][_j].d - 1 == e[i][j].d && strcmp(M(_i, _j).c_str(), M(i, j).c_str()) == -1 || e[_i][_j].d - 1 == e[i][j].d && strcmp(M(_i, _j).c_str(), M(i, j).c_str()) == -1 && (e[_i][_j].ch == ' ' || e[_i][_j].ch - '0' < k)) {
              e[_i][_j].d = e[i][j].d + 1;
              e[_i][_j].px = i;
              e[_i][_j].py = j;
              e[_i][_j].ch = k + '0';
            }
          }
        }
      }
    }
    for (int i = 0; i <= n; i++) {
      if (e[i][0].f) {
        string _ans = M(i, 0);
        if (ans.length() < _ans.length() || ans.length() == _ans.length() && strcmp(ans.c_str(), _ans.c_str()) == -1) {
          ans = _ans;
        }
      }
    }
    cout << (ans == "" ? "-1" : ans) << endl;
  }
  return 0;
}
