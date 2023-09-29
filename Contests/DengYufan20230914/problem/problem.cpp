#include <fstream>
#include <vector>

using namespace std;

ifstream cin("problem.in");
ofstream cout("problem.out");

const int kMaxN = 1e5 + 1, kInf = 1e9;
struct V {
  int d, r, t0, t1;
  bool b;
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m, k, t, ans, c[kMaxN << 1];

void T(int f, int x) {
  v[x].r = ++k, v[x].b = 0;
  for (auto i : v[x].e) {
    if (i.second != f) {
      if (!v[i.first].r) {
        v[i.first].d = v[x].d + 1, c[i.second] = -kInf;
        T(i.second, i.first);
      } else if (v[i.first].r < v[x].r) {
        if (v[x].d - v[i.first].d & 1) {  // 偶环
          v[x].t0++, v[i.first].t0--, c[i.second] = -kInf;
        } else {
          v[x].t1++, v[i.first].t1--, c[i.second]++, t++;
        }
      }
    }
  }
}

void R(int f, int x) {
  v[x].b = 1;
  for (auto i : v[x].e) {
    if (i.second != f) {
      if (!v[i.first].b) {
        R(i.second, i.first);
        v[x].t0 += v[i.first].t0, v[x].t1 += v[i.first].t1;
      }
    }
  }
  if (f && !v[x].t0 && v[x].t1 == t) {
    ans++;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back({y, i}), v[y].e.push_back({x, i});
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].r) {
      T(0, i), R(0, i);
    }
  }
  for (int i = 1; i <= m; i++) {
    if (c[i] == t) {
      ans++;
    }
  }
  cout << ans;
  return 0;
}
