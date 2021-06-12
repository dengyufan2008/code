#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int h = 1, t = 1, a[5][5], q[51][2], f[26];
bool b[5][5];

void Print(int x) {
  if (f[x]) {
    Print(f[x]);
  }
  cout << "(" << x / 5 << ", " << x % 5 << ")" << endl;
}

void Push(int fx, int fy, int x, int y) {
  if (x < 0 || y < 0 || x > 4 || y > 4 || a[x][y] || b[x][y]) {
    return;
  }
  b[x][y] = true;
  f[x * 5 + y] = fx * 5 + fy;
  q[++t][0] = x, q[t][1] = y;
  if (x == 4 && y == 4) {
    cout << "(0, 0)" << endl;
    Print(24);
    t = 0;
    return;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  for (int i = 0; i <= 4; i++) {
    for (int j = 0; j <= 4; j++) {
      cin >> a[i][j];
    }
  }
  q[1][0] = q[1][1] = 0;
  for (; h <= t; h++) {
    for (int i = 0; i <= 3; i++) {
      Push(q[h][0], q[h][1], q[h][0] + kMove[i][0], q[h][1] + kMove[i][1]);
    }
  }
  return 0;
}
