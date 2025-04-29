#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long
#define Point pair<int, LL>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 1e6 + 1, kInf = 1e18;
struct V {
  int d, l, r, s;
  LL f;
  vector<pair<int, int>> e;
  vector<int> g;
} v[kMaxN];
int n, m;
LL ans;

LL Sqr(int x) { return 1LL * x * x; }

void Tarjan(int f, int x) {
  static int k;
  static vector<int> l;
  v[x].d = v[x].l = ++k;
  l.push_back(x);
  for (auto i : v[x].e) {
    if (!v[i.first].d) {
      Tarjan(i.second, i.first);
      v[x].l = min(v[x].l, v[i.first].l);
    } else if (i.second != f) {
      v[x].l = min(v[x].l, v[i.first].d);
    }
  }
  if (v[x].d == v[x].l) {
    for (; l.back() != x; l.pop_back()) {
      v[l.back()].r = x, v[x].s++;
      v[x].e.insert(v[x].e.end(), v[l.back()].e.begin(), v[l.back()].e.end());
      v[l.back()].e.clear();
    }
    v[x].r = x, v[x].s++, l.pop_back();
  }
}

void CalcG() {
  for (int i = 1; i <= n; i++) {
    for (auto j : v[i].e) {
      if (v[j.first].r != i) {
        v[i].g.push_back(v[j.first].r);
      }
    }
  }
}

LL Cross(Point o, Point x, Point y) {
  return (x.first - o.first) * (y.second - o.second) - (y.first - o.first) * (x.second - o.second);
}

int Find(int k, vector<Point> &l) {
  int x = 0, y = l.size() - 1;
  while (x <= y) {
    int mid = x + y >> 1;
    if (!mid || l[mid].second - l[mid - 1].second < 1LL * k * (l[mid].first - l[mid - 1].first)) {
      x = mid + 1;
    } else {
      y = mid - 1;
    }
  }
  return y;
}

void Push(int x, LL y, vector<Point> &l) {
  for (; l.size() > 1 && Cross(l[l.size() - 2], l.back(), {x, y}) <= 0; l.pop_back()) {
  }
  l.push_back({x, y});
}

void Dp(int f, int x) {
  static vector<int> g;
  static vector<Point> l;
  for (int i : v[x].g) {
    if (i != f) {
      g.push_back(i);
    }
  }
  v[x].g.swap(g), g.clear();

  if (v[x].g.empty()) {
    v[x].f = Sqr(v[x].s);
    return;
  }

  for (int i : v[x].g) {
    if (i != f) {
      Dp(x, i), v[x].s += v[i].s;
    }
  }

  sort(v[x].g.begin(), v[x].g.end(), [](int i, int j) {
    return v[i].s < v[j].s;
  });
  v[x].f = kInf, l.clear();
  for (int i : v[x].g) {
    if (i != f) {
      v[x].f = min(v[x].f, v[i].f + Sqr(v[x].s - v[i].s));
      if (!l.empty()) {
        int t = Find(n - v[i].s, l);
        ans = min(ans, l[t].second - 1LL * l[t].first * (n - v[i].s) + v[i].f + Sqr(n - v[i].s));
      }
      Push(v[i].s << 1, v[i].f + Sqr(v[i].s), l);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, x++, y++;
    v[x].e.push_back({y, i}), v[y].e.push_back({x, i});
  }
  Tarjan(0, 1), CalcG();
  ans = kInf, Dp(0, 1), ans = min(ans, v[1].f);
  cout << (1LL * n * n - ans >> 1) << '\n';
  return 0;
}
