#include <fstream>
#include <queue>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 71, kMaxM = kMaxN - 1 >> 2, kInf = 1e9;
struct V {
  int r, f[1 << kMaxM];
  bool b[1 << kMaxM];
  vector<pair<int, int>> e;
} v[kMaxN];
struct Q {
  int x, s, w;
  bool operator<(const Q &q) const {
    return w > q.w;
  }
};
int n, m, k, a;
priority_queue<Q> q;

int T(int x, int p, int q) {
  int c = 0;
  if (v[x].r == p) {
    c = 1, v[x].r = q;
    for (auto i : v[x].e) {
      if (i.second == a) {
        c += T(i.first, p, q);
      }
    }
  }
  return c;
}

void Update(int x, int s, int w) {
  if (v[x].f[s] > w) {
    v[x].f[s] = w, q.push({x, s, w});
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> a >> k, k = 0;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  for (int i = 1; i <= n; i++) {
    v[i].r = kInf;
  }
  for (int i = 1, j = 0; i <= n; i++) {
    if (v[i].r == kInf && T(i, kInf, k++) < 4) {
      T(i, --k, --j);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 1 << k; j++) {
      v[i].f[j] = kInf;
    }
  }
  for (Update(1, v[1].r >= 0 ? 1 << v[1].r : 0, 0); !q.empty();) {
    Q o = q.top();
    q.pop();
    if (v[o.x].b[o.s]) {
      continue;
    }
    v[o.x].b[o.s] = 1;
    int s = v[o.x].r >= 0 ? o.s | 1 << v[o.x].r : o.s;
    for (auto i : v[o.x].e) {
      if (v[o.x].r == v[i.first].r) {
        if (i.second == a) {
          Update(i.first, s, o.w + i.second);
        }
      } else {
        if (v[i.first].r < 0 || o.s >> v[i.first].r & 1 ^ 1) {
          Update(i.first, s, o.w + i.second);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int ans = kInf;
    for (int j = 0; j < 1 << k; j++) {
      ans = min(ans, v[i].f[j]);
    }
    cout << ans << " \n"[i == n];
  }
  return 0;
}
