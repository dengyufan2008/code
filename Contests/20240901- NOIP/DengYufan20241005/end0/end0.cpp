#include <fstream>
#define LL long long

using namespace std;

ifstream cin("end0.in");
ofstream cout("end0.out");

const LL kMaxN = 2e5 + 2, kInf = 1e18;
struct W {
  LL w;
  int l, r;
  bool operator<(const W &x) const {
    return w < x.w;
  }
  W operator+(const W &x) const {
    return {w + x.w, l, x.r};
  }
  W operator-(const W &x) const {
    return {w - x.w, x.r + 1, r};
  }
};
struct V {
  W s, w0, w1, ans0, ans1;
  bool t;
} v[kMaxN << 2];
int n, m;
LL a[kMaxN], ans[kMaxN];

void Pushup(int p) {
  v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  v[p].w0 = min(v[p << 1].w0, v[p << 1].s + v[p << 1 | 1].w0);
  v[p].w1 = max(v[p << 1].w1, v[p << 1].s + v[p << 1 | 1].w1);
  v[p].ans0 = min(v[p << 1].ans0, v[p << 1 | 1].ans0);
  v[p].ans0 = min(v[p].ans0, v[p << 1].s + v[p << 1 | 1].w0 - v[p << 1].w1);
  v[p].ans1 = max(v[p << 1].ans1, v[p << 1 | 1].ans1);
  v[p].ans1 = max(v[p].ans1, v[p << 1].s + v[p << 1 | 1].w1 - v[p << 1].w0);
}

void Init(int p, int l, int r) {
  if (l == r) {
    v[p].s = v[p].w0 = v[p].w1 = v[p].ans0 = v[p].ans1 = {a[l], l, l};
    v[p].t = 0;
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  Pushup(p);
}

void Tag(int p) {
  v[p].t ^= 1, v[p].s.w = -v[p].s.w;
  swap(v[p].w0, v[p].w1);
  v[p].w0.w = -v[p].w0.w;
  v[p].w1.w = -v[p].w1.w;
  swap(v[p].ans0, v[p].ans1);
  v[p].ans0.w = -v[p].ans0.w;
  v[p].ans1.w = -v[p].ans1.w;
}

void Pushdown(int p) {
  if (v[p].t) {
    Tag(p << 1), Tag(p << 1 | 1), v[p].t = 0;
  }
}

void Rev(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return Tag(p);
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Rev(p << 1, l, mid, _l, _r);
  }
  if (mid < _r) {
    Rev(p << 1 | 1, mid + 1, r, _l, _r);
  }
  Pushup(p);
}

LL Calc() {
  W t = v[1].ans1;
  Rev(1, 0, n, t.l, t.r);
  return t.w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, o; i <= n; i++) {
    cin >> o >> a[i];
    if (!o) {
      ans[0] += a[i];
      a[i] = -a[i];
    }
  }
  a[++n] = kInf, Init(1, 0, n), ans[0] += Calc() - kInf;
  for (int i = 1; i <= n; i++) {
    ans[i] = ans[i - 1] + Calc();
    if (ans[i] <= ans[i - 1]) {
      for (int j = i; j <= n; j++) {
        ans[j] = ans[i - 1];
      }
      break;
    }
  }
  cin >> m;
  for (int i = 1, x; i <= m; i++) {
    cin >> x, cout << ans[x] << '\n';
  }
  return 0;
}
