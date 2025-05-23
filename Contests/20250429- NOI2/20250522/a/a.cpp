#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2501, kMaxM = kMaxN << 1;
int t, n, m, l, c[2];
int a[kMaxN][kMaxN], b[kMaxN][kMaxN];
bool d[kMaxM];

void Input() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      static char c;
      cin >> c;
      if (c == '>' || c == 'v') {
        a[i][j] = 0;
      } else if (c == '^' || c == '<') {
        a[i][j] = 1;
      } else {
        a[i][j] = -1;
      }
      if (c == '>' || c == '<') {
        b[i][j] = 0;
      } else if (c == 'v' || c == '^') {
        b[i][j] = 1;
      } else {
        b[i][j] = -1;
      }
    }
  }
}

void Solve(bool _o) {
  for (int i = 1, p = 1; i < l; i++) {
    bool o = _o ^ (i & 1);
    if (d[i] == o && d[i + 1] == o) {
      int j = i - 1, k = i + 2;
      bool u = 1;
      for (; j >= p && d[j] != o; j -= 2) {
        if (j == p || d[j - 1] != o) {
          u = 0;
          break;
        }
      }
      if (!u) {
        continue;
      }
      for (; k <= l && d[k] != o; k += 2) {
        if (k == l || d[k + 1] != o) {
          u = 0;
          break;
        }
      }
      if (u) {
        c[o]++, d[j + 1] ^= 1, d[k - 1] ^= 1;
      } else {
        p = k + 2, i = p - 1;
      }
    }
  }
}

void Do() {
  static bool o[kMaxN][kMaxN];
  c[0] = c[1] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      o[i][j] = 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= 1; j--) {
      if (o[i][j]) {
        continue;
      }
      if (a[i][j] == 0) {
        l = 0;
        for (int x = i, y = j; y >= 1 && a[x][y] == 0; x++, y--) {
          d[++l] = b[x][y], o[x][y] = 1;
          if (x == n || a[x + 1][y] != 1) {
            break;
          }
          d[++l] = b[x + 1][y], o[x + 1][y] = 1;
        }
        Solve(0);
      } else if (a[i][j] == 1) {
        l = 0;
        for (int x = i, y = j; x <= n && a[x][y] == 1; x++, y--) {
          d[++l] = b[x][y], o[x][y] = 1;
          if (y == 1 || a[x][y - 1] != 0) {
            break;
          }
          d[++l] = b[x][y - 1], o[x][y - 1] = 1;
        }
        Solve(1);
      }
    }
  }
  cout << (c[0] > c[1] ? "Alice\n" : "Bob\n");
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    Input(), Do();
  }
  return 0;
}
