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
string ans, tmp, a, b;

inline int Cmp() {
  if (a.length() != b.length()) {
    return a.length() > b.length() ? 1 : -1;
  }
  for (register int i(0); i < a.length(); ++i) {
    if (a[i] != b[i]) {
      return a[i] > b[i] ? 1 : -1;
    }
  }
  return 0;
}

inline void M(register int x, register int y) {
  if (x || y) {
    M(e[x][y].px, e[x][y].py);
    tmp += e[x][y].ch;
  }
}

int main() {
  // freopen("stick.in", "r", stdin);
  // freopen("stick.out", "w", stdout);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    fill(&e[0][0], &e[3000][3000] + 1, (E){0, 0, 0, 0, ' '});
    e[0][0].f = 1, ans = "";
    for (register int i(0); i <= n; ++i) {
      for (register int j(0); j < m; ++j) {
        if (e[i][j].f) {
          for (register int k(9); k >= 0; --k) {
            if (i + kN[k] <= n) {
              register int _i = i + kN[k], _j = (j * 10 + k) % m;
              e[_i][_j].f = 1;
              tmp = "", M(_i, _j), a = tmp;
              tmp = "", M(i, j), b = tmp + (char)(k + '0');
              if (Cmp() == -1) {
                e[_i][_j].px = i;
                e[_i][_j].py = j;
                e[_i][_j].d = e[i][j].d + 1;
                e[_i][_j].ch = k + '0';
              }
            }
          }
        }
      }
    }
    for (register int i(0); i <= n; ++i) {
      if (e[i][0].f) {
        string _ans;
        tmp = "", M(i, 0), _ans = tmp;
        a = ans, b = _ans;
        if (Cmp() == -1) {
          ans = _ans;
        }
      }
    }
    cout << (ans == "" ? "-1" : ans) << '\n';
  }
  return 0;
}
