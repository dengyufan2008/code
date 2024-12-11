#include <fstream>
#include <queue>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

// const int kMaxN = 1e5 + 1, kMaxL = 17;
const int kMaxN = 1e3 + 1, kMaxL = 10;
struct V {
  int d, w, f[kMaxL];
  vector<int> e;
  priority_queue<int> q[2];
} v[kMaxN];
int u, n, m, k;

void Init(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    Init(x, i);
  }
}

int Lca(int x, int y) {
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int Dis(int o, int x, int y, int z) {
  int i = Lca(o, x), j = Lca(o, y);
  if (v[i].d > v[z].d) {
    return v[o].d - v[i].d;
  } else if (v[j].d > v[z].d) {
    return v[o].d - v[j].d;
  }
  int k = Lca(o, z);
  return v[o].d + v[z].d - (v[k].d << 1);
}

void Add(int x, int y, bool o) {  // 1:insert 0:delete
  int z = Lca(x, y);
  for (int i = 1; i <= n; i++) {
    v[i].q[o].push(Dis(i, x, y, z));
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> u;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Init(0, 1);
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> y, k++, Add(x, y, 1);
    } else if (o == 2) {
      cin >> y, k--, Add(x, y, 0);
    } else if (!k) {
      cout << 0 << '\n';
    } else {
      int ans = 0;
      for (int j = 1; j <= n; j++) {
        while (!v[j].q[0].empty() && v[j].q[0].top() == v[j].q[1].top()) {
          v[j].q[0].pop(), v[j].q[1].pop();
        }
        ans += v[j].q[1].top() <= x;
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
