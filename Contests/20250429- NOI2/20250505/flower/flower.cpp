#include <fstream>

using namespace std;

ifstream cin("flower.in");
ofstream cout("flower.out");

const int kMaxN = 2e5 + 1, kB = 600;
struct Q {
  int o, l, r, x, y;
} q[kMaxN];
int n, m, a[kMaxN], c[kMaxN], o[kMaxN], ans[kMaxN];

void Calc0(int l, int r) {
  struct E {
    int p, x;
  };
  struct V {
    int p, x, o;
  };
  static int d[kMaxN], p[kMaxN], w[kMaxN];
  static int ec, vc, et[kB << 1 | 1], vt[kB << 1 | 1];
  static E e[kMaxN];
  static V v[kB + 1];
  fill(&d[1], &d[n] + 1, 0);
  fill(&w[0], &w[n] + 1, 0);
  fill(&et[0], &et[o[n]] + 1, 0);
  fill(&vt[1], &vt[o[n]] + 1, 0);
  ec = vc = 0;
  for (int i = 1; i <= n; i++) {
    if (c[a[i]] == c[a[i] - 1]) {
      p[i] = d[a[i]], d[a[i]] = i;
      e[++ec] = {et[o[p[i]]], o[i]}, et[o[p[i]]] = ec;
    }
  }
  for (int i = l; i <= r; i++) {
    if (q[i].o == 2) {
      v[++vc] = {vt[o[q[i].l]], o[q[i].r], i}, vt[o[q[i].l]] = vc;
    }
  }
  for (int i = 1; i <= o[n]; i++) {
    for (int j = et[i - 1]; j; j = e[j].p) {
      w[e[j].x]++;
    }
    for (int j = vt[i]; j; j = v[j].p) {
      for (int k = i; k <= v[j].x; k++) {
        ans[v[j].o] += w[k];
      }
    }
  }
}

void Calc1(int l, int r) {
  static int s[kB << 1 | 1][kB << 1 | 1];
  static bool w[kB << 1 | 1][kB << 1 | 1];
  for (int i = 1; i <= c[n]; i++) {
    fill(&w[i][1], &w[i][o[n]] + 1, 0);
  }
  for (int i = 1; i <= n; i++) {
    if (c[a[i]] > c[a[i] - 1]) {
      w[c[a[i]]][o[i]] = 1;
    }
  }
  for (int i = 1; i <= c[n]; i++) {
    for (int j = 1; j <= o[n]; j++) {
      s[i][j] = s[i][j - 1] + w[i][j];
    }
  }
  for (int i = l; i <= r; i++) {
    int ll = o[q[i].l], rr = o[q[i].r];
    if (q[i].o == 1) {
      int x = c[q[i].x], y = c[q[i].y];
      for (int j = ll; j <= rr; j++) {
        w[y][j] |= w[x][j], w[x][j] = 0;
      }
      for (int j = ll; j <= o[n]; j++) {
        s[x][j] = s[x][j - 1] + w[x][j];
        s[y][j] = s[y][j - 1] + w[y][j];
      }
    } else {
      for (int j = 1; j <= c[n]; j++) {
        ans[i] += s[j][ll - 1] < s[j][rr];
      }
    }
  }
}

void Forward(int l, int r) {
  static int t[kB << 1 | 1][kB << 1 | 1];
  for (int i = 1, _i = 0; i <= n; i++) {
    if (c[i] > c[i - 1]) {
      _i++;
      for (int j = 0; j <= o[n]; j++) {
        t[_i][j] = i;
      }
    }
  }
  for (int i = r; i >= l; i--) {
    if (q[i].o == 1) {
      int ll = o[q[i].l], rr = o[q[i].r];
      int x = c[q[i].x], y = c[q[i].y];
      for (int j = ll; j <= rr; j++) {
        t[x][j] = t[y][j];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (c[a[i]] > c[a[i] - 1]) {
      a[i] = t[c[a[i]]][o[i]];
    }
  }
}

void Calc(int l, int r) {
  bool u = 0;
  fill(&c[1], &c[n] + 1, 0);
  for (int i = l; i <= r; i++) {
    if (q[i].o == 1) {
      c[q[i].x] = c[q[i].y] = 1;
    } else {
      u = 1;
    }
  }
  fill(&o[1], &o[n] + 1, 0);
  for (int i = l; i <= r; i++) {
    o[q[i].l] = o[q[i].r + 1] = 1;
  }
  for (int i = 1; i <= n; i++) {
    c[i] += c[i - 1];
    o[i] += o[i - 1];
  }
  if (u) {
    Calc0(l, r), Calc1(l, r);
  }
  Forward(l, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].o >> q[i].l >> q[i].r;
    if (q[i].o == 1) {
      cin >> q[i].x >> q[i].y;
      if (q[i].x == q[i].y) {
        q[i] = q[0], i--, m--;
      }
    }
  }
  for (int i = 1; i <= m; i += kB) {
    Calc(i, min(i + kB - 1, m));
  }
  for (int i = 1; i <= m; i++) {
    if (q[i].o == 2) {
      cout << ans[i] << '\n';
    }
  }
  return 0;
}
