#include <algorithm>
#include <fstream>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("s.in");
ofstream cout("s.out");

const LL kMaxN = 2e5 + 1, kMaxL = 18, kInf = 1e18;
struct P {
  int x, y, o;
} p[kMaxN];
struct A {
  int l, r, o;
  void operator+=(A a) {
    int w = (r < a.l) - (l > a.r);
    if ((o == w || l == r) && (a.o == w || a.l == a.r)) {
      o = w;
    } else {
      o = 0;
    }
    l = min(l, a.l), r = max(r, a.r);
  }
  bool operator&(A a) {
    return l == a.r + 1 || a.l == r + 1;
  }
} a[kMaxL][kMaxN];
int n;
unordered_map<LL, LL> s;

void Init() {
  int h[kMaxN] = {};
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].x >> p[i].y;
    p[i].o = h[i] = i;
  }
  sort(p + 1, p + n + 1, [](P i, P j) {
    return i.x < j.x;
  });
  sort(h + 1, h + n + 1, [](int i, int j) {
    return p[i].y < p[j].y;
  });
  for (int i = 1; i <= n; i++) {
    a[0][h[i]] = {i, i};
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = a[i - 1][j];
      if (j + (1 << i - 1) <= n) {
        a[i][j] += a[i - 1][j + (1 << i - 1)];
      }
    }
  }
}

int Dis(int x, int y) {
  return abs(p[x].x - p[y].x) + abs(p[x].y - p[y].y);
}

LL R(int l, int r, bool o) {
  return 2LL * n * (l - 1) + 2LL * (r - 1) + o;
}

A Ask(int l, int r) {
  A t = a[0][l];
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (l + (1 << i) <= r) {
      t += a[i][l + 1], l += 1 << i;
    }
  }
  return t;
}

int FindL(int x, A t) {
  int l = 1, r = x - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    A _t = Ask(mid, x - 1);
    if (_t.r - _t.l == x - mid - 1) {
      if ((_t.o == 1 || _t.l == _t.r) && t.l - 1 == _t.r) {
        r = mid - 1;
      } else if ((_t.o == -1 || _t.l == _t.r) && t.r + 1 == _t.l) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    } else {
      l = mid + 1;
    }
  }
  return l;
}

int FindR(int x, A t) {
  int l = x + 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    A _t = Ask(x + 1, mid);
    if (_t.r - _t.l == mid - x - 1) {
      if ((_t.o == 1 || _t.l == _t.r) && t.r + 1 == _t.l) {
        l = mid + 1;
      } else if ((_t.o == -1 || _t.l == _t.r) && t.l - 1 == _t.r) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    } else {
      r = mid - 1;
    }
  }
  return r;
}

LL Calc(int l, int r, bool o) {
  if (s.count(R(l, r, o))) {
    return s[R(l, r, o)];
  }
  A t = Ask(l, r);
  int _l = FindL(l, t), _r = FindR(r, t);
  LL ans = kInf;
  if (_l < l) {
    ans = min(ans, Calc(_l, r, 0) + Dis(_l, o ? r : l));
  }
  if (_r > r) {
    ans = min(ans, Calc(l, _r, 1) + Dis(_r, o ? r : l));
  }
  if (_l == l && _r == r) {
    ans = l - r;
  }
  return s[R(l, r, o)] = ans;
}

void Ans() {
  LL ans[kMaxN] = {};
  for (int i = 1; i <= n; i++) {
    ans[p[i].o] = Calc(i, i, 0);
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Ans();
  return 0;
}
