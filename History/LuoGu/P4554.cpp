#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
struct A {
  int x, y, v;
};
int n, m, x, y, v[500][500];
char ch[500][500];
queue<A> q;

int main() {
  while (1) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> ch[i][j];
      }
    }
    if (!n && !m) {
      break;
    }
    cin >> x >> y;
    fill(&v[0][0], &v[499][499] + 1, 1919810);
    while (!q.empty()) {
      q.pop();
    }
    for (q.push({x, y, 0}); !q.empty(); q.pop()) {
      A c = q.front();
      if (c.x < 0 || c.y < 0 || c.x >= n || c.y >= m || v[c.x][c.y] <= c.v) {
        continue;
      }
      v[c.x][c.y] = c.v;
      for (int i = 0; i <= 3; i++) {
        q.push({c.x + kMove[i][0], c.y + kMove[i][1], c.v + (ch[c.x][c.y] != ch[c.x + kMove[i][0]][c.y + kMove[i][1]])});
      }
    }
    cin >> x >> y;
    cout << v[x][y] << endl;
  }
  return 0;
}
