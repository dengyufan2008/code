// 暴力
#include <fstream>
#include <queue>
#include <unordered_set>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.ans");

const int kMaxN = 2e5 + 1;
const int kMove[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m, k, t, ans;
queue<pair<int, int>> q;
unordered_set<int> s[kMaxN];
unordered_set<int> g[kMaxN], gg;
unordered_set<int> b[kMaxN], bb;

void FindGrid(int x, int y) {
  if (x < 1 || x > n || y < 1 || y > m || !s[x].count(y) || b[x].count(y)) {
    return;
  }
  bb.insert(x), b[x].insert(y);
  gg.insert(x), g[x].insert(y);
  for (int i = 0; i < 4; i++) {
    FindGrid(x + kMove[i][0], y + kMove[i][1]);
  }
}

bool Deletable(int x, int y) {
  if ((x == 1 || !g[x - 1].count(y)) && (x == n || !g[x + 1].count(y))) {
    return 1;
  } else if ((y == 1 || !g[x].count(y - 1)) && (y == m || !g[x].count(y + 1))) {
    return 1;
  }
  return 0;
}

void Change(int x, int y, int w) {
  FindGrid(x, y);
  for (int i : gg) {
    for (int j : g[i]) {
      if (Deletable(i, j)) {
        q.push({i, j});
      }
    }
  }
  for (; !q.empty(); q.pop()) {
    int x = q.front().first, y = q.front().second;
    if (!g[x].count(y)) {
      continue;
    }
    ans += w, g[x].erase(y);
    for (int i = 0; i < 4; i++) {
      int _x = x + kMove[i][0], _y = y + kMove[i][1];
      if (_x >= 1 && _x <= n && _y >= 1 && _y <= m && Deletable(_x, _y)) {
        q.push({_x, _y});
      }
    }
  }
  for (int i : gg) {
    g[i].clear();
  }
  gg.clear();
}

void Clear() {
  for (int i : bb) {
    b[i].clear();
  }
  bb.clear();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k >> t;
  for (int i = 1, x, y; i <= k; i++) {
    cin >> x >> y, s[x].insert(y);
  }
  for (int i = 1; i <= n; i++) {
    for (int j : s[i]) {
      Change(i, j, 1);
    }
  }
  Clear();
  cout << ans << '\n';
  for (int i = 1, x, y; i <= t; i++) {
    cin >> x >> y;
    if (s[x].count(y)) {
      Change(x, y, -1), Clear();
      s[x].erase(y);
      for (int j = 0; j < 4; j++) {
        Change(x + kMove[j][0], y + kMove[j][1], 1);
      }
      Clear();
    } else {
      for (int j = 0; j < 4; j++) {
        Change(x + kMove[j][0], y + kMove[j][1], -1);
      }
      Clear();
      s[x].insert(y);
      Change(x, y, 1), Clear();
    }
    cout << ans << '\n';
  }
  return 0;
}
