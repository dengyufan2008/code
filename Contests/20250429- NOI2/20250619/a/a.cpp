#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 1e5 + 1, kInf = 1e18;
int n, m, p, a[kMaxN];
LL s, w[kMaxN];
bool b[kMaxN];

class Seg {  // 写完才意识到可以颜色段均摊
  struct V {
    LL w;
    bool t;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = {w[l], 0};
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p].w = min(v[p << 1].w, v[p << 1 | 1].w);
    v[p].t = 0;
  }

  void Tag(int p) {
    v[p].w = kInf, v[p].t = 1;
  }

  void Pushdown(int p) {
    if (v[p].t) {
      Tag(p << 1), Tag(p << 1 | 1), v[p].t = 0;
    }
  }

  void Change(int p, int l, int r, int x, LL y) {
    if (l == r) {
      v[p].w = y + w[l];
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    v[p].w = min(v[p << 1].w, v[p << 1 | 1].w);
  }

  LL Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      LL ans = v[p].w;
      return Tag(p), ans;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    LL ans = kInf;
    if (mid >= _l) {
      ans = min(ans, Ask(p << 1, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = min(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r));
    }
    v[p].w = min(v[p << 1].w, v[p << 1 | 1].w);
    return ans;
  }

  LL Output(int p, int l, int r) {
    if (l == r) {
      return v[p].w - w[l];
    }
    Pushdown(p);
    int mid = l + r >> 1;
    LL ans = kInf;
    ans = min(ans, Output(p << 1, l, mid));
    ans = min(ans, Output(p << 1 | 1, mid + 1, r));
    return ans;
  }

 public:
  void Init() { Init(1, 0, m); }
  LL Ask(int l, int r) { return Ask(1, 0, m, l, r); }
  void Change(int x, LL w) { Change(1, 0, m, x, w); }
  LL Output() { return Output(1, 0, m); }
} seg;

bool Init() {
  static int o[kMaxN];
  cin >> n >> p;
  for (int i = 1, x; i <= n; i++) {
    cin >> w[i] >> x;
    w[i] <<= 1, b[i] = x == 1, s += w[i];
    if (b[i] && w[i] > p) {
      cout << -1 << '\n';
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    w[i] = (w[i] + w[i - 1]) % p, o[i] = i;
  }
  sort(o, o + n + 1, [](int i, int j) {
    return w[i] < w[j];
  });
  for (int i = 1; i <= n; i++) {
    a[o[i]] = a[o[i - 1]] + (w[o[i - 1]] < w[o[i]]);
  }
  sort(w, w + n + 1), m = unique(w, w + n + 1) - w - 1;
  return 1;
}

void Dp() {
  seg.Init();
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      continue;
    }
    int l = a[i - 1], r = a[i] == 0 ? m : a[i] - 1;
    LL ans = kInf;
    if (l <= r) {
      ans = min(ans, seg.Ask(l, r) - w[l]);
    } else {
      ans = min(ans, seg.Ask(l, m) - w[l]);
      ans = min(ans, seg.Ask(0, r) - w[l] + p);
    }
    seg.Change(l, ans);
  }
  cout << s + seg.Output() << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init() ? Dp() : void();
  return 0;
}
