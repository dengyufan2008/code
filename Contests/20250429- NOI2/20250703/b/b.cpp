// 出题人是不是母亲似了, 硬来一个构造方案
// 老子顶着 10s 一次的编译写代码
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5e4 + 1, kMaxL = 30;
struct V {
  int c, s[2];
  vector<int> l;
} v[kMaxN * kMaxL];
int t, n, m, k, a[kMaxN];

void Insert(int x, int o) {
  v[1].c++, v[1].l.push_back(o);
  for (int i = kMaxL - 1, p = 1; i >= 0; i--) {
    bool u = x >> i & 1;
    !v[p].s[u] && (v[p].s[u] = ++m);
    p = v[p].s[u], v[p].c++, v[p].l.push_back(o);
  }
}

// 将 p 子树和 q 子树内的数匹配, 使得匹配的数对异或大于等于 x 的后 d 位, 求最大匹配
int Calc2(int p, int q, int x, int d) {
  if (!p || !q) {
    return 0;
  } else if (d < 0) {
    return min(v[p].c, v[q].c);
  } else if (x >> d & 1) {
    return Calc2(v[p].s[0], v[q].s[1], x, d - 1) + Calc2(v[p].s[1], v[q].s[0], x, d - 1);
  }
  int pl = v[v[p].s[0]].c, pr = v[v[p].s[1]].c;
  int ql = v[v[q].s[0]].c, qr = v[v[q].s[1]].c;
  int w1 = min(pl, qr), w2 = min(pr, ql);
  pl -= w1, qr -= w1, pr -= w2, ql -= w2;
  if (pl && ql) {
    return w1 + w2 + min(Calc2(v[p].s[0], v[q].s[0], x, d - 1), min(pl, ql));
  } else if (pr && qr) {
    return w1 + w2 + min(Calc2(v[p].s[1], v[q].s[1], x, d - 1), min(pr, qr));
  } else {
    return w1 + w2;
  }
}

// 将 p 子树内的数染色, 至少染成 ans 种颜色才能让同色组内两两异或大于等于 x 的后 d 位
int Calc(int p, int x, int d) {
  if (!p) {
    return 0;
  } else if (d < 0) {
    return 1;
  } else if (x >> d & 1) {
    return v[p].c - Calc2(v[p].s[0], v[p].s[1], x, d - 1);
  } else {
    return max(Calc(v[p].s[0], x, d - 1), Calc(v[p].s[1], x, d - 1));
  }
}

vector<pair<int, int>> Match(int p, int q, int x, int d) {
  static int _h, h[kMaxN];
  if (!p || !q) {
    return {};
  } else if (d < 0) {
    int ans = min(v[p].c, v[q].c);
    vector<pair<int, int>> g = {};
    for (int i = 0; i < ans; i++) {
      g.push_back({v[p].l[i], v[q].l[i]});
    }
    return g;
  } else if (x >> d & 1) {
    auto g1 = Match(v[p].s[0], v[q].s[1], x, d - 1);
    auto g2 = Match(v[p].s[1], v[q].s[0], x, d - 1);
    g1.insert(g1.end(), g2.begin(), g2.end());
    return g1;
  }
  vector<pair<int, int>> g = {};
  int pl = v[v[p].s[0]].c, pr = v[v[p].s[1]].c;
  int ql = v[v[q].s[0]].c, qr = v[v[q].s[1]].c;
  int w1 = min(pl, qr), w2 = min(pr, ql);
  pl -= w1, qr -= w1, pr -= w2, ql -= w2;
  if (pl && ql) {
    g = Match(v[p].s[0], v[q].s[0], x, d - 1), _h++;
    for (; g.size() > min(pl, ql); g.pop_back()) {
    }
    for (auto i : g) {
      h[i.first] = h[i.second] = _h;
    }
  } else if (pr && qr) {
    g = Match(v[p].s[1], v[q].s[1], x, d - 1), _h++;
    for (; g.size() > min(pr, qr); g.pop_back()) {
    }
    for (auto i : g) {
      h[i.first] = h[i.second] = _h;
    }
  } else {
    _h++;
  }
  for (int i = 0, pj = 0, qj = 0; i < w1; i++) {
    for (; h[v[v[p].s[0]].l[pj]] == _h; pj++) {
    }
    for (; h[v[v[q].s[1]].l[qj]] == _h; qj++) {
    }
    g.push_back({v[v[p].s[0]].l[pj++], v[v[q].s[1]].l[qj++]});
  }
  for (int i = 0, pj = 0, qj = 0; i < w2; i++) {
    for (; h[v[v[p].s[1]].l[pj]] == _h; pj++) {
    }
    for (; h[v[v[q].s[0]].l[qj]] == _h; qj++) {
    }
    g.push_back({v[v[p].s[1]].l[pj++], v[v[q].s[0]].l[qj++]});
  }
  return g;
}

int Construct(int p, int x, int d, int w) {
  if (!p) {
    return 0;
  } else if (d < 0) {
    for (int i : v[p].l) {
      a[i] = w;
    }
    return 1;
  } else if (x >> d & 1) {
    auto ans = Match(v[p].s[0], v[p].s[1], x, d - 1);
    for (auto i : ans) {
      a[i.first] = a[i.second] = w++;
    }
    for (int i : v[p].l) {
      !a[i] && (a[i] = w++);
    }
    return v[p].c - ans.size();
  } else {
    return max(Construct(v[p].s[0], x, d - 1, w), Construct(v[p].s[1], x, d - 1, w));
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> k, m = 1;
    for (int i = 1, x; i <= n; i++) {
      cin >> x, Insert(x, i);
    }
    int l = 1, r = (1 << kMaxL) - 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Calc(1, mid, kMaxL - 1) <= k) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    Construct(1, r, kMaxL - 1, 1);
    cout << r << '\n';
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " \n"[i == n];
      a[i] = 0;
    }
    fill(&v[1], &v[m] + 1, v[0]);
  }
  return 0;
}
