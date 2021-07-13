#include <iostream>
#define LL long long

using namespace std;

const int kMove[5][2] = {{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int m, n, k, dstep, ansstep = 114514;
bool flag, a[16][16], d[16][16], ans[16][16];

bool Compare() {
  if (ansstep != dstep) {
    return ansstep > dstep;
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (d[i][j] != ans[i][j]) {
        return ans[i][j] > d[i][j];
      }
    }
  }
  return false;
}

void S(int x, int y, int s) {
  if (x > m) {
    return;
  }
  if (!s) {
    flag = true;
    if (Compare()) {
      ansstep = dstep;
      copy(&d[0][0], &d[15][15] + 1, &ans[0][0]);
    }
    return;
  }
  for (int i = 0; i <= 1; i++) {
    S(x - (y == 1), y == 1 ? n : y - 1, s);
    d[x][y] += i ? -1 : 1, dstep += i ? -1 : 1;
    for (int j = 0; j <= 4; j++) {
      a[x + kMove[j][0]][y + kMove[j][1]] = !a[x + kMove[j][0]][y + kMove[j][1]];
      s += a[x + kMove[j][0]][y + kMove[j][1]] ? 1 : -1;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      k += a[i][j];
    }
  }
  S(m, n, k);
  if (!flag) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        cout << ans[i][j] << " ";
      }
      cout << endl;
    }
  }
  return 0;
}
