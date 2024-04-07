#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMod = 998244353, kInf = 1e9;
struct V {
  int mx, mxt, mn, mnt, d, dt;
  int mxlw, mxlc, mnlw, mnlc, w, c;
  LL hisw, hisc, hist;
  LL prew, prec, pretw, pretc, prett;
  LL answ, ansc;
} v[kMaxN << 2];
int n, m, a[kMaxN];
LL ans;

void Init(int p, int l, int r) {
  v[p].mn = n + 1;
  v[p].mxlw = l, v[p].mxlc = 1;
  v[p].mnlw = l - n - 1, v[p].mnlc = 1;
  v[p].w = l - n - 1, v[p].c = 1;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
}

void TagD(int p, int dt) {
  v[p].d -= dt, v[p].dt += dt, v[p].w -= dt;
}

void TagMax(int p, int l, int mxt) {
  v[p].mx = mxt, v[p].mxt = mxt;
  v[p].mxlw = l + mxt, v[p].mxlc = 1;
  v[p].w = mxt + v[p].mnlw, v[p].c = v[p].mnlc;
}

void TagMin(int p, int l, int mnt) {
  v[p].mn = mnt, v[p].mnt = mnt;
  v[p].mnlw = l - mnt, v[p].mnlc = 1;
  v[p].w = mnt + v[p].mxlw, v[p].c = v[p].mxlc;
}

void TagHis(int p, int hist) {  // CHICK
  ;
}

void TagPre(int p, int l, int r, int pretw, int pretc, int prett) {  // CHICK
  ;
}

void Pushdown(int p, int l, int r) {  // CHICK
  ;
}

void Pushup(int p, int l, int r) {  // CHICK
  ;
}

int FindMax(int p, int l, int r, int o, int x) {
  if (l == r) {
    return l;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (v[p << 1].mx < x || mid >= o) {
    return FindMax(p << 1, l, mid, o, x);
  }
  return FindMax(p << 1 | 1, mid + 1, r, o, x);
}

void Max(int p, int l, int r, int _l, int _r, int x) {
  if (l >= _l && r <= _r) {
    return TagMax(p, l, x);
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Max(p << 1, l, mid, _l, _r, x);
  }
  if (mid < _r) {
    Max(p << 1 | 1, mid + 1, r, _l, _r, x);
  }
  Pushup(p, l, r);
}

int FindMin(int p, int l, int r, int o, int x) {
  if (l == r) {
    return l;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (v[p << 1].mn > x || mid >= o) {
    return FindMin(p << 1, l, mid, o, x);
  }
  return FindMin(p << 1 | 1, mid + 1, r, o, x);
}

void Min(int p, int l, int r, int _l, int _r, int x) {
  if (l >= _l && r <= _r) {
    return TagMin(p, l, x);
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Min(p << 1, l, mid, _l, _r, x);
  }
  if (mid < _r) {
    Min(p << 1 | 1, mid + 1, r, _l, _r, x);
  }
  Pushup(p, l, r);
}

void Pre(int p, int l, int r, int o, LL w = n + 1, LL c = 0) {  // CHICK
  if (l == r) {
    v[p].prew = w, v[p].prec = c;
    return;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= o) {
    Pre(p << 1, l, mid, o, w, c);
  } else {
    TagPre(p << 1, l, mid, w, c, 0);
    Pre(p << 1 | 1, mid + 1, r, o, w, c);
  }
  Pushup(p, l, r);
}

pair<LL, LL> Ask(int p, int l, int r, int o) {  // CHICK
  ;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Init(1, 1, n);
  for (int i = 1; i <= n; i++) {
    if (a[i - 1] < a[i]) {
      int p = FindMax(1, 1, n, i, a[i]);
      Max(1, 1, n, p, i, a[i]);
    }
    if (i == 1 || a[i - 1] > a[i]) {
      int p = FindMin(1, 1, n, i, a[i]);
      Min(1, 1, n, p, i, a[i]);
    }
    TagD(1, 1);
    if (i > m) {
      pair<LL, LL> t = Ask(1, 1, n, i - m);
      !t.second && (ans = (ans + t.first) % kMod);
    }
    TagHis(1, 1);
    if (i > m) {
      Pre(1, 1, n, 1, i - m);
    }
  }
  cout << ans << '\n';
  return 0;
}
