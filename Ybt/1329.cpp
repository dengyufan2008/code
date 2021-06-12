#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMove[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, m, ans, a[1001][1001];
bool b[1001][1001];
char ch;

bool S(int x, int y) {
  if (x < 1 || y < 1 || x > n || y > m || !a[x][y] || b[x][y]) {
    return false;
  }
  b[x][y] = true;
  for (int i = 0; i <= 3; i++) {
    S(x + kMove[i][0], y + kMove[i][1]);
  }
  return true;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> ch;
      a[i][j] = ch - '0';
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans += S(i, j);
    }
  }
  cout << ans << endl;
  return 0;
}
