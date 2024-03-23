#include <algorithm>
#include <fstream>
#include <vector>
// #include <iostream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 201, kMod = 998244353;
struct Solve1 {
  int n, m, ans, c[2], f[2][1 << 20];
  bool b[2][kMaxN];

  void Update(int i, int j, int _j) {
    f[i ^ 1][_j] = (f[i ^ 1][_j] + f[i][j]) % kMod;
  }

  int Main(int _n, int _m, int c0, int c1) {
    n = _n, m = _m, c[0] = c0, c[1] = c1;
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      b[max(x, y) - min(x, y) == c[1]][max(x, y)] = 1;
    }
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
      fill(&f[i & 1 ^ 1][0], &f[i & 1 ^ 1][1 << c[1]], 0);
      for (int j = 0; j < (1 << c[1]); j++) {
        Update(i & 1, j, j >> 1);
        for (int o = 0; o < 2; o++) {
          if (b[o][i + 1] && !(j & 1 << c[1] - c[o])) {
            Update(i & 1, j, (j | 1 << c[1] - c[o]) >> 1 | 1 << c[1] - 1);
          }
        }
      }
    }
    for (int j = 0; j < (1 << c[1]); j++) {
      ans = (ans + f[n & 1][j]) % kMod;
    }
    cout << ans;
    return 0;
  }
} solve1;
struct Solve2 {
  int n, m, k, h, ans, c[2], f[2][1 << 20], l[kMaxN];
  bool b[2][kMaxN];
  vector<int> v[kMaxN];

  int Main(int _n, int _m, int c0, int c1) {
    n = _n, m = _m, c[0] = c0, c[1] = c1;
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      b[max(x, y) - min(x, y) == c[1]][max(x, y)] = 1;
    }
    for (int i = 1; i <= c[0]; i++) {
      for (int j = i; j <= (n + c[1] - 1) / c[1] * c[1]; j += c[0]) {
        v[j % c[1]].push_back(j);
      }
    }
    h = v[0].size();
    for (int i = 1; i <= c[0]; i++) {
      for (int j = i, _k = k; j != i || k == _k; j = (j + c[0]) % c[1]) {
        for (int _v : v[j]) {
          l[++k] = _v;
        }
      }
    }
    for (int i = 1; i <= k; i++) {
      cout << l[i] << ' ';
    }
    cout << h;
    return 0;
  }
} solve2;
int n, m, c[2];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> c[0] >> c[1];
  // if (max(c[0], c[1]) <= 20) {
  //   return solve1.Main(n, m, min(c[0], c[1]), max(c[0], c[1]));
  // } else {
  //   return solve2.Main(n, m, min(c[0], c[1]), max(c[0], c[1]));
  // }
  return solve2.Main(n, m, min(c[0], c[1]), max(c[0], c[1]));
}
