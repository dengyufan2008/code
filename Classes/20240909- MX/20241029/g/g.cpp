#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 3e5 + 1, kB = 550, kInf = 1e9;
struct D {
  int t;
  pair<int, LL> d[kB];
  void Clear() { t = 0; }
  void Insert(int x) { d[t++] = {x, 0}; }
};
struct V {
  int minp, minp2, chkp, maxs, maxs2, chks;
  int tw, c;
  int p[kB], s[kB], w[kB];
  int tp, ts;
  D rp, rp2, rs, rs2;
} v[kMaxN / kB + 1];
int u, n, m, a[kMaxN];

void Init() {
  for (int i = 0; i < m; i++) {
    v[i].tw = v[i].c = v[i].tp = v[i].ts = 0;
    v[i].rp.Clear(), v[i].rp2.Clear();
    v[i].rs.Clear(), v[i].rs2.Clear();
    for (int j = 0; j < kB; j++) {
      v[i].w[j] = -1;
    }
  }
}

void Update(int o) {
  v[o].tp = v[o].ts = 0;
  v[o].rp.Clear(), v[o].rp2.Clear();
  v[o].rs.Clear(), v[o].rs2.Clear();
  for (int i = 0; i < kB; i++) {
    if (v[o].p[i] == v[o].minp) {
      v[o].p[i] = v[o].chkp;
    }
    if (v[o].s[i] == v[o].maxs) {
      v[o].s[i] = v[o].chks;
    }
  }
}

void CalcPS(int o) {
  v[o].minp = v[o].minp2 = kInf, v[o].maxs = v[o].maxs2 = -kInf, v[o].c = 0;
  for (int i = 0; i < kB; i++) {
    if (~v[o].w[i]) {
      v[o].c++;
      if (v[o].minp > v[o].p[i]) {
        v[o].minp2 = v[o].minp, v[o].minp = v[o].p[i];
      } else if (v[o].minp < v[o].p[i]) {
        v[o].minp2 = min(v[o].minp2, v[o].p[i]);
      }
      if (v[o].maxs < v[o].s[i]) {
        v[o].maxs2 = v[o].maxs, v[o].maxs = v[o].s[i];
      } else if (v[o].maxs > v[o].s[i]) {
        v[o].maxs2 = max(v[o].maxs2, v[o].s[i]);
      }
    }
  }
  v[o].chkp = v[o].minp, v[o].chks = v[o].maxs;
}

int AskW(int x) {
  int o = x / kB;
  return v[o].w[x - o * kB] + v[o].tw;
}

int AskW(int o, int x) { return v[o].w[x] + v[o].tw; }

void Calc(D &d) {
  d.d[0].second = d.d[0].first;
  for (int i = 1; i < d.t; i++) {
    d.d[i].second = d.d[i - 1].second + d.d[i].first;
  }
}

void CalcR(int o) {
  for (int i = 0; i < kB; i++) {
    if (~v[o].w[i]) {
      if (v[o].p[i] == v[o].minp) {
        v[o].rp.Insert(v[o].minp == -kInf ? n : AskW(o, i) - AskW(v[o].minp));
      } else {
        v[o].rp2.Insert(AskW(o, i) - AskW(v[o].p[i]));
      }
      if (v[o].s[i] == v[o].maxs) {
        v[o].rs.Insert(v[o].maxs == kInf ? n : AskW(v[o].maxs) - AskW(o, i));
      } else {
        v[o].rs2.Insert(AskW(v[o].s[i]) - AskW(o, i));
      }
    }
  }
  reverse(v[o].rs.d, v[o].rs.d + v[o].rs.t);
  sort(v[o].rp2.d, v[o].rp2.d + v[o].rp2.t);
  sort(v[o].rs2.d, v[o].rs2.d + v[o].rs2.t);
  Calc(v[o].rp), Calc(v[o].rp2), Calc(v[o].rs), Calc(v[o].rs2);
}

void Rebuild(int o) { Update(o), CalcPS(o), CalcR(o); }

void CheckMaxP(int o, int x) {
  if (v[o].chkp == -kInf || v[o].minp2 <= x) {
    int l = o * kB, r = min(l + kB, n);
    for (int i = 0; i < kB; i++) {
      v[o].p[i] = max(v[o].p[i], x);
    }
    Rebuild(o);
  } else if (v[o].chkp < x) {
    v[o].tp += AskW(x) - AskW(v[o].chkp) - 1;
    v[o].chkp = x;
  }
}

void CheckMinS(int o, int x) {
  if (v[o].chks == kInf || v[o].maxs2 >= x) {
    int l = o * kB, r = min(l + kB, n);
    for (int i = 0; i < kB; i++) {
      v[o].s[i] = min(v[o].s[i], x);
    }
    Rebuild(o);
  } else if (v[o].chks > x) {
    v[o].ts += AskW(v[o].chks) - AskW(x) - 1;
    v[o].chks = x;
  }
}

void Insert(int x) {
  int o = x / kB, y = x - o * kB, c = 0;
  for (int i = 0; i < y; i++) {
    v[o].s[i] = min(v[o].s[i], x);
    ~v[o].w[i] && ++c && (v[o].w[i] += v[o].tw);
  }
  for (int i = y; i < kB; i++) {
    v[o].p[i] = max(v[o].p[i], x);
    ~v[o].w[i] && ++v[o].w[i] && (v[o].w[i] += v[o].tw);
  }
  for (int i = 0; i < o; i++) {
    c += v[i].c;
  }
  v[o].p[y] = -kInf, v[o].s[y] = kInf, v[o].w[y] = c, v[o].tw = 0;
  for (int i = o + 1; i < m; i++) {
    v[i].tw++;
  }
  Rebuild(o);
  for (int i = 0; i < o; i++) {
    CheckMinS(i, x);
  }
  for (int i = o + 1; i < m; i++) {
    CheckMaxP(i, x);
  }
}

LL AskS(D &d, int x) {
  int p = lower_bound(d.d, d.d + d.t, make_pair(x + 1, 0LL)) - d.d;
  return p ? d.d[p - 1].second : 0;
}

int AskC(D &d, int x) {
  return lower_bound(d.d, d.d + d.t, make_pair(x + 1, 0LL)) - d.d;
}

LL Query(int x) {
  LL ans = 0;
  for (int i = 0; i < m; i++) {
    ans += AskS(v[i].rp, x + v[i].tp);
    ans -= 1LL * (v[i].tp + x) * AskC(v[i].rp, x + v[i].tp);
    ans += AskS(v[i].rp2, x);
    ans += 1LL * x * (v[i].rp.t + v[i].rp2.t - AskC(v[i].rp2, x));

    ans += AskS(v[i].rs, x + v[i].ts);
    ans -= 1LL * (v[i].ts + x) * AskC(v[i].rs, x + v[i].ts);
    ans += AskS(v[i].rs2, x);
    ans += 1LL * x * (v[i].rs.t + v[i].rs2.t - AskC(v[i].rs2, x));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    cin >> n, m = (n - 1) / kB + 1;
    for (int i = 0, x; i < n; i++) {
      cin >> x, a[x - 1] = i;
    }
    Init();
    for (int i = 0, x; i < n; i++) {
      cin >> x, Insert(a[i]);
      for (int j = 0, y; j < x; j++) {
        cin >> y, cout << Query(y) - i - y << '\n';
      }
    }
  }
  return 0;
}
