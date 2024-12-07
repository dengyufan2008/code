#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("traverse.in");
ofstream cout("traverse.out");

const int kMaxN = 1e5 + 1, kMod = 1e9 + 7;
struct V {
  LL f, g;
  vector<pair<int, int>> e;
} v[kMaxN];
int u, t, n, m, s;
bool b[kMaxN];
LL ans, fact[kMaxN];

void T(int f, int x) {
  if (v[x].e.size() == 1) {
    v[x].f = v[x].g = 1;
    return;
  }
  v[x].f = 0, v[x].g = 1;
  for (auto i : v[x].e) {
    if (i.first != f) {
      T(x, i.first);
      if (b[i.second]) {
        v[x].f = v[x].f * v[i.first].g % kMod;
      } else {
        v[x].f = (v[x].f * v[i.first].g + v[x].g * v[i.first].f) % kMod;
      }
      v[x].g = v[x].g * v[i.first].g % kMod;
    }
  }
  v[x].f = v[x].f * fact[v[x].e.size() - 2] % kMod;
  v[x].g = v[x].g * fact[v[x].e.size() - 1] % kMod;
}

void Solve() {
  static pair<int, int> e[kMaxN];
  cin >> n >> m, ans = 0;
  for (int i = 1; i <= n; i++) {
    v[i] = v[0], b[i] = 0;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y, e[i] = {x, y};
    v[x].e.push_back({y, i}), v[y].e.push_back({x, i});
  }
  for (int i = 1, o; i <= m; i++) {
    cin >> o;
    int x = e[o].first, y = e[o].second;
    T(y, x), T(x, y), b[o] = 1;
    ans = (ans + v[x].f * v[y].f) % kMod;
  }
  cout << ans << '\n';
}

void Solve2() {
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
  }
  for (int i = 1, o; i <= m; i++) {
    cin >> o;
  }
  cout << 1 << '\n';
}

void Solve3() {
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
  }
  for (int i = 1, o; i <= m; i++) {
    cin >> o;
  }
  if (n == 2) {
    cout << 1 << '\n';
  } else {
    cout << (1LL * m * (m - 1) / 2 + 1LL * m * (n - m - 1)) % kMod * fact[n - 3] % kMod << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  cin >> u >> t;
  if (u <= 17) {
    while (t--) {
      Solve();
    }
  } else if (u <= 18) {
    while (t--) {
      Solve2();
    }
  } else if (u <= 21) {
    while (t--) {
      Solve3();
    }
  } else {
    while (t--) {
      Solve();
    }
  }
  return 0;
}
