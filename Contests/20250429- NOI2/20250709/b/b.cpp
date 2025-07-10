#include <fstream>
#include <set>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1;
struct V {
  int f, c, _c;
  vector<int> e;
} v[kMaxN];
int n, m;

void Do(int f, int x) {
  v[x].f = f, v[f]._c += v[x].c;
  for (int i : v[x].e) {
    if (i != f) {
      Do(x, i);
    }
  }
}

void Solve1() {
  static int a[kMaxN];
  for (int i = 1; i <= n; i++) {
    a[i] = i, v[i].c = 1;
  }
  for (int i = 1, x; i <= m; i++) {
    cin >> x, Do(a[x], a[x]);
    LL ans = 0;
    for (int j = 1; j <= n; j++) {
      v[j].c = v[j]._c, v[j]._c = 0;
      ans += 1LL * v[j].c * (v[j].c - 1) / 2;
      a[j] = v[a[j]].f;
    }
    cout << ans << '\n';
  }
}

LL Calc(int x) { return 1LL * x * (x - 1) / 2; }

void Solve2() {
  static set<int> s;
  LL ans = 0;
  for (int i = 0; i <= n; i++) {
    s.insert(i);
  }
  for (int i = 1, x; i <= m; i++) {
    cin >> x;
    auto p = s.lower_bound(x);
    int r = *p, l = *--p;
    if (l == 0 && r == n) {
    } else if (l == 0) {
      int rr = *s.upper_bound(r);
      ans -= Calc(r - l);
      ans -= Calc(rr - r);
      ans += Calc(rr - l);
      s.erase(r);
    } else if (r == n) {
      int ll = *--s.lower_bound(l);
      ans -= Calc(r - l);
      ans -= Calc(l - ll);
      ans += Calc(r - ll);
      s.erase(l);
    } else {
      int ll = *--s.lower_bound(l);
      int rr = *s.upper_bound(r);
      ans -= Calc(l - ll);
      ans -= Calc(r - l);
      ans -= Calc(rr - r);
      ans += Calc(rr - ll);
      s.erase(l), s.erase(r);
    }
    cout << ans << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  cin >> m;
  if (n <= 5000 && m <= 5000) {
    Solve1();
  } else {
    Solve2();
  }
  return 0;
}
