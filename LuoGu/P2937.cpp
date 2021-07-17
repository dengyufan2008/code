#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct A {
  int x, y, d, s;
};
int w, h, m, n, ans = 114514;
bool b[101][101];
char ch[101][101];
queue<A> q;

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
  q.push({m, n, 4, 0});
  while (!q.empty()) {
    A c = q.front();
    q.pop();
    if (c.x < 1 || c.y < 1 || c.x > w || c.y > h || b[c.x][c.y] || ch[c.x][c.y] == '*') {
      continue;
    }
    b[c.x][c.y] = 1;
    if (ch[c.x][c.y] == 'C' && (c.x != m || c.y != n)) {
      ans = min(ans, c.s);
      continue;
    }
    for (int i = 0; i <= 3; i++) {
      q.push({c.x + kMove[i][0], c.y + kMove[i][1], i, c.s + (i != c.d)});
    }
  }
  cout << ans - 1 << endl;
  return 0;
}
