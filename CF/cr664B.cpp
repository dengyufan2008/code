#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMove[4][2] =
    {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int n, m, x, y, way[10001][2];
bool a[101][101];

void Dfs(int x, int y, int step) {
  if (step == n * m + 1) {
    for (int i = 1; i <= n * m; i++) {
      cout << way[i][0] << " " << way[i][1] << "\n";
    }
    exit(0);
  }
  if (x < 1 || y < 1 || x > n || y > m || a[x][y]) {
    return;
  }
  way[step][0] = x, way[step][1] = y, a[x][y] = true;
  for (int i = 0; i <= 3; i++) {
    for (int j = 1; j <= max(n, m); j++) {
      Dfs(x + j * kMove[i][0], y + j * kMove[i][1], step + 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> x >> y;
  Dfs(x, y, 1);
  return 0;
}
