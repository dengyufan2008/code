#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 3e5 + 1;
struct V {
  int p, r, s;
  LL w, f;
  vector<int> e;
} v[kMaxN];
int t, n, m, k;

class Uni {
  int f[kMaxN];

 public:
  void Init() {
    for (int i = 1; i <= n; i++) {
      f[i] = i;
    }
  }

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    x != y && (f[x] = y);
  }
} uni;

// 单点加链求和 -> 子树加单点查
class Bit {
  LL d[kMaxN];

 public:
  void Init() {
    for (int i = 1; i <= n; i++) {
      d[i] = 0;
    }
  }

  void Add(int x, LL w) {
    for (int i = v[x].r; i <= n; i += i & -i) {
      d[i] += w;
    }
    for (int i = v[x].r + v[x].s; i <= n; i += i & -i) {
      d[i] -= w;
    }
  }

  LL Ask(int x) {
    LL ans = 0;
    for (int i = v[x].r; i >= 1; i -= i & -i) {
      ans += d[i];
    }
    return ans;
  }
} bit;

void Init(int x) {
  v[x].r = ++k, v[x].s = 1, v[x].f = v[x].w;
  for (int i : v[x].e) {
    Init(i), v[x].s += v[i].s;
    v[x].f += max(v[i].f, 0LL);
  }
  if (v[x].f >= 0) {
    uni.Merge(x, v[x].p);
  } else {
    bit.Add(x, v[x].f);
  }
}

void Add(int x, int y) {
  for (int i = uni.GetRoot(x); i; i = uni.GetRoot(i)) {
    int t = min(-v[i].f, (LL)y);
    v[i].f += t, y -= t, bit.Add(i, t);
    if (v[i].f == 0) {
      uni.Merge(i, v[i].p);
    } else {
      break;
    }
  }
}

LL Ask(int x) { return max(-bit.Ask(x), 1LL); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n, k = 0, fill(&v[1], &v[n] + 1, v[0]);
    for (int i = 1; i <= n; i++) {
      cin >> v[i].w;
    }
    for (int i = 2, x; i <= n; i++) {
      cin >> x, v[i].p = x, v[x].e.push_back(i);
    }
    uni.Init(), bit.Init(), Init(1), cin >> m;
    for (int i = 1, o, x, y; i <= m; i++) {
      cin >> o >> x;
      if (o == 1) {
        cin >> y, Add(x, y);
      } else {
        cout << Ask(x) << '\n';
      }
    }
  }
  return 0;
}
