#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("run.in");
ofstream cout("run.out");

const int kMaxN = 2e5 + 1;
struct V {
  int a, d, k, s, f;
  bool b, o;
  LL l, mn, ans;
  vector<int> e;
} v[kMaxN];
int n, r, s, l[kMaxN];
LL d[kMaxN];
vector<pair<LL, int>> e, q, _e[kMaxN], _q[kMaxN];

void Add(int x, int y) {
  for (int i = x; i >= 1; i -= i & -i) {
    d[i] += y;
  }
}

LL Ask(int x) {
  LL ans = 0;
  for (int i = x; i <= n; i += i & -i) {
    ans += d[i];
  }
  return ans;
}

void CalcR(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f && !v[i].b) {
      CalcR(x, i);
      v[x].s += v[i].s;
      mx = max(mx, v[i].s);
    }
  }
  if (!r && max(mx, s - v[x].s) * 2 <= s) {
    r = x;
  }
}

void CalcL(int f, int x, int s) {
  v[x].l = v[f].l + v[x].d;
  v[x].mn = min(v[f].mn, v[x].l + v[x].k);
  v[x].o = 1, v[x].f = f;
  e.push_back({v[x].k + v[x].d - v[x].l, x});
  _e[s].push_back({v[x].k + v[x].d - v[x].l, x});
  if (v[x].l <= v[x].mn) {
    q.push_back({v[x].l - v[r].d, x});
    _q[s].push_back({v[x].l - v[r].d, x});
  }
  Add(v[x].a, v[x].a);
  for (int i : v[x].e) {
    if (i != f && !v[i].b) {
      CalcL(x, i, s);
    }
  }
}

void Del(int x) {
  if (v[x].o) {
    v[x].o = 0, Add(v[x].a, -v[x].a);
    for (int i : v[x].e) {
      if (i != v[x].f && !v[i].b) {
        Del(i);
      }
    }
  }
}

void Divide() {
  int x = r, _s = s;
  v[x].b = v[x].o = 1, v[x].l = v[x].d;
  v[x].mn = v[x].l + v[x].k;
  e.clear(), e.push_back({v[x].k, x});
  q.clear(), q.push_back({0, x});
  Add(v[x].a, v[x].a);
  for (int i : v[x].e) {
    if (!v[i].b) {
      _e[i].clear(), _q[i].clear(), CalcL(x, i, i);
    }
  }
  sort(e.begin(), e.end()), sort(q.begin(), q.end());
  q.push_back({e.back().first + 1, 0});
  for (int i = 0, j = 0; i < q.size(); i++) {
    for (; j < e.size() && e[j].first < q[i].first; j++) {
      Del(e[j].second);
    }
    v[q[i].second].ans += Ask(v[q[i].second].a);
  }
  for (int y : v[x].e) {
    if (!v[y].b) {
      for (auto i : _e[y]) {
        v[i.second].o = 1, Add(v[i.second].a, v[i.second].a);
      }
      sort(_e[y].begin(), _e[y].end()), sort(_q[y].begin(), _q[y].end());
      _q[y].push_back({_e[y].back().first + 1, 0});
      for (int i = 0, j = 0; i < _q[y].size(); i++) {
        for (; j < _e[y].size() && _e[y][j].first < _q[y][i].first; j++) {
          Del(_e[y][j].second);
        }
        v[_q[y][i].second].ans -= Ask(v[_q[y][i].second].a);
      }
    }
  }
  for (int i : v[x].e) {
    if (!v[i].b) {
      r = 0, s = v[i].s > v[x].s ? _s - v[x].s : v[i].s, CalcR(x, i), Divide();
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  v[0].a = kMaxN, cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].a >> v[i].d >> v[i].k, l[i] = i;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  r = 0, s = n, CalcR(0, 1), Divide();
  for (int i = 1; i <= n; i++) {
    cout << v[i].ans << " \n"[i == n];
  }
  return 0;
}
