#include <iostream>
#include <queue>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 1001, kInf = 1e9;
struct A {
  int x, y, w;
};
int n, m, k, v[kMaxN][kMaxN];
queue<A> q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  fill(&v[0][0], &v[kMaxN][0], kInf);
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x][y] = z, q.push({x, y, v[x][y]});
  }
  for (; !q.empty(); q.pop()) {
    int x = q.front().x, y = q.front().y, w = q.front().w;
    if (v[x][y] == w) {
      for (int i = 1; i + x <= n; i++) {
        int a = i + x, b = i + y;
        if (v[a][i] > v[x][y] + v[a][b]) {
          v[a][i] = v[x][y] + v[a][b], q.push({a, i, v[a][i]});
        }
        if (v[a][b] > v[x][y] + v[a][i]) {
          v[a][b] = v[x][y] + v[a][i], q.push({a, b, v[a][b]});
        }
      }
      for (int i = 1; i + y <= x; i++) {
        int b = i + y, c = x - y;
        if (v[c][i] > v[x][y] + v[x][b]) {
          v[c][i] = v[x][y] + v[x][b], q.push({c, i, v[c][i]});
        }
        if (v[x][b] > v[x][y] + v[c][i]) {
          v[x][b] = v[x][y] + v[c][i], q.push({x, b, v[x][b]});
        }
      }
      // for (int i = x - y + 1; i <= n; i++) {
      //   int d = i - x + y, e = x - i;
      //   if (v[i][d] > v[x][y] + v[x][e]) {
      //     v[i][d] = v[x][y] + v[x][e], q.push({i, d, v[i][d]});
      //   }
      //   if (v[x][e] > v[x][y] + v[i][d]) {
      //     v[x][e] = v[x][y] + v[i][d], q.push({x, e, v[x][e]});
      //   }
      // }
    }
  }
  for (int i = 1, x1, y1, x2, y2; i <= k; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    cout << v[x1][y1] + v[x2][y2] << '\n';
  }
  return 0;
}
