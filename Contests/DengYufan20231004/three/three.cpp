#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("three.in");
ofstream cout("three.out");

const LL kMaxN = 5e5 + 1;
struct V {
  LL d, b;
  vector<LL> e, g;
} v[kMaxN];
LL n, m, d, ans, a[kMaxN];

void Add(LL x, LL y) {
  for (LL i = x; i <= n; i += i & -i) {
    a[i] += y;
  }
}

LL Ask(LL x) {
  LL ans = 0;
  for (LL i = x; i >= 1; i -= i & -i) {
    ans += a[i];
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> d;
  for (LL i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
    v[x].d++, v[y].d++;
  }
  for (LL i = 1; i <= n; i++) {
    sort(v[i].e.begin(), v[i].e.end());
    for (LL j : v[i].e) {
      if (v[i].d < v[j].d || v[i].d == v[j].d && i < j) {
        v[i].g.push_back(j);
      }
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j : v[i].e) {
      ans += (max(i, j) - min(i, j) <= d) * (Ask(n) - Ask(max(i, j) - d - 1));
      Add(j, 1);
    }
    for (LL j : v[i].e) {
      Add(j, -1);
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j : v[i].g) {
      v[j].b = i;
    }
    for (LL j : v[i].g) {
      for (LL k : v[j].g) {
        if (v[k].b == i && max({i, j, k}) - min({i, j, k}) <= d) {
          ans -= 2;
        }
      }
    }
  }
  cout << ans;
  return 0;
}
