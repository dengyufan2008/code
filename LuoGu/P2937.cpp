#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kMove[5][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
struct A {
  int x, y, d, s;
};
int w, h, m1, n1, m2, n2, b[101][101];
char ch[101][101];
queue<A> q;

int main() {
  cin >> w >> h;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> ch[i][j];
      if (ch[i][j] == 'C') {
        if (!m1) {
          m1 = i, n1 = j;
        } else {
          m2 = i, n2 = j;
        }
      }
    }
  }
  q.push({m1, n1, 4, 0});
  fill(&b[0][0], &b[100][100] + 1, 114514);
  while (!q.empty()) {
    A c = q.front();
    q.pop();
    if (c.x < 1 || c.y < 1 || c.x > h || c.y > w || b[c.x][c.y] <= c.s || ch[c.x][c.y] == '*') {
      continue;
    }
    b[c.x][c.y] = min(b[c.x][c.y], c.s);
    if (c.x == m2 && c.y == n2) {
      continue;
    }
    q.push({c.x + kMove[c.d][0], c.y + kMove[c.d][1], c.d, c.s});
    for (int i = 0; i <= 3; i++) {
      if (i != c.d) {
        q.push({c.x + kMove[i][0], c.y + kMove[i][1], i, c.s + 1});
      }
    }
  }
  cout << b[m2][n2] - 1 << endl;
  return 0;
}
