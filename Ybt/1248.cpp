#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMove[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

int x, y, z, h, t, q[1000001][4];
char a[101][101][101];
bool flag, b[101][101][101];

void Push(int _x, int _y, int _z, int s) {
  if (_x < 1 || _x > x || _y < 1 || _y > y || _z < 1 || _z > z || a[_x][_y][_z] == '#' || b[_x][_y][_z]) {
    return;
  }
  b[_x][_y][_z] = true;
  q[++t][0] = _x, q[t][1] = _y, q[t][2] = _z, q[t][3] = s;
  if (a[_x][_y][_z] == 'E') {
    cout << "Escaped in " << s << " minute(s)." << endl;
    flag = true;
    t = 0;
    return;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  while (1) {
    cin >> x >> y >> z;
    if (!x && !y && !z) {
      break;
    }
    for (int i = 1; i <= x; i++) {
      for (int j = 1; j <= y; j++) {
        for (int k = 1; k <= z; k++) {
          cin >> a[i][j][k];
          if (a[i][j][k] == 'S') {
            q[1][0] = i, q[1][1] = j, q[1][2] = k;
          }
        }
      }
    }
    h = t = 1, flag = false;
    for (; h <= t; h++) {
      for (int i = 0; i <= 5; i++) {
        Push(q[h][0] + kMove[i][0], q[h][1] + kMove[i][1], q[h][2] + kMove[i][2], q[h][3] + 1);
      }
    }
    if (!flag) {
      cout << "Trapped!" << endl;
    }
  }
  return 0;
}
