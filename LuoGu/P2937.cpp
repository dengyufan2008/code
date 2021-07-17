#include <iostream>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int w, h, m, n, ans = 114514;
bool b[101][101];
char ch[101][101];

void S(int x, int y, int d, int s) {
  if (x < 1 || y < 1 || x > w || y > h || b[x][y] || ch[x][y] == '*') {
    return;
  }
  if (ch[x][y] == 'C' && (x != m || y != n)) {
    ans = min(ans, s);
    return;
  }
  b[x][y] = 1;
  for (int i = 0; i <= 3; i++) {
    S(x + kMove[i][0], y + kMove[i][1], i, s + (i != d));
  }
  b[x][y] = 0;
}

int main() {
  cin >> w >> h;
  for (int i = 1; i <= w; i++) {
    for (int j = 1; j <= h; j++) {
      cin >> ch[i][j];
      if (ch[i][j] == 'C') {
        m = i, n = j;
      }
    }
  }
  S(m, n, 4, 0);
  cout << ans - 1 << endl;
  return 0;
}
