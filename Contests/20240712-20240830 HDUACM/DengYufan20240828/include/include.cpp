#include <fstream>
#include <queue>
#include <set>

using namespace std;

ifstream cin("include.in");
ofstream cout("include.out");

const int kMaxN = 1e5 + 1, kMaxV = kMaxN * 2, kB = 1000;
int n, m, b[kMaxV], t[kMaxN], w[kMaxN << 2];
bool u[kMaxN];
vector<int> v, a[kMaxN], d[kMaxN];
set<int> s[kMaxV];
priority_queue<int> l[kMaxN], q[kMaxN];
priority_queue<int, vector<int>, greater<int>> r[kMaxN];

void Change(int p, int l, int r, int x, int y) {
  if (l == r) {
    w[p] = y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, y);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, y);
  }
  w[p] = max(w[p << 1], w[p << 1 | 1]);
}

int Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return w[p];
  }
  int mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    ans = max(ans, Ask(p << 1, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = max(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r));
  }
  return ans;
}

void Update(int x) {
  for (; !q[x].empty() && !u[q[x].top()]; q[x].pop()) {
  }
  int _t = q[x].empty() ? 0 : q[x].top();
  if (t[x] != _t) {
    t[x] = _t;
    if (u[x]) {
      Change(1, 1, n, x, _t);
    }
  }
}

void Init() {
  for (int i = 1; i <= n; i++) {
    if (a[i].size() <= kB) {
      for (int j : a[i]) {
        auto p = s[j].insert(i).first;
        if (p != s[j].begin()) {
          q[i].push(*--p);
        }
      }
      Update(i);
    } else {
      v.push_back(i);
      for (int j : a[i]) {
        b[j] = i;
      }
      for (int j = 1; j <= n; j++) {
        if (i != j) {
          for (int k : a[j]) {
            if (b[k] == i) {
              d[j].push_back(i);
              j < i ? l[i].push(j) : r[i].push(j);
              break;
            }
          }
        }
      }
    }
  }
}

void Switch(int x) {
  u[x] ^= 1;
  if (u[x]) {
    if (a[x].size() <= kB) {
      for (int j : a[x]) {
        auto p = s[j].lower_bound(x);
        if (p != s[j].end() && a[*p].size() <= kB) {
          q[*p].push(x), Update(*p);
        }
        if (p != s[j].begin()) {
          q[x].push(*--p);
        }
        s[j].insert(x);
      }
      Update(x);
    }
    for (int j : d[x]) {
      x < j ? l[j].push(x) : r[j].push(x);
    }
  } else if (a[x].size() <= kB) {
    for (int j : a[x]) {
      s[j].erase(x);
      auto p = s[j].lower_bound(x);
      if (p != s[j].begin()) {
        auto _p = p--;
        if (_p != s[j].end() && a[*_p].size() <= kB) {
          q[*_p].push(*p), Update(*_p);
        }
      } else if (p != s[j].end() && a[*p].size() <= kB) {
        Update(*p);
      }
    }
    t[x] = 0, Change(1, 1, n, x, 0);
  }
}

bool Exist(int x, int y) {
  if (Ask(1, 1, n, x, y) >= x) {
    return 1;
  }
  for (int j : v) {
    if (u[j]) {
      for (; !l[j].empty() && !u[l[j].top()]; l[j].pop()) {
      }
      for (; !r[j].empty() && !u[r[j].top()]; r[j].pop()) {
      }
      if (!l[j].empty() && l[j].top() >= x && j <= y) {
        return 1;
      } else if (!r[j].empty() && j >= x && r[j].top() <= y) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    u[i] = 1, cin >> x;
    for (int j = 1, y; j <= x; j++) {
      cin >> y, a[i].push_back(y);
    }
  }
  Init();
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      Switch(x);
    } else {
      cin >> y;
      cout << (Exist(x, y) ? "Yes\n" : "No\n");
    }
  }
  return 0;
}
