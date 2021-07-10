#include <iostream>
#define LL long long

using namespace std;

const int kMove[12][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {2, 0}, {0, 2}, {-2, 0}, {0, -2}};

int m, n, a[101][101], d[101][101];

void S(int x, int y, int c) {
  if (x < 1 || y < 1 || x > m || y > m || c >= d[x][y]) {
    return;
  }
  d[x][y] = c;
  for (int i = 0; i <= 3; i++) {
    if (a[x + kMove[i][0]][y + kMove[i][1]]) {
      S(x + kMove[i][0], y + kMove[i][1], c + (a[x][y] != a[x + kMove[i][0]][y + kMove[i][1]]));
    }
  }
  for (int i = 4; i <= 11; i++) {
    if (a[x + kMove[i][0]][y + kMove[i][1]]) {
      S(x + kMove[i][0], y + kMove[i][1], c + 2 + (a[x][y] != a[x + kMove[i][0]][y + kMove[i][1]]));
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> m >> n;
  for (int i = 1, x, y, c; i <= n; i++) {
    cin >> x >> y >> c;
    a[x][y] = c + 1;
  }
  fill(&d[0][0], &d[100][100] + 1, 114514);
  S(1, 1, 0);
  cout << (d[m][m] == 114514 ? -1 : d[m][m]) << endl;
  return 0;
}
