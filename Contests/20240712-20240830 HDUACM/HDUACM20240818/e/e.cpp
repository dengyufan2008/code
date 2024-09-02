// not be done
#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long
#define LLL __int128_t
#define Point pair<LL, LL>

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 2e5 + 1;
struct Poly {
  LL s;
  vector<Point> v;
} a[kMaxN];
int t, n;

LL Cross(Point o, Point x, Point y) {
  return (x.first - o.first) * (y.second - o.second) -
         (y.first - o.first) * (x.second - o.second);
}

bool C(Poly x, Poly y) {
  for (int u = 0, i = 0, j = 1, k = 2; u < y.v.size(); u++) {
    Point p = y.v[u], q = y.v[(u + 1) % y.v.size()];
  }
}

bool C() {
  for (int i = 2; i <= n; i++) {
    if (!C(a[i - 1], a[i])) {
      return 0;
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
      cin >> x;
      for (int j = 0, y, z; j < x; j++) {
        cin >> y >> z;
        a[i].v.push_back({y, z});
      }
      a[i].s += Cross({0, 0}, a[i].v.back(), a[i].v.front());
      for (int j = 1; j < a[i].v.size(); j++) {
        a[i].s += Cross({0, 0}, a[i].v[j - 1], a[i].v[j]);
      }
    }
    sort(a + 1, a + n + 1, [](Poly x, Poly y) {
      return x.s < y.s;
    });
    cout << (C() ? "Yes\n" : "No\n");
  }
  return 0;
}
