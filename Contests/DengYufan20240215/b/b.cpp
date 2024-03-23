#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kMaxN = 1e5, kMaxM = 317, kMaxL = 9;
struct Q {
  int o, x, p, w;
} q[kMaxN << 1];
int n, m, k, d[kMaxN], lg[kMaxM + 1];
LL ans[kMaxN];
class H1 {
  int a[kMaxM];
  vector<int> v[kMaxM];

 public:
  void Change(int x, bool o) {
    static int n = 0;
    if ((++n) % kMaxM) {
      for (int i = 0; i < kMaxM; i++) {
        if (!v[i].empty() && v[i].back() >= x) {
          auto p = lower_bound(v[i].begin(), v[i].end(), x);
          o ? v[i].insert(p, x) : v[i].erase(p);
          for (; i < kMaxM; i++) {
            a[i] += o ? 1 : -1;
          }
          return;
        }
      }
      v[kMaxM - 1].push_back(x), a[kMaxM - 1]++;
    } else {
      vector<int> l;
      for (int i = 0; i < kMaxM; i++) {
        l.insert(l.end(), v[i].begin(), v[i].end()), v[i].clear();
      }
      auto p = lower_bound(l.begin(), l.end(), x);
      o ? l.insert(p, x) : l.erase(p);
      for (int i = 0, p = 0; i < kMaxM; i++) {
        for (int j = 0; j < kMaxM && p < l.size(); j++) {
          v[i].push_back(l[p++]);
        }
        a[i] = (i ? a[i - 1] : 0) + v[i].size();
      }
    }
  }

  int Find(int x) {
    int p = x / kMaxM;
    for (; p > 0 && a[p - 1] > x; p--) {
    }
    for (; p < kMaxM && a[p] <= x; p++) {
    }
    return v[p][x - (p ? a[p - 1] : 0)];
  }
} h1;
class T {
  int a[kMaxL][kMaxM];

 public:
  void Change(int x, int w) {
    a[0][x] = w;
    for (int i = 1; i < kMaxL; i++) {
      for (int j = max(x - (1 << i) + 1, 0); j <= x; j++) {
        a[i][j] = a[i - 1][j];
        if (j + (1 << i - 1) < kMaxM) {
          a[i][j] = max(a[i][j], a[i - 1][j + (1 << i - 1)]);
        }
      }
    }
  }

  int Max(int x, int y) {
    int l = lg[y - x + 1];
    return max(a[l][x], a[l][y - (1 << l) + 1]);
  }
};
class H2 {
  T t, a[kMaxM];

 public:
  void Change(int x, int w) {
    int p = x / kMaxM, q = x - p * kMaxM;
    a[p].Change(q, w);
    t.Change(p, a[p].Max(0, kMaxM - 1));
  }

  int Max(int x, int y) {
    int px = x / kMaxM, qx = x - px * kMaxM;
    int py = y / kMaxM, qy = y - py * kMaxM;
    if (px == py) {
      return a[px].Max(qx, qy);
    } else {
      int ans = max(a[px].Max(qx, kMaxM - 1), a[py].Max(0, qy));
      if (px + 1 <= py - 1) {
        ans = max(ans, t.Max(px + 1, py - 1));
      }
      return ans;
    }
  }
} h2;

void Update(LL &x, LL y) { x = max(x, y); }

void Add(int x, int y) {
  for (int i = x; i <= n; i += i & -i) {
    d[i - 1] += y;
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i - 1];
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fill(&ans[0], &ans[kMaxN], -2);
  for (int i = 1, j = 0; i <= kMaxM; i++) {
    lg[i] = j;
    if (i == (1 << j + 1)) {
      j++;
    }
  }
  cin >> n >> m;
  for (int i = 0, o, l, r, x; i < m; i++) {
    cin >> o;
    if (o == 1) {
      cin >> l >> r >> x;
      q[k++] = {1, l, i, x}, q[k++] = {2, r + 1, i, x};
      Add(l, 1), Add(r + 1, -1);
    } else {
      cin >> x;
      q[k++] = {3, x, i, Ask(x)}, ans[i] = -1;
    }
  }
  sort(q, q + k, [](Q i, Q j) {
    return i.x < j.x || i.x == j.x && i.o < j.o;
  });
  for (int i = 0; i < k; i++) {
    if (q[i].o == 1) {
      h1.Change(q[i].p, 1), h2.Change(q[i].p, q[i].w);
    } else if (q[i].o == 2) {
      h1.Change(q[i].p, 0), h2.Change(q[i].p, 0);
    } else {
      int w = q[i].w;
      for (int l = 1, r; l <= w; l = r + 1) {
        r = w / (w / l);
        int _l = h1.Find(w - r), _r = h1.Find(w - l);
        Update(ans[q[i].p], 1LL * w / l * h2.Max(_l, _r));
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if (ans[i] > -2) {
      cout << ans[i] << '\n';
    }
  }
  return 0;
}
