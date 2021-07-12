#include <iostream>
#define LL long long

using namespace std;

const LL kMove[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

LL n, m, t, r1, c1, r2, c2, ans;
char ch[101][101];

inline void S(LL x, LL y, LL s) {
  if (x < 1 || y < 1 || x > n || y > m || ch[x][y] == '*' || s > t) {
    return;
  }
  if (x == r2 && y == c2) {
    ans++;
    return;
  }
  for (LL i = 0; i <= 3; i++) {
    S(x + kMove[i][0], y + kMove[i][1], s + 1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m >> t;
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      cin >> ch[i][j];
    }
  }
  cin >> r1 >> c1 >> r2 >> c2;
  S(r1, c1, 0);
  cout << ans << endl;
  return 0;
}
