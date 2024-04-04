#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const LL kMaxN = 1e6 + 1, kInf = 1e18 + 1;
struct A {
  LL w[2][2];
  A(LL w0 = 0, LL w1 = 0) { w[0][0] = w0, w[1][1] = w1; }
};
struct B {
  LL w[2];
  B(LL w0 = 0, LL w1 = 0) { w[0] = w0, w[1] = w1; }
};
struct V {
  int f, l, d, dr, c, br;
  vector<int> e;
} v[kMaxN];
int n;
LL k;
vector<int> l;

LL Mul(LL x, LL y) {
  if (!y) {
    return 0;
  }
  return x > kInf / y ? kInf : x * y;
}

LL Add(LL x) { return x; }

template <typename... Args>
LL Add(LL x, Args... args) {
  LL y = Add(args...);
  return x + y >= kInf ? kInf : x + y;
}

class T {
  pair<A, B> v[kMaxN << 2];

  pair<A, B> Merge(pair<A, B> x, pair<A, B> y) {
    pair<A, B> ans;
    for (int i : {0, 1}) {
      for (int j : {0, 1}) {
        ans.first.w[i][j] = Add(Mul(x.first.w[i][0], y.first.w[0][j]),
                                Mul(x.first.w[i][0], y.first.w[1][j]),
                                Mul(x.first.w[i][1], y.first.w[0][j]));
      }
    }
    ans.second = {Mul(x.second.w[0], y.second.w[0]),
                  Mul(x.second.w[1], y.second.w[1])};
    return ans;
  }

  void Change(int p, int l, int r, int x, pair<A, B> y, bool b) {
    if (l == r) {
      if (b) {
        v[p].second = y.second;
      } else {
        v[p].first = y.first;
      }
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y, b);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y, b);
    }
    v[p] = Merge(v[p << 1], v[p << 1 | 1]);
  }

  pair<A, B> Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1;
    if (mid >= _l && mid < _r) {
      pair<A, B> x = Ask(p << 1, l, mid, _l, _r);
      pair<A, B> y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
      return Merge(x, y);
    } else if (mid >= _l) {
      return Ask(p << 1, l, mid, _l, _r);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
  }

 public:
  void Change(int x, pair<A, B> y, bool b) { Change(1, 1, n, x, y, b); }
  pair<A, B> Ask(int l, int r) { return Ask(1, 1, n, l, r); }
};
class H {
  T t;

 public:
  void Init() {
    for (int i = 1; i <= n; i++) {
      if (v[i].e.size() == 1 && v[i].e[0] == v[i].f) {
        t.Change(v[i].dr, {A(1, 1), B()}, 0);
        t.Change(v[i].br, {A(), B(1, 1)}, 0);
      }
    }
  }

  void Enable(int x) {
    ;
  }

  void Disable(int x) {
    ;
  }

  void Undo() {
    ;
  }

  LL Ask() {
    ;
  }
} h;

void Input() {
  int fuck, shit[kMaxN];
  cin >> n >> k;
  for (int i = 1; i < n; i++) {
    cin >> shit[i];
  }
  for (int i = 1, x; i < n; i++) {
    cin >> x;
    v[x].e.push_back(shit[i]);
    v[shit[i]].e.push_back(x);
  }
  cin >> fuck;
  l.resize(1);
  for (int i = 1, x; i <= fuck; i++) {
    cin >> x, l.push_back(x);
  }
}

int R(int f, int x) {
  int s = 1, mx = 0;
  v[x].f = f;
  for (int &i : v[x].e) {
    if (i != f) {
      int _s = R(x, i);
      if (s += _s, _s > mx) {
        mx = _s, swap(i, v[x].e[0]);
      }
    }
  }
  return s;
}

void S(int f, int x, bool b) {
  static int k = 0;
  v[x].l = b ? v[f].l : x, v[x].dr = ++k;
  v[v[x].l].d = max(v[v[x].l].d, v[x].dr - v[v[x].l].dr + 1);
  if (!v[x].e.empty() && v[x].e[0] != f) {
    S(x, v[x].e[0], 1);
  }
  for (int i : v[x].e) {
    if (i != f && i != v[x].e[0]) {
      S(x, i, 0);
    }
  }
}

void Init() {
  int k = 0;
  queue<int> q;
  R(0, 1), S(0, 1, 0);
  for (q.push(1); !q.empty(); q.pop()) {
    v[q.front()].br = ++k;
    for (int i : v[q.front()].e) {
      if (i != v[q.front()].f) {
        q.push(i);
      }
    }
  }
  h.Init();
}

void Calc() {
  for (int i = 1, j = 0; i <= l.back(); i++) {
    if (i == l[j]) {
      h.Enable(i), j++;
    } else {
      h.Disable(i);
    }
  }
  int w = l.back();
  while (l.size() > 1) {
    LL _k = h.Ask() - 1;
    if (k > _k) {
      k -= _k;
      for (int i = w; i >= l.back(); i--) {
        h.Undo();
      }
      h.Disable(l.back()), w = l.back(), l.pop_back();
    } else {
      break;
    }
  }
  for (int i = w + 1; i <= n; i++) {
    h.Enable(i);
    LL _k = h.Ask();
    if (k > _k) {
      k -= _k, h.Undo(), h.Disable(i);
    } else {
      l.push_back(i);
    }
  }
  if (k == 1) {
    for (int i : l) {
      cout << i << ' ';
    }
    cout << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Init(), Calc();
  return 0;
}
