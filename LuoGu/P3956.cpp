#include <iostream>
#define LL long long

using namespace std;

const LL kMove[12][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {2, 0}, {0, 2}, {-2, 0}, {0, -2}};

LL m, n, a[1001][1001], d[1001][1001];

void S(LL x, LL y, LL c) {
  if (x < 1 || y < 1 || x > m || y > m || !a[x][y] || c >= d[x][y]) {
    return;
  }
  d[x][y] = c;
  for (LL i = 0; i <= 11; i++) {
    S(x + kMove[i][0], y + kMove[i][1], c + (a[x][y] != a[x + kMove[i][0]][y + kMove[i][1]]) + (i >= 4) * 2);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> m >> n;
  for (LL i = 1, x, y, c; i <= n; i++) {
    cin >> x >> y >> c;
    a[x][y] = c + 1;
  }
  fill(&d[0][0], &d[1000][1000] + 1, 114514);
  S(1, 1, 0);
  if (!a[m][m]) {
    d[m][m] = min(d[m][m], min(d[m][m - 1], d[m - 1][m]) + 2);
  }
  cout << (d[m][m] == 114514 ? -1 : d[m][m]) << endl;
  return 0;
}
