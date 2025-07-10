#include <fstream>
#include <queue>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e6 + 1;
const int kMove[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int t, n, m;
char *ha, *a[kMaxN], ua[kMaxN];
bool *hb, *b[kMaxN], ub[kMaxN];
bool *hbb[4], *bb[4][kMaxN], ubb[4][kMaxN];
bool *hans, *ans[kMaxN], uans[kMaxN];

bool Stop(int x, int y) {
  return x < 0 || x >= n || y < 0 || y >= m || a[x][y] == '#';
}

void Move(int &x, int &y, int o) {
  b[x][y] = 1;
  while (!Stop(x + kMove[o][0], y + kMove[o][1])) {
    x += kMove[o][0], y += kMove[o][1];
    b[x][y] = 1;
  }
}

bool Do(int x, int y) {
  static queue<pair<int, int>> q;
  fill(&ubb[0], &ubb[n * m], 0);
  bb[x][y] = 1;
  for (q.push({x, y}); !q.empty(); q.pop()) {
    int x = q.front().first, y = q.front().second;
    for (int o = 0; o < 4; o++) {
      static int xx, yy;
      Move(xx = x, yy = y, o);
      if (!bb[xx][yy]) {
        bb[xx][yy] = 1, q.push({xx, yy});
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!b[i][j] && a[i][j] == '.') {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m, ha = ua, hb = ub, hans = uans;
    for (int o = 0; o < 4; o++) {
      hbb[o] = ubb[o];
    }
    for (int i = 0; i < n; i++) {
      a[i] = ha, ha += m;
      b[i] = hb, hb += m;
      for (int o = 0; o < 4; o++) {
        bb[o][i] = hbb[o], hbb[o] += m;
      }
      ans[i] = hans, hans += m;
      for (int j = 0; j < m; j++) {
        cin >> a[i][j], ans[i][j] = 0;
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (a[i][j] == '.') {
          ans[i][j] = Do(i, j);
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (a[i][j] == '#') {
          cout << '#';
        } else if (ans[i][j]) {
          cout << '*';
        } else {
          cout << '.';
        }
      }
      cout << '\n';
    }
  }
  return 0;
}
