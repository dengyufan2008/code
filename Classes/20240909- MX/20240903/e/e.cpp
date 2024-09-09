#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 501, kInf = 2e9;
struct E {
  int x, w;
};
struct V {
  int in, out, mxdel, f, mn;
  vector<E> e;
} v[kMaxN];
int t, n, m, k, s;
long long ans;

int GetRoot(int x) { return v[x].f == x ? x : v[x].f = GetRoot(v[x].f); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> m >> n >> k >> s;
    for (int i = 1; i <= n; i++) {
      v[i].in = v[i].out = v[i].mxdel = 0;
      v[i].f = i, v[i].mn = kInf, v[i].e.clear();
    }
    ans = 0, v[s].in++;
    for (int i = 1, x, y, z; i <= m; i++) {
      cin >> x >> z >> y;
      ans += z, v[x].out++, v[y].in++;
      v[x].e.push_back({y, z});
    }
    for (int i = 1, x; i <= k; i++) {
      cin >> x, v[x].in++;
    }
    for (int i = 1; i <= n; i++) {
      sort(v[i].e.begin(), v[i].e.end(), [](E i, E j) {
        return i.w > j.w;
      });
      for (; v[i].out > v[i].in; v[i].out--) {
        ans -= v[i].e.back().w;
        v[i].mxdel = v[i].e.back().w;
        v[i].e.pop_back();
      }
    }
    for (int i = 1; i <= n; i++) {
      for (E j : v[i].e) {
        int x = GetRoot(i), y = GetRoot(j.x);
        v[x].mn = min(v[x].mn, min(v[y].mn, j.w - v[i].mxdel));
        if (x != y) {
          v[y].f = x, v[x].in += v[y].in, v[x].out += v[y].out;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      if (v[i].f == i && v[i].in == v[i].out && v[i].mn < kInf) {
        ans -= v[i].mn;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
