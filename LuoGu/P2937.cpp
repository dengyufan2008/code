#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kMove[5][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct A {
  int x, y, d, s;
};
int w, h, m, n, ans = 114514;
bool b[101][101];
char ch[101][101];
queue<A> q;

int main() {
  cin >> w >> h;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
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
    if (c.x < 1 || c.y < 1 || c.x > h || c.y > w || b[c.x][c.y] || ch[c.x][c.y] == '*' || c.s >= ans) {
      continue;
    }
    if (ch[c.x][c.y] == 'C' && (c.x != m || c.y != n)) {
      ans = min(ans, c.s);
      continue;
    }
    b[c.x][c.y] = 1;
    q.push({c.x + kMove[c.d][0], c.y + kMove[c.d][1], c.d, c.s});
    for (int i = 0; i <= 3; i++) {
      if (i != c.d) {
        q.push({c.x + kMove[i][0], c.y + kMove[i][1], i, c.s + 1});
      }
    }
  }
  cout << ans - 1 << endl;
  return 0;
}
