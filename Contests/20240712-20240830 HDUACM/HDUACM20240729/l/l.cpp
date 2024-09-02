#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 3e5 + 2;
struct Q {
  int x, y, d;
};
int t, n, m;
LL f[2][kMaxN], d[2][kMaxN], ans[6][kMaxN];
pair<int, int> a[kMaxN];
vector<Q> q[6];

void Max0(int x, LL w) {
  for (int i = x; i <= n; i += i & -i) {
    d[0][i] = max(d[0][i], w);
  }
}

LL Ask0(int x) {
  LL w = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    w = max(w, d[0][i]);
  }
  return w;
}

void Max1(int x, LL w) {
  for (int i = x; i >= 1; i -= i & -i) {
    d[1][i] = max(d[1][i], w);
  }
}

LL Ask1(int x) {
  LL w = 0;
  for (int i = x; i <= n; i += i & -i) {
    w = max(w, d[1][i]);
  }
  return w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m, a[n + 1] = {0, 0};
    for (int i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
    }
    fill(&d[0][1], &d[0][n] + 1, 0);
    fill(&d[1][1], &d[1][n] + 1, 0);
    for (int i = 1; i <= n; i++) {
      f[0][i] = Ask0(a[i].first) + a[i].second;
      Max0(a[i].first, f[0][i]);
    }
    for (int i = n; i >= 1; i--) {
      f[1][i] = Ask1(a[i].first) + a[i].second;
      Max1(a[i].first, f[1][i]);
    }
    for (int i = 1, x1, y1, x2, y2; i <= m; i++) {
      cin >> x1 >> y1 >> x2 >> y2;
      q[0].push_back({x1 - 1, y2 + 1, i});
      q[1].push_back({x2 + 1, y1 - 1, i});
      q[2].push_back({x1 - 1, y2, i});
      q[3].push_back({x1, y2 + 1, i});
      q[4].push_back({x2, y1 - 1, i});
      q[5].push_back({x2 + 1, y1, i});
    }
    fill(&d[0][1], &d[0][n] + 1, 0);
    fill(&d[1][1], &d[1][n] + 1, 0);
    for (int i = 0; i <= 4; i += 2) {
      sort(q[i].begin(), q[i].end(), [](Q i, Q j) {
        return i.x < j.x;
      });
    }
    for (int i = 0, j = 0, k = 0, l = 0; i <= n; i++) {
      if (i >= 1) {
        Max1(a[i].first, f[0][i] + f[1][i] - a[i].second);
        Max0(a[i].first, f[0][i]);
      }
      for (; j < q[0].size() && q[0][j].x == i; j++) {
        ans[0][q[0][j].d] = max(ans[0][q[0][j].d], Ask1(q[0][j].y));
      }
      for (; k < q[2].size() && q[2][k].x == i; k++) {
        ans[2][q[2][k].d] = max(ans[2][q[2][k].d], Ask0(q[2][k].y));
      }
      for (; l < q[4].size() && q[4][l].x == i; l++) {
        ans[4][q[4][l].d] = max(ans[4][q[4][l].d], Ask0(q[4][l].y));
      }
    }
    fill(&d[0][1], &d[0][n] + 1, 0);
    fill(&d[1][1], &d[1][n] + 1, 0);
    for (int i = 1; i <= 5; i += 2) {
      sort(q[i].begin(), q[i].end(), [](Q i, Q j) {
        return i.x > j.x;
      });
    }
    for (int i = n + 1, j = 0, k = 0, l = 0; i >= 1; i--) {
      if (i <= n) {
        Max0(a[i].first, f[0][i] + f[1][i] - a[i].second);
        Max1(a[i].first, f[1][i]);
      }
      for (; j < q[1].size() && q[1][j].x == i; j++) {
        ans[1][q[1][j].d] = max(ans[1][q[1][j].d], Ask0(q[1][j].y));
      }
      for (; k < q[3].size() && q[3][k].x == i; k++) {
        ans[3][q[3][k].d] = max(ans[3][q[3][k].d], Ask1(q[3][k].y));
      }
      for (; l < q[5].size() && q[5][l].x == i; l++) {
        ans[5][q[5][l].d] = max(ans[5][q[5][l].d], Ask1(q[5][l].y));
      }
    }
    for (int i = 1; i <= m; i++) {
      LL w1 = max(ans[0][i], ans[1][i]);
      LL w2 = max(ans[2][i] + ans[3][i], ans[4][i] + ans[5][i]);
      cout << max(w1, w2) << '\n';
      for (int j = 0; j <= 5; j++) {
        ans[j][i] = 0;
      }
    }
    for (int i = 0; i <= 5; i++) {
      q[i].clear();
    }
  }
  return 0;
}
