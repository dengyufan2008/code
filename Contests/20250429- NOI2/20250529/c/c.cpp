#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e6 + 1;
struct V {
  int f, e[26];
  bool b;
  int d, p, r, s;
  vector<int> g;
} v[kMaxN];
int n, m;
string s[kMaxN];

void Update(pair<int, int> &x, pair<int, int> y) {
  x.first = min(x.first, y.first);
  x.second = max(x.second, y.second);
}

class Bit {
  int n;
  pair<int, int> v[kMaxN];

 public:
  void Init(int _n) {
    n = _n, fill(&v[1], &v[n] + 1, make_pair(m + 1, 0));
  }

  void Change(int x, int w) {
    for (int i = x; i >= 1; i -= i & -i) {
      Update(v[i], {w, w});
    }
  }

  pair<int, int> Ask(int x) {
    pair<int, int> ans = {m + 1, 0};
    for (int i = x; i <= n; i += i & -i) {
      Update(ans, v[i]);
    }
    return ans;
  }
} bit;

void T(int x) {
  static int k = 0;
  v[x].r = ++k, v[x].s = 1;
  for (int i : v[x].g) {
    v[i].p = v[i].b ? i : v[x].p;
    T(i);
    v[x].s += v[i].s;
  }
}

void Init() {
  static queue<int> q;
  cin >> n, m = 1;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    int p = 1;
    for (int j = 0; j < s[i].size(); j++) {
      int x = s[i][j] - 'a';
      if (!v[p].e[x]) {
        v[p].e[x] = ++m;
      }
      p = v[p].e[x];
    }
    v[p].b = 1;
  }
  for (q.push(1); !q.empty(); q.pop()) {
    int x = q.front(), y, z;
    for (int i = 0; i < 26; i++) {
      y = v[x].e[i];
      if (y) {
        v[y].d = v[x].d + 1, q.push(y);
        for (z = v[x].f; z && !v[z].e[i]; z = v[z].f) {
        }
        v[y].f = z ? v[z].e[i] : 1, v[v[y].f].g.push_back(y);
      }
    }
  }
  T(1);
}

int Calc(string &s) {
  struct A {
    int p, l, r;
  };
  static pair<int, int> w[kMaxN];
  static vector<int> l;
  static vector<A> h, _h;
  l.clear(), h.clear();
  for (int i = 0, j, p = 1, q; i < s.size(); i++) {
    p = v[p].e[s[i] - 'a'], q = i + 1 == s.size() ? v[p].f : p;
    for (j = 0; j < 2 && v[q].p; j++, q = v[q].f) {
      q = v[q].p;
      h.push_back({q, v[p].d - v[q].d + 1, v[p].d});
    }
    if (j == 2) {
      l.push_back(v[q].r);
    }
  }
  sort(l.begin(), l.end());
  for (A i : h) {
    auto p = lower_bound(l.begin(), l.end(), v[i.p].r);
    if (p == l.end() || *p >= v[i.p].r + v[i.p].s) {
      _h.push_back(i);
    }
  }
  h.swap(_h), _h.clear();
  for (A i : h) {
    w[i.p] = {m + 1, 0};
  }
  sort(h.begin(), h.end(), [](A i, A j) {
    return i.l < j.l || i.l == j.l && i.r > j.r;
  });
  bit.Init(s.size());
  for (A i : h) {
    Update(w[i.p], bit.Ask(i.r));
    bit.Change(i.r, i.p);
  }
  int c = 0;
  for (A i : h) {
    if (w[i.p].first == w[i.p].second) {
      c++, w[i.p] = {m + 1, 0};
    }
  }
  return c;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += Calc(s[i]);
  }
  cout << ans << '\n';
  return 0;
}
