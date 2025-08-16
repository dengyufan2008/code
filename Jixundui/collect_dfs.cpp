// 3800ms
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("collect.in");
ofstream cout("collect.out");

const LL kMaxN = 1e6 + 1, kInf = 1e18;
struct V {
  int o, r;
  LL ans;
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m, o;
LL ans;

LL S(int x, int o) {
  static int k = 0;
  LL ans = 0;
  v[x].o = o, v[x].r = ++k;
  for (auto i : v[x].e) {
    if (!v[i.first].r) {
      v[x].ans += i.second;
      ans += i.second + S(i.first, o);
    } else if (v[i.first].r > v[x].r) {
      v[x].ans += i.second;
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z});
    v[y].e.push_back({x, z});
  }
  ans = kInf;
  for (int i = 1; i <= n; i++) {
    if (!v[i].o) {
      LL w = S(i, i);
      if (ans > w) {
        o = i, ans = w;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << (v[i].o == o ? v[i].ans : 0) << " \n"[i == n];
  }
  return 0;
}
