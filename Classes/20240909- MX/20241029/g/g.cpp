#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 3e5 + 1, kB = 550, kInf = 1e9;
struct D {
  int l, r, c;
  LL s;
} d[kMaxN * 20];
struct V {
  int minp, minp2, maxs, maxs2;
  int rp, rp2, tp, rs, rs2, ts;
  int tw, c;
} v[kB];
int u, n, m, k, a[kMaxN], p[kMaxN], s[kMaxN], w[kMaxN];
vector<int> bin;

void Init() {
  k = 0, bin.clear();
  for (int i = 0; i < n; i++) {
    w[i] = -1;
  }
  for (int i = 0; i < m; i++) {
    v[i].rp = v[i].rp2 = v[i].tp = 0;
    v[i].rs = v[i].rs2 = v[i].ts = 0;
    v[i].tw = v[i].c = 0;
  }
}

int New() {
  if (bin.empty()) {
    return ++k;
  } else {
    int p = bin.back();
    bin.pop_back();
    return p;
  }
}

void Recovery(int p) {
  if (p) {
    bin.push_back(p), Recovery(d[p].l), Recovery(d[p].r);
  }
}

void Add(int &p, int l, int r, int x) {
  if (!p) {
    p = New(), d[p] = d[0];
  }
  if (l == r) {
    d[p].c++, d[p].s += x;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(d[p].l, l, mid, x);
  } else {
    Add(d[p].r, mid + 1, r, x);
  }
  d[p].c = d[d[p].l].c + d[d[p].r].c;
  d[p].s = d[d[p].l].s + d[d[p].r].s;
}

LL AskS(int p, int l, int r, int _l, int _r) {
  if (!p) {
    return 0;
  } else if (l >= _l && r <= _r) {
    return d[p].s;
  }
  int mid = l + r >> 1;
  LL ans = 0;
  if (mid >= _l) {
    ans += AskS(d[p].l, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += AskS(d[p].r, mid + 1, r, _l, _r);
  }
  return ans;
}

int AskC(int p, int l, int r, int _l, int _r) {
  if (!p) {
    return 0;
  } else if (l >= _l && r <= _r) {
    return d[p].c;
  }
  int mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    ans += AskC(d[p].l, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += AskC(d[p].r, mid + 1, r, _l, _r);
  }
  return ans;
}

int AskW(int x) { return w[x] + v[x / kB].tw; }

void Rebuild(int o) {
  int l = o * kB, r = l + kB;
  Recovery(v[o].rp), Recovery(v[o].rp2);
  Recovery(v[o].rs), Recovery(v[o].rs2);
  v[o].rp = v[o].rp2 = v[o].tp = v[o].rs = v[o].rs2 = v[o].ts = v[o].c = 0;
  v[o].minp = v[o].minp2 = kInf, v[o].maxs = v[o].maxs2 = -kInf;
  for (int i = l; i < r; i++) {
    if (~w[i]) {
      v[o].c++;
      if (v[o].minp > p[i]) {
        v[o].minp2 = v[o].minp, v[o].minp = p[i];
      } else if (v[o].minp < p[i]) {
        v[o].minp2 = min(v[o].minp2, p[i]);
      }
      if (v[o].maxs < s[i]) {
        v[o].maxs2 = v[o].maxs, v[o].maxs = s[i];
      } else if (v[o].maxs > s[i]) {
        v[o].maxs2 = max(v[o].maxs2, s[i]);
      }
    }
  }
  for (int i = l; i < r; i++) {
    Add(p[i] == v[o].minp ? v[o].rp : v[o].rp2, 1, n, AskW(i) - AskW(p[i]));
    Add(s[i] == v[o].maxs ? v[o].rs : v[o].rs2, 1, n, AskW(s[i]) - AskW(i));
  }
}

void CheckMaxP(int o, int x) {  // v[o].tw++
  if (v[o].minp2 <= x) {
    int l = o * kB, r = l + kB;
    for (int i = l; i < r; i++) {
      p[i] = max(p[i], x);
    }
    v[o].tw++, Rebuild(o);
  } else if (v[o].minp < x) {
    v[o].tp += AskW(x) - AskW(v[o].minp) - 1;
    v[o].tw++;
  } else {
    v[o].tw++;
  }
}

void CheckMinS(int o, int x) {
  if (v[o].maxs2 >= x) {
    int l = o * kB, r = l + kB;
    for (int i = l; i < r; i++) {
      s[i] = min(s[i], x);
    }
    Rebuild(o);
  } else if (v[o].maxs > x) {
    v[o].ts += AskW(v[o].maxs) - AskW(x);
  }
}

void Insert(int x) {
  int o = x / kB, l = o * kB, r = l + kB, c = 0;
  for (int i = l; i < x; i++) {
    s[i] = min(s[i], x);
    ~w[i] && ++c && (w[i] += v[o].tw);
  }
  for (int i = x; i < r; i++) {
    p[i] = max(p[i], x);
    ~w[i] && ++w[i] && (w[i] += v[o].tw);
  }
  for (int i = 0; i < o; i++) {
    c += v[i].c;
  }
  p[x] = -kInf, s[x] = kInf, w[x] = c, v[o].tw = 0;
  Rebuild(o);
  for (int i = 0; i < o; i++) {
    CheckMinS(i, x);
  }
  for (int i = o + 1; i < m; i++) {
    CheckMaxP(i, x);
  }
}

LL Query(int x) {
  LL ans = -n - x + 1;
  for (int i = 0; i < m; i++) {
    ans += AskS(v[i].rp, 1, n, 1, x + v[i].tp);
    ans -= 1LL * v[i].tp * AskC(v[i].rp, 1, n, 1, x + v[i].tp);
    x + v[i].tp < n ? ans += 1LL * x * AskC(v[i].rp, 1, n, x + v[i].tp + 1, n) : 0;
    ans += AskS(v[i].rp2, 1, n, 1, x);
    x < n ? ans += 1LL * x * AskC(v[i].rp2, 1, n, x + 1, n) : 0;

    ans += AskS(v[i].rs, 1, n, 1, x + v[i].ts);
    ans -= 1LL * v[i].ts * AskC(v[i].rs, 1, n, 1, x + v[i].ts);
    x + v[i].ts < n ? ans += 1LL * x * AskC(v[i].rs, 1, n, x + v[i].ts + 1, n) : 0;
    ans += AskS(v[i].rs2, 1, n, 1, x);
    x < n ? ans += 1LL * x * AskC(v[i].rs2, 1, n, x + 1, n) : 0;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    cin >> n, m = n / kB;
    for (int i = 0, x; i < n; i++) {
      cin >> x, a[x - 1] = i;
    }
    Init();
    for (int i = 0, x; i < n; i++) {
      cin >> x, Insert(a[i]);
      for (int j = 0, y; j < x; j++) {
        cin >> y, cout << Query(y) << '\n';
      }
    }
  }
  return 0;
}
