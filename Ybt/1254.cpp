#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, m, h = 1, t = 1, q[10001][3];
char a[101][101];
bool b[101][101];

void Push(int x, int y, int s) {
  if (x < 1 || x > n || y < 1 || y > n || a[x][y] == '#' || b[x][y]) {
    return;
  }
  b[x][y] = true;
  q[++t][0] = x, q[t][1] = y, q[t][2] = s;
  if (a[x][y] == 'T') {
    cout << q[t][2] << endl;
    t = 0;
    return;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      if (a[i][j] == 'S') {
        q[1][0] = i, q[1][1] = j;
      }
    }
  }
  for (; h <= t; h++) {
    for (int i = 0; i <= 3; i++) {
      Push(q[h][0] + kMove[i][0], q[h][1] + kMove[i][1], q[h][2] + 1);
    }
  }
  return 0;
}
