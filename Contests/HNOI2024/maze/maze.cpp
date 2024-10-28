#include <fstream>
#define LL long long

using namespace std;

ifstream cin("maze.in");
ofstream cout("maze.out");

const LL kMaxN = 16, kMaxM = 1 << kMaxN + 1, kInf = 1e18;
struct V {
  LL w;
  int l, r;
} v[kMaxM * kMaxN * 56];
int t, n, u, s[kMaxM];
LL m, a[kMaxM];

void Change(int &p, int l, int r, int x, LL w) {
  if (!p) {
    p = ++u, v[p] = v[0];
  }
  if (l == r) {
    v[p].w = w;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(v[p].l, l, mid, x, w);
  } else {
    Change(v[p].r, mid + 1, r, x, w);
  }
  v[p].w = min(v[v[p].l].w, v[v[p].r].w);
}

void Calc(int p, int l, int r, int &s, int q, LL w) {
  if (!p) {
    return;
  }
  if (l == r) {
    Change(s, 1, 1 << n, l, min(v[p].w + w, kInf));
    return;
  }
  int mid = l + r >> 1;
  Calc(v[p].l, l, mid, s, v[q].l, min(w, v[v[q].r].w));
  Calc(v[p].r, mid + 1, r, s, v[q].r, w);
}

LL Ask(int p, int l, int r, int _l, int _r, bool shit = 0) {
  if (!p) {
    return kInf;
  } else if (l >= _l && r <= _r) {
    return v[p].w;
  }
  int mid = l + r >> 1;
  LL ans = kInf;
  if (mid >= _l) {
    ans = min(ans, Ask(v[p].l, l, mid, _l, _r, shit));
  }
  if (mid < _r) {
    ans = min(ans, Ask(v[p].r, mid + 1, r, _l, _r, shit));
  }
  return ans;
}

int Find(int p, int l, int r, LL w) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1;
  if (v[v[p].r].w <= w) {
    return Find(v[p].r, mid + 1, r, w);
  } else {
    return Find(v[p].l, l, mid, w);
  }
}

LL Print(int x, LL in) {
  LL out = 0;
  // cout << x << ' ' << in << '\n';
  if (x >= (1 << n)) {
    cout << a[x] << ' ';
    return out;
  }
  int y = Find(s[x], 1, 1 << n, in);
  // cout << ' ' << y << '\n';
  if (Ask(s[x << 1], 1, 1 << n, y, y) < kInf) {
    LL w = Ask(s[x << 1 | 1], 1, 1 << n, y, 1 << n);
    LL t = Print(x << 1, in - min(w, (LL)a[x]));
    out += t, in -= t;
    // cout << "  " << x << ' ' << in << '\n';
    in < w && (out += a[x], in -= a[x]);
    t = Print(x << 1 | 1, in);
    out += t, in -= t;
    // cout << "   " << x << ' ' << in << '\n';
  } else {
    LL w = Ask(s[x << 1], 1, 1 << n, y, 1 << n);
    LL t = Print(x << 1 | 1, in - w);
    out += t, in -= t;
    // cout << "  " << x << ' ' << in << '\n';
    t = Print(x << 1, in);
    out += t, in -= t;
    // cout << "   " << x << ' ' << in << '\n';
  }
  return out;
}

void Shit(int p, int l, int r) {
  if (!p) {
    return;
  } else if (l == r) {
    cout << l << ": " << v[p].w << '\n';
    return;
  }
  int mid = l + r >> 1;
  Shit(v[p].l, l, mid), Shit(v[p].r, mid + 1, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  v[0].w = kInf;
  cin >> t;
  while (t--) {
    u = 0, fill(&s[1], &s[1 << n + 1], 0);
    cin >> n >> m;
    for (int i = 1; i < 1 << n + 1; i++) {
      cin >> a[i];
    }
    for (int i = 1 << n; i < 1 << n + 1; i++) {
      Change(s[i], 1, 1 << n, a[i], 0);
    }
    for (int i = (1 << n) - 1; i >= 1; i--) {
      Calc(s[i << 1], 1, 1 << n, s[i], s[i << 1 | 1], a[i]);
      Calc(s[i << 1 | 1], 1, 1 << n, s[i], s[i << 1], kInf);
    }
    Print(1, m), cout << '\n';
    // for (int i = 1; i < 1 << n + 1; i++) {
    //   cout << "[" << i << "]\n";
    //   Shit(s[i], 1, 1 << n);
    // }
    // cout << '\n';
  }
  return 0;
}
