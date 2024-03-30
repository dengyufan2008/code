#include <fstream>

using namespace std;

ifstream cin("medrcy.in");
ofstream cout("medrcy.out");

const int kMaxN = 1001;
int t, n, m, k, mn, d[kMaxN], c[kMaxN];
bool e[kMaxN][kMaxN], b[kMaxN], ans[kMaxN];

void S(int x) {
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    c[mx] < c[i] && (mx = i);
  }
  if (c[mx] == 2) {
    ;
    return;
  } else if (x > k) {
    return;
  }
  mx = 0;
  for (int i = 1; i <= n; i++) {
    !b[i] && c[mx] < c[i] && (mx = i);
  }
  d[x] = mx;
  for (int i = 1; i <= n; i++) {
    if (e[mx][i]) {
      c[mx]--, c[i]--;
    }
  }
  S(x + 1), b[mx] = 1;
  for (int i = 1; i <= n; i++) {
    if (e[mx][i]) {
      c[mx]++, c[i]++;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (e[mx][i] && !b[i] && x <= k) {
      d[x++] = i;
      for (int j = 1; j <= n; j++) {
        if (e[i][j]) {
          c[i]--, c[j]--;
        }
      }
    } else if (e[mx][i]) {
      return;
    }
  }
  S(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      c[i] = ans[i] = 0;
      for (int j = 1; j <= n; j++) {
        e[i][j] = 0;
      }
    }
    cin >> n >> m >> k;
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      c[x]++, c[y]++;
      e[x][y] = e[y][x] = 1;
    }
    mn = k + 1, S(1);
    if (mn > k) {
      cout << -1 << '\n';
    } else {
      int w = 0;
      for (int i = 1; i <= n; i++) {
        w += ans[i];
      }
      cout << mn << ' ' << w << '\n';
      for (int i = 1; i <= n; i++) {
        if (ans[i]) {
          cout << i << ' ';
        }
      }
      cout << '\n';
    }
  }
  return 0;
}
