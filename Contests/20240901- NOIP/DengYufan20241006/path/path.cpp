#include <algorithm>
#include <iostream>
#include <vector>

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *is = ibuf + iL, *it = ibuf + iL;
#define Getchar() ((is == it) ? (it = (is = ibuf) + fread(ibuf, 1, iL, stdin), is == it ? EOF : *is++) : *is++)
template <class T>
inline void Read(T &x) {
  x = 0;
  int f = 0;
  char ch = Getchar();
  for (; !isdigit(ch); f |= ch == '-', ch = Getchar()) {
  }
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = Getchar()) {
  }
  x = (f == 1 ? ~x + 1 : x);
}
template <class T, class... Args>
inline void Read(T &x, Args &...args) { Read(x), Read(args...); }
template <class T>
inline void Readch(T &x) {
  char ch = Getchar();
  for (; !isalpha(ch); ch = Getchar()) {
  }
  x = ch;
}
char out[iL], *iter = out;
#define Flush() fwrite(out, 1, iter - out, stdout), iter = out
template <class T>
inline void Write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter++ = '-', x = ~x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10) {
  }
  for (; l; --l, *iter++ = c[l] + '0') {
  }
  *iter++ = ch;
  Flush();
}
template <class T, class... Args>
inline void Write(T x, Args... args) { Write(x, ' '), Write(args...); }
}  // namespace IO
using namespace IO;
using namespace std;

const int kMaxN = 1e6 + 1, kMaxL = 20;
struct V {
  int d, l, w, f[kMaxL];
  vector<int> e;
} v[kMaxN];
struct L {
  int x, y;
};
struct Q {
  int x, y, o;
};
int n, m, s, t, ans[kMaxN];
vector<L> l;
vector<Q> q;

void CalcD(int f, int x) {
  v[x].d = v[f].d + !!f;
  for (int i : v[x].e) {
    if (i != f) {
      CalcD(x, i);
    }
  }
}

void CalcF(int f, int x) {
  v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      CalcF(x, i);
    }
  }
}

void CalcW(int f, int x, int d, int &w) {
  w = max(w, d);
  for (int i : v[x].e) {
    if (i != f) {
      CalcW(x, i, d + 1, w);
    }
  }
}

void Init() {
  int mx1 = 0, mx2 = 0;
  CalcD(0, 1);
  for (int i = 1; i <= n; i++) {
    if (v[mx1].d < v[i].d) {
      mx1 = i;
    }
  }
  CalcD(0, mx1);
  for (int i = 1; i <= n; i++) {
    v[i].l = v[i].d, v[i].w = -1;
    if (v[mx2].d < v[i].d) {
      mx2 = i;
    }
  }
  CalcD(0, mx2), CalcF(0, mx2);
  for (int i = mx1, f = v[i].f[0]; f != mx2; i = f, f = v[i].f[0]) {
    for (int j : v[f].e) {
      if (j != i && v[j].f[0] == f) {
        CalcW(f, j, 1, v[f].w);
      }
    }
  }
  s = mx2, t = mx1;
}

int Lca(int x, int y) {
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int Dis(int x, int y) { return v[x].d + v[y].d - v[Lca(x, y)].d * 2; }

void Calc() {
  int mx = -n;
  for (int i = 1; i <= n; i++) {
    if (~v[i].w) {
      l.push_back({v[i].w + v[i].d, v[i].w - v[i].d});
    }
  }
  sort(l.begin(), l.end(), [](L i, L j) {
    return i.x > j.x;
  });
  sort(q.begin(), q.end(), [](Q i, Q j) {
    return i.x > j.x;
  });
  for (int i = 0, j = 0; i < q.size(); i++) {
    for (; j < l.size() && l[j].x >= q[i].x; j++) {
      mx = max(mx, l[j].y);
    }
    ans[q[i].o] += mx < q[i].y;
  }
}

int main() {
  freopen("path.in", "r", stdin);
  freopen("path.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Read(n, m);
  for (int i = 1, x, y; i < n; i++) {
    Read(x, y);
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Init();
  for (int i = 1, x, y, k; i <= m; i++) {
    Read(x, y, k);
    if (min(max(v[x].d, v[x].l), max(v[y].d, v[y].l)) < k) {
      ans[i] = -1;
    } else if (Dis(x, y) >= k) {
      ans[i] = 1;
    } else {
      ans[i] = 2;
      if (max(min(v[x].d, v[y].d), min(v[x].l, v[y].l)) < k) {
        int a = Lca(t, x), b = Lca(t, y);
        v[a].d > v[b].d ? swap(a, b), swap(x, y) : void();
        q.push_back({k + v[a].d * 2 - v[x].d, k - v[y].d, i});
      }
    }
  }
  Calc();
  for (int i = 1; i <= m; i++) {
    Write(ans[i]);
  }
  return 0;
}
