// O((n+q) \log n)
#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("occur.in");
ofstream cout("occur.out");

const int kMaxN = 2e5 + 1, kMaxL = 18;
int n, m, lg[kMaxN];
string s;

struct SA {
  int a[kMaxN], r[kMaxN], l[kMaxL][kMaxN];

  void CalcR() {
    int b[kMaxN] = {}, c[kMaxN] = {};
    for (int i = 1; i <= n; i++) {
      a[i] = i;
    }
    sort(a + 1, a + n + 1, [](int i, int j) {
      return s[i] < s[j];
    });
    for (int i = 1; i <= n; i++) {
      r[a[i]] = r[a[i - 1]] + (s[a[i]] != s[a[i - 1]]);
    }
    for (int h = 1; h < n; h <<= 1) {
      for (int i = 1; i <= h; i++) {
        b[i] = n - h + i;
      }
      for (int i = 1, j = h; i <= n; i++) {
        if (a[i] > h) {
          b[++j] = a[i] - h;
        }
      }
      fill(&c[1], &c[n] + 1, 0);
      for (int i = 1; i <= n; i++) {
        c[r[i]]++;
      }
      for (int i = 1; i <= n; i++) {
        c[i] += c[i - 1];
      }
      for (int i = n; i >= 1; i--) {
        a[c[r[b[i]]]--] = b[i];
      }
      for (int i = 1; i <= n; i++) {
        b[a[i]] = b[a[i - 1]];
        if (r[a[i]] != r[a[i - 1]]) {
          b[a[i]]++;
        } else if (r[a[i] + h] != r[a[i - 1] + h]) {
          b[a[i]]++;
        }
      }
      copy(&b[1], &b[n] + 1, &r[1]);
    }
  }

  void CalcL() {
    for (int i = 1, _i; i <= n; i++) {
      if (r[i] < n) {
        _i = a[r[i] + 1], l[0][r[i]] = max(l[0][r[i - 1]] - 1, 0);
        for (int &j = l[0][r[i]]; s[j + i] == s[j + _i]; j++) {
        }
      }
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        l[i][j] = l[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          l[i][j] = min(l[i][j], l[i - 1][j + (1 << i - 1)]);
        }
      }
    }
  }

  void Init() { CalcR(), CalcL(); }

  int Lcp(int x, int y) {
    x = r[x], y = r[y];
    if (x == y) {
      return n - a[x] + 1;
    } else if (x > y) {
      swap(x, y);
    }
    int o = lg[y - x + 1];
    return min(l[o][x], l[o][y - (1 << o) + 1]);
  }
} sa;

struct SAM {
  struct V {
    int f, l, c, mx, r, d, e[26];
    LL w;
  } v[kMaxN << 1];
  struct D {
    int x;
    LL w, c;
  };
  struct H {
    int l, r;
    vector<D> d;
  } h[kMaxN << 1];
  int k;

  void Build() {
    int r = k = 1;
    for (int i = 1; i <= n; i++) {
      int x = s[i] - 'a', p = r;
      v[++k].l = v[p].l + 1;
      for (; p && !v[p].e[x]; p = v[p].f) {
        v[p].e[x] = k;
      }
      if (p) {
        int q = v[p].e[x];
        if (v[p].l + 1 == v[q].l) {
          v[k].f = q, r = k;
        } else {
          v[++k] = v[q], v[k].l = v[p].l + 1;
          for (; p && v[p].e[x] == q; p = v[p].f) {
            v[p].e[x] = k;
          }
          v[k - 1].f = v[q].f = k, r = k - 1;
        }
      } else {
        v[k].f = 1, r = k;
      }
    }
  }

  void Calc() {
    int l[kMaxN << 1] = {};
    for (int i = 1, p = 1; i <= n; i++) {
      p = v[p].e[s[i] - 'a'], v[p].c = 1, v[p].mx = i;
    }
    for (int i = 1; i <= k; i++) {
      l[i] = i;
    }
    sort(l + 1, l + k + 1, [&](int i, int j) {
      return v[i].l < v[j].l;
    });
    for (int i = k; i >= 2; i--) {
      int x = l[i];
      v[v[x].f].c += v[x].c;
      v[v[x].f].mx = max(v[v[x].f].mx, v[x].mx);
    }
    for (int i = 2; i <= k; i++) {
      int x = l[i];
      v[x].w = v[v[x].f].w;
      v[x].w += 1LL * v[x].c * (v[x].l - v[v[x].f].l);
    }
    for (int i = 1; i <= k; i++) {
      int x = l[i];
      v[x].w -= 1LL * v[x].c * v[x].l;
    }
  }

  void Div() {
    LL in[kMaxN << 1] = {}, out[kMaxN << 1] = {};
    int pre[kMaxN << 1] = {}, suf[kMaxN << 1] = {};
    for (int i = 1; i <= k; i++) {
      in[i]++;
      for (int j = 0; j < 26; j++) {
        v[i].e[j] && (in[v[i].e[j]] += in[i]);
      }
    }
    for (int i = k; i >= 1; i--) {
      out[i]++;
      for (int j = 0; j < 26; j++) {
        v[i].e[j] && (out[i] += out[v[i].e[j]]);
      }
    }
    for (int i = 1; i <= k; i++) {
      for (int j = 0; j < 26; j++) {
        int x = v[i].e[j];
        if (x) {
          in[pre[x]] < in[i] && (pre[x] = i);
          out[suf[i]] < out[x] && (suf[i] = x);
        }
      }
    }
    for (int i = 1; i <= k; i++) {
      int s;
      if (suf[pre[i]] != i) {
        v[i].r = i, v[i].d = 0, s = 1;
        h[i].d.push_back({i, v[i].w, v[i].c});
        for (int x = i, y = suf[i]; pre[y] == x;) {
          D d = h[i].d.back();
          h[i].d.push_back({y, d.w + v[y].w + 1LL * v[y].c * s, d.c + v[y].c});
          v[y].r = i, v[y].d = s, x = y, y = suf[y], s++;
        }
        int x = h[i].d.back().x;
        h[i].l = v[x].mx - s + 2, h[i].r = v[x].mx;
      }
    }
  }

  void Init() { Build(), Calc(), Div(); }
} sam;

LL Ask(int l, int r) {
  if (l > r) {
    return 0;
  }
  LL ans = 0;
  for (int x = l, p = 1, q; x <= r;) {
    q = sam.v[p].r;
    SAM::H &h = sam.h[q];
    int d = sam.v[p].d;
    int mn = min(r - x, h.r - h.l - d + 1);
    int t = min(sa.Lcp(x, h.l + d), mn);
    SAM::D &d0 = h.d[d], &d1 = h.d[d + t];
    ans += (d1.w - d0.w) + 1LL * (d1.c - d0.c) * (x - l - d);
    x += t, p = sam.v[d1.x].e[s[x] - 'a'];
    x++, ans += sam.v[p].w + 1LL * (x - l) * sam.v[p].c;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n >> s >> m, s = '~' + s + '~';
  sa.Init(), sam.Init();
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cout << Ask(x, y) << '\n';
  }
  return 0;
}
