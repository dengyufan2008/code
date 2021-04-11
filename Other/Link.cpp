#include <iostream>
#define LL long long

using namespace std;

struct A {
  int x, y, step;
} table[2501];

const int kAdd[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m, x, y, h, t;
char a[51][51];
bool b[51][51];

void Find(int x, int y) {
  if (x < 1 || x > m || y < 1 || y > m || b[x][y] || a[x][y] != 'X') {
    return;
  }
  b[x][y] = true;
  for (int i = 0; i <= 3; i++) {
    Find(x + kAdd[i][0], y + kAdd[i][1]);
  }
}

void S(int x, int y, int step) {
  if (x < 1 || x > m || y < 1 || y > m || b[x][y]) {
    return;
  }
  if (a[x][y] == 'X') {
    cout << step << "\n";
    exit(0);
  }
  b[x][y] = true;
  for (int i = 0; i <= 3; i++) {
    table[++t].x = x + kAdd[i][0], table[t].y = y + kAdd[i][1], table[t].step = step + 1;
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
      if (a[i][j] == 'X') {
        x = i, y = j;
      }
    }
  }
  Find(x, y);
  for (h = 1, t = 1, table[1].x = x, table[1].y = y, table[1].step = 0; h <= t; h++) {
    S(table[h].x, table[h].y, table[h].step);
  }
  return 0;
}
