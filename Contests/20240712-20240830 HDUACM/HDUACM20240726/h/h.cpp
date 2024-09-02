#include <fstream>
#include <queue>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const LL kMaxN = 1 << 17, kMaxL = 17, kInf = 1e18;
struct V {
  LL d;
  bool b;
  vector<pair<int, int>> e;
} v[kMaxN];
int t, n, m, k, lg;
LL f[kMaxN];
priority_queue<pair<LL, int>> q;

int Log2(int x) {
  int ans = 0;
  for (; x; x >>= 1) {
    ans++;
  }
  return ans;
}

void Update(int x, LL d) {
  if (v[x].d > d) {
    v[x].d = d, q.push({-d, x});
  }
}

void Dij(bool o) {
  for (int i = 1; i <= n; i++) {
    v[i].b = 0;
    if (i == 1 || o) {
      q.push({-v[i].d, i});
    }
  }
  for (; !q.empty();) {
    int x = q.top().second;
    q.pop();
    if (v[x].b) {
      continue;
    }
    v[x].b = 1;
    for (auto i : v[x].e) {
      Update(i.first, v[x].d + i.second);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> k, lg = Log2(n);
    for (int i = 1; i <= n; i++) {
      v[i].d = kInf, v[i].e.clear();
    }
    for (int i = 0; i < 1 << lg; i++) {
      f[i] = kInf;
    }
    for (int i = 1, x, y, z; i <= m; i++) {
      cin >> x >> y >> z;
      v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
    }
    v[1].d = 0, Dij(0);
    for (int i = 1; i <= n; i++) {
      f[i] = v[i].d;
    }
    for (int i = 0; i < lg; i++) {
      for (int j = 1; j <= n; j++) {
        if (j >> i & 1 ^ 1) {
          f[j | 1 << i] = min(f[j | 1 << i], f[j]);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i; j < 1 << lg; j = j + 1 | i) {
        v[i].d = min(v[i].d, f[j] + 1LL * j * k);
      }
    }
    Dij(1);
    for (int i = 2; i <= n; i++) {
      cout << v[i].d << " \n"[i == n];
    }
  }
  return 0;
}
