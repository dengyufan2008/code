#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e6 + 1;
struct E {
  int p, d;
} e[kMaxN << 1];
struct V {
  int s, d, l, et;
  int t, p;
  bool b;
} v[kMaxN];
int n, s, r, ans[kMaxN];

void CalcT() {
  static vector<int> q[kMaxN];
  for (int i = 1; i <= n; i++) {
    q[v[i].t].push_back(i);
  }
  for (int i = n; i >= 1; i--) {
    for (int x : q[i]) {
      if (v[x].t > i) {
        continue;
      }
      for (int j = v[x].et; j; j = e[j].p) {
        int y = e[j].d;
        if (v[y].t < v[x].t - 1) {
          v[y].t = v[x].t - 1, q[v[y].t].push_back(y);
        }
      }
    }
  }
}

void CalcR(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f && !v[e[i].d].b) {
      CalcR(x, e[i].d), v[x].s += v[e[i].d].s;
      mx = max(mx, v[e[i].d].s);
    }
  }
  if (max(mx, s - v[x].s) << 1 <= s) {
    r = x;
  }
}

void CalcP(int f, int x, int *d) {
  v[x].l = 0;
  int _d = d[v[x].d + v[x].t];
  if (!_d || v[_d].d > v[x].d) {
    d[v[x].d + v[x].t] = x;
  }
  if (d[v[x].d] && (!d[v[x].d + 1] || v[d[v[x].d]].d < v[d[v[x].d + 1]].d)) {
    v[x].p = d[v[x].d];
  } else {
    v[x].p = d[v[x].d + 1];
  }
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f && !v[e[i].d].b) {
      v[e[i].d].d = v[x].d + 1;
      CalcP(x, e[i].d, d);
      v[x].l = max(v[x].l, v[e[i].d].l);
    }
  }
  v[x].l++, d[v[x].d + v[x].t] = _d;
}

void CalcC(int f, int x, int lim, int *c1, int *c2) {
  c1[v[x].d]++;
  if (v[x].d > v[r].t && v[v[x].p].t >= v[v[x].p].d) {
    c2[min(v[v[x].p].t - v[v[x].p].d, lim)]++;
  }
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f && !v[e[i].d].b) {
      CalcC(x, e[i].d, lim, c1, c2);
    }
  }
}

void CalcAns(int f, int x, int w, int lim, int *c1, int *c2) {
  if (v[x].d <= v[r].t) {
    ans[x] += w * (c1[min(v[r].t, lim)] + c2[v[x].d]);
  } else if (v[v[x].p].t >= v[v[x].p].d) {
    ans[x] += w * c1[min(v[v[x].p].t - v[v[x].p].d, lim)];
  }
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f && !v[e[i].d].b) {
      CalcAns(x, e[i].d, w, lim, c1, c2);
    }
  }
}

void Divide() {
  static int c1[kMaxN], c2[kMaxN], d[kMaxN << 1];
  int x = r, _s = s;
  v[x].b = 1, v[x].d = 0, CalcP(0, x, d);
  CalcC(0, x, v[x].l - 1, c1, c2);
  for (int i = 1; i < v[x].l; i++) {
    c1[i] += c1[i - 1];
  }
  for (int i = v[x].l - 2; i >= 0; i--) {
    c2[i] += c2[i + 1];
  }
  CalcAns(0, x, 1, v[x].l - 1, c1, c2);
  for (int i = 0; i < v[x].l; i++) {
    c1[i] = c2[i] = 0;
  }
  for (int i = v[x].et; i; i = e[i].p) {
    int y = e[i].d;
    if (!v[y].b) {
      CalcC(0, y, v[y].l, c1, c2);
      for (int j = 1; j <= v[y].l; j++) {
        c1[j] += c1[j - 1];
      }
      for (int j = v[y].l - 1; j >= 0; j--) {
        c2[j] += c2[j + 1];
      }
      CalcAns(0, y, -1, v[y].l, c1, c2);
      for (int j = 0; j <= v[y].l; j++) {
        c1[j] = c2[j] = 0;
      }
    }
  }
  for (int i = v[x].et; i; i = e[i].p) {
    int y = e[i].d;
    if (!v[y].b) {
      if (v[y].s > v[x].s) {
        s = _s - v[x].s;
      } else {
        s = v[y].s;
      }
      CalcR(0, y), Divide();
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].t;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    e[i << 1] = {v[x].et, y}, v[x].et = i << 1;
    e[i << 1 | 1] = {v[y].et, x}, v[y].et = i << 1 | 1;
  }
  CalcT(), s = n, CalcR(0, 1), Divide();
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
