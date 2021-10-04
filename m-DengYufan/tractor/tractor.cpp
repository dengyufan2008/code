#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, x, y, d[1001][1001];
bool b[1001][1001], _b[1001][1001];  // Grass, In_queue
queue<pair<int, int>> q;

int main() {
  freopen("tractor.in", "r", stdin);
  freopen("tractor.out", "w", stdout);
  cin >> n >> x >> y;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    b[x][y] = 1;
  }
  fill(&d[0][0], &d[1000][1000] + 1, 0x7fffffff);
  d[x][y] = 0, _b[x][y] = 1;
  for (q.push({x, y}); !q.empty(); q.pop()) {
    auto c = q.front();
    for (int i = 0; i <= 3; i++) {
      int _x = c.first + kMove[i][0], _y = c.second + kMove[i][1];
      if (_x >= 0 && _x <= 1000 && _y >= 0 && _y <= 1000 && d[_x][_y] > d[c.first][c.second] + b[_x][_y]) {
        d[_x][_y] = d[c.first][c.second] + b[_x][_y];
        if (!_b[_x][_y]) {
          q.push({_x, _y});
          _b[_x][_y] = 1;
        }
      }
    }
    _b[c.first][c.second] = 0;
  }
  cout << d[0][0] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
