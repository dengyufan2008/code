#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1, kMod = 998244353;
int n, a[kMaxN], p[kMaxN], l[kMaxN];
unordered_map<int, int> f[kMaxN];

class Tree {
  int d[kMaxN], p[kMaxN];
  unordered_set<int> e[kMaxN];

  void T(int f, int x) {
    d[x] = d[f] + 1, p[x] = f;
    for (int i : e[x]) {
      if (i != f) {
        T(x, i);
      }
    }
  }

 public:
  void AddEdge(int x, int y) { e[x].insert(y), e[y].insert(x); }
  void Init() { T(0, 1); }
  bool Edge(int x, int y) { return e[x].count(y); }

  int Mid(int x, int y) {
    if (d[x] == d[y]) {
      return p[x] == p[y] ? p[x] : 0;
    } else if (d[x] + 2 == d[y]) {
      return p[p[y]] == x ? p[y] : 0;
    } else if (d[x] == d[y] + 2) {
      return p[p[x]] == y ? p[x] : 0;
    }
    return 0;
  }
} tree;

void Update(int &x, int y) {
  x += y, x >= kMod && (x -= kMod);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    tree.AddEdge(x, y);
  }
  tree.Init();
  for (int i = 1; i <= n; i++) {
    cin >> a[i], p[a[i]] = i;
    for (int &j = l[i] = i - 1; j >= 1 && tree.Edge(a[i], a[j]); j--) {
    }
  }
  f[1][a[1]] = 1;
  for (int i = 1; i < n; i++) {
    for (auto [x, w] : f[i]) {
      Update(f[i + 1][a[i + 1]], w);
      if (tree.Edge(x, a[i + 1])) {
        Update(f[i + 1][x], w);
      } else {
        int y = tree.Mid(x, a[i + 1]);
        if (y && p[y] > i + 1 && l[p[y]] <= i) {
          Update(f[p[y]][a[p[y] - 1]], w);
        }
      }
    }
  }
  int ans = 0;
  for (auto [x, w] : f[n]) {
    Update(ans, w);
  }
  cout << ans << '\n';
  return 0;
}
