#include <iostream>
#define LLL __int128_t

using namespace std;

const int kMaxN = 101;
int n, m, q;
char a[kMaxN][kMaxN], b[kMaxN][kMaxN];

void _Print(LLL x) {
  if (x > 9) {
    _Print(x / 10);
  }
  putchar(48 + x % 10);
}

void Print(LLL x) {
  if (x < 0) {
    putchar(45), x = -x;
  }
  _Print(x);
}

LLL Solve1() {
  int x = 1;
  for (; x <= m && a[1][x] != '.'; x++) {
  }
  for (int i = x; i <= m; i++) {
    if (a[1][i] != b[1][i]) {
      return -1;
    }
  }
  LLL s = 0, t = 0;
  for (int i = x - 1; i >= 1; i--) {
    s = s << 1 | (a[1][i] == '>');
    t = t << 1 | (b[1][i] == '>');
  }
  LLL d = s < t ? t - s : s - t;
  return min(d, ((LLL)1 << x - 1) - d);
}

LLL Solve2() {
  static char c[kMaxN][kMaxN];
  int k = 1 << n + m - 1;
  int s = 0, t = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      c[i][j] = a[i][j];
      s = s << 1 | (a[i][j] == '>');
      t = t << 1 | (b[i][j] == '>');
    }
  }
  if (s == t) {
    return 0;
  }
  int ans = 0;
  for (int i = 1; i < k; i++) {
    int x = 1, y = 1;
    while (x <= n && y <= m && c[x][y] != '.') {
      s ^= 1 << (n - x) * m + m - y;
      c[x][y] ^= '>' ^ 'v';
      if (c[x][y] == 'v') {
        y++;
      } else {
        x++;
      }
    }
    if (s == t) {
      ans = i;
      break;
    }
  }
  if (!ans) {
    return -1;
  }
  s = t = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      c[i][j] = b[i][j];
      s = s << 1 | (a[i][j] == '>');
      t = t << 1 | (b[i][j] == '>');
    }
  }
  for (int i = 1; i < k; i++) {
    int x = 1, y = 1;
    while (x <= n && y <= m && c[x][y] != '.') {
      t ^= 1 << (n - x) * m + m - y;
      c[x][y] ^= '>' ^ 'v';
      if (c[x][y] == 'v') {
        y++;
      } else {
        x++;
      }
    }
    if (s == t) {
      return min(ans, i);
    }
  }
  return -1;
}

LLL Solve() {
  if (n == 1) {
    return Solve1();
  } else if (n <= 4 && m <= 4) {
    return Solve2();
  }
  return -1;
}

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> b[i][j];
    }
  }
  Print(Solve()), putchar(10);
  for (int i = 1, o, x, y; i <= q; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      a[x][y] ^= '>' ^ 'v';
    } else {
      b[x][y] ^= '>' ^ 'v';
    }
    Print(Solve()), putchar(10);
  }
  return 0;
}
