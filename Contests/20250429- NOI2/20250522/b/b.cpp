#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 2;
struct A {
  int w[6];
} c, a[kMaxN];
int t, n;

class Uni {
  int f[kMaxN];

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

 public:
  void Init() {
    for (int i = 1; i <= n + 1; i++) {
      f[i] = i;
    }
  }

  bool Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    return x != y ? f[x] = y, 1 : 0;
  }
} uni;

bool Init() {
  struct V {
    int x, o, p;
    const bool operator<(const V &v) const {
      return o < v.o || o == v.o && p > v.p;
    }
  };
  static bool b[kMaxN];
  static vector<V> v[kMaxN];
  static priority_queue<V> q;
  cin >> n, c = {};
  for (; !q.empty(); q.pop()) {
  }
  for (int i = 1; i <= n; i++) {
    b[i] = 0, v[i].clear();
  }
  for (int i = 1; i <= n; i++) {
    for (int o = 1; o <= 5; o++) {
      cin >> a[i].w[o];
      a[i].w[o] += a[i].w[o - 1];
      v[a[i].w[o - 1] + 1].push_back({i, o, a[i].w[o]});
    }
  }
  for (int i = 1, o = 5; i <= n; i++) {
    for (V _v : v[i]) {
      !b[_v.x] ? q.push(_v) : void();
    }
    for (; b[q.top().x]; q.pop()) {
    }
    if (o < q.top().o) {
      cout << 0 << '\n';
      return 0;
    }
    o = q.top().o, b[q.top().x] = 1;
    q.pop(), c.w[o]++;
  }
  for (int o = 1; o <= 5; o++) {
    c.w[o] += c.w[o - 1];
  }
  return 1;
}

void Solve() {
  uni.Init();
  for (int i = 1; i <= n; i++) {
    bool u = 0;
    for (int o = 1; o <= 5; o++) {
      int l = max(a[i].w[o - 1], n - c.w[o]) + 1;
      int r = min(a[i].w[o], n - c.w[o - 1]);
      if (l <= r) {
        u = 1;
        if (!uni.Merge(l, r + 1)) {
          cout << 0 << '\n';
          return;
        }
      }
    }
    if (!u) {
      cout << 0 << '\n';
      return;
    }
  }
  cout << 1 << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    Init() ? Solve() : void();
  }
  return 0;
}
