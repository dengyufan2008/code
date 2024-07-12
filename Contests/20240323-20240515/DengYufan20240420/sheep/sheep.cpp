#include <algorithm>
#include <chrono>
#include <fstream>
#include <queue>
#include <random>

using namespace std;

ifstream cin("sheep.in");
ofstream cout("sheep.out");

const int kMaxN = 51, kMaxM = 1601;
struct Point {
  int x, y;
  bool operator==(Point p) {
    return x == p.x && y == p.y;
  }
  Point operator+(Point p) {
    return {x + p.x, y + p.y};
  }
  Point operator=(Point p) {
    return {x = p.x, y = p.y};
  }
} p[kMaxN][kMaxN];
const Point kMove[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
struct V {
  Point a, b;
} v[kMaxM];
int n, m;
bool a[kMaxN][kMaxN];
vector<pair<Point, Point>> ans;
queue<pair<Point, int>> q;
mt19937 Rand;

void Add(Point x, Point y) {
  if (x == y) {
    return;
  }
  Add(x, p[y.x][y.y]), ans.push_back({p[y.x][y.y], y});
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> v[i].a.x >> v[i].a.y;
  }
  for (int i = 1; i <= m; i++) {
    cin >> v[i].b.x >> v[i].b.y;
  }
  for (bool o = 1; o;) {
    o = 0, ans.clear();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        a[i][j] = 0;
      }
    }
    Rand = mt19937(chrono::steady_clock().now().time_since_epoch().count());
    shuffle(v + 1, v + m + 1, Rand);
    for (int i = 1; i <= m; i++) {
      a[v[i].a.x][v[i].a.y] = 1;
    }
    for (int i = 1; i <= m; i++) {
      a[v[i].a.x][v[i].a.y] = 0;
      while (!q.empty()) {
        q.pop();
      }
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          p[i][j] = {};
        }
      }
      for (q.push({v[i].a, 0}); !q.empty(); q.pop()) {
        if (q.front().first == v[i].b) {
          break;
        }
        for (int i = 0; i < 4; i++) {
          Point x = q.front().first + kMove[i];
          if (x.x >= 1 && x.x <= n && x.y >= 1 && x.y <= n && !a[x.x][x.y] && p[x.x][x.y] == (Point){}) {
            p[x.x][x.y] = q.front().first;
            q.push({x, q.front().second + 1});
          }
        }
      }
      if (p[v[i].b.x][v[i].b.y] == (Point){}) {
        o = 1;
        break;
      } else {
        Add(v[i].a, v[i].b), a[v[i].b.x][v[i].b.y] = 1;
      }
    }
  }
  cout << ans.size() << '\n';
  for (auto i : ans) {
    cout << i.first.x << ' ' << i.first.y << ' ' << i.second.x << ' ' << i.second.y << '\n';
  }
  return 0;
}
