#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1.5e5 + 1;
int n, m, q, a[2][kMaxN];
vector<pair<bool, int>> l;

class Uni {
  int f[kMaxN], s[kMaxN];

 public:
  void Init(int n) {
    for (int i = 0; i <= n; i++) {
      f[i] = i, s[i] = 1;
    }
  }

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

  int Size(int x) { return s[GetRoot(x)]; }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    if (x != y) {
      f[x] = y, s[y] += s[x];
    }
  }
} uni[2];

LL Solve(int x, int y) {
  int mx[2] = {};
  LL ans = 0;
  uni[0].Init(n), uni[1].Init(m);
  for (auto i : l) {
    if (i.first && (i.second < x || i.second > y)) {
      continue;
    }
    uni[i.first].Merge(i.second, i.second - 1);
    int s = uni[i.first].Size(i.second) - 1;
    mx[i.first] = max(mx[i.first], s);
    ans = max(ans, 1LL * a[i.first][i.second] * (s + mx[!i.first]));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[0][i], l.push_back({0, i});
  }
  for (int i = 1; i <= m; i++) {
    cin >> a[1][i], l.push_back({1, i});
  }
  sort(l.begin(), l.end(), [](pair<bool, int> i, pair<bool, int> j) {
    return a[i.first][i.second] > a[j.first][j.second];
  });
  for (int i = 1, x, y; i <= q; i++) {
    cin >> x >> y, x++, y++;
    cout << Solve(x, y) << '\n';
  }
  return 0;
}
