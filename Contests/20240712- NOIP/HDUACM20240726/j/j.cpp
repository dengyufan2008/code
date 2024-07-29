#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 5e4 + 1, kMaxM = 201, kInf = 1e9;
struct E {
  int o, p, w;  // 0:ans 1:d 2:p
};
int t, n, m, ans, b[kMaxN], d[kMaxN], p[kMaxN];
vector<int> s, v[kMaxN << 2];
vector<E> _e;
vector<vector<E>> e;

void Insert(int x) {
  int _ans = kInf;
  _e.clear();
  if (s.size() > kMaxM) {
    for (int i = 1; i < kMaxM && i < x; i++) {
      _ans = min(_ans, i + d[x - i]);
    }
    for (int i = 1; i < kMaxM && i * x <= n; i++) {
      _ans = min(_ans, i + p[i * x]);
    }
  } else {
    for (int i : s) {
      _ans = min(_ans, min(x / i + x % i, i / x + i % x));
    }
  }
  if (ans > _ans) {
    _e.push_back({0, 0, ans}), ans = _ans;
  }
  s.push_back(x);
  for (int i = x, j = 1; j < kMaxM && i <= n; i += x, j++) {
    if (d[i] > j) {
      _e.push_back({1, i, d[i]}), d[i] = j;
    }
  }
  for (int i = 0; i < kMaxM && i < x; i++) {
    if (p[x - i] > i) {
      _e.push_back({2, x - i, p[x - i]}), p[x - i] = i;
    }
  }
  e.push_back(_e);
}

void Undo() {
  s.pop_back(), _e = e.back(), e.pop_back();
  reverse(_e.begin(), _e.end());
  for (E i : _e) {
    if (i.o == 0) {
      ans = i.w;
    } else if (i.o == 1) {
      d[i.p] = i.w;
    } else {
      p[i.p] = i.w;
    }
  }
}

void Add(int p, int l, int r, int _l, int _r, int x) {
  if (l >= _l && r <= _r) {
    return v[p].push_back(x);
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, x);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, x);
  }
}

void Calc(int p, int l, int r) {
  for (int i : v[p]) {
    Insert(i);
  }
  if (l == r) {
    cout << (ans == kInf ? -1 : ans) << '\n';
  } else {
    int mid = l + r >> 1;
    Calc(p << 1, l, mid), Calc(p << 1 | 1, mid + 1, r);
  }
  for (int i : v[p]) {
    Undo();
  }
  v[p].clear();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    ans = kInf;
    for (int i = 1; i <= n; i++) {
      b[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      d[i] = p[i] = kInf;
    }
    for (int i = 1, o, x; i <= m; i++) {
      cin >> o >> x;
      if (o) {
        b[x] = i;
      } else {
        Add(1, 1, m, b[x], i - 1, x);
        b[x] = 0;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (b[i]) {
        Add(1, 1, m, b[i], m, i);
      }
    }
    Calc(1, 1, m);
  }
  return 0;
}
