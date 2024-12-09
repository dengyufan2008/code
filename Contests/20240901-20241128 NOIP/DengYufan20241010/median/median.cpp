#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("median.in");
ofstream cout("median.out");

const int kMaxN = 7001, kMaxM = 31, kMod = 1e9 + 7;
struct V {
  int l, r, s, g, e[3];
  LL f[3][kMaxM][kMaxM];
} v[kMaxN * 3 / 2];
int n, m, k, w, a[kMaxN], b[kMaxN];
LL ans;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

int Mid(int x, int y) {
  return !~x || !~y ? -1 : min(x, y);
}

int Mid(int x, int y, int z) {
  if (!~x || !~y || !~z) {
    return -1;
  }
  return (LL)x + y + z - max(max(x, y), z) - min(min(x, y), z);
}

void Init(int &p, int l, int r) {
  static int t;
  p = ++t, v[p].l = l, v[p].r = r;
  if (l == r) {
    v[p].s = !~a[l], v[p].g = a[l];
    return;
  } else if (l + 1 == r) {
    v[p].s = !~a[l] + !~a[r], v[p].g = Mid(a[l], a[r]);
    return;
  }
  int mid1 = l + (r - l) / 3, mid2 = mid1 + (r - l + 2) / 3;
  Init(v[p].e[0], l, mid1);
  Init(v[p].e[1], mid1 + 1, mid2);
  Init(v[p].e[2], mid2 + 1, r);
  v[p].s = v[v[p].e[0]].s + v[v[p].e[1]].s + v[v[p].e[2]].s;
  v[p].g = Mid(v[v[p].e[0]].g, v[v[p].e[1]].g, v[v[p].e[2]].g);
}

void Clear(int s, LL f[kMaxM][kMaxM]) {
  for (int i = 0; i <= s; i++) {
    for (int j = 0; i + j <= s; j++) {
      f[i][j] = 0;
    }
  }
}

void Merge(int sg, int sh, LL f[kMaxM][kMaxM],
           LL g[kMaxM][kMaxM], LL h[kMaxM][kMaxM]) {
  int sf = sg + sh;
  for (int i = 0; i <= sg; i++) {
    for (int j = 0; i + j <= sg; j++) {
      for (int k = 0; k <= sh; k++) {
        for (int l = 0; k + l <= sh; l++) {
          f[i + k][j + l] = (f[i + k][j + l] + g[i][j] * h[k][l]) % kMod;
        }
      }
    }
  }
}

void Dp(int p, int mid) {
  if (!v[p].s) {
    int o = (v[p].g == mid) + (v[p].g > mid) * 2;
    v[p].f[0][0][0] = v[p].f[1][0][0] = v[p].f[2][0][0] = 0;
    v[p].f[o][0][0] = 1;
    return;
  } else if (v[p].l == v[p].r) {
    v[p].f[0][1][0] = v[p].f[1][0][0] = v[p].f[2][0][1] = 1;
    return;
  } else if (v[p].l + 1 == v[p].r) {
    if (!~a[v[p].l] && !~a[v[p].r]) {
      v[p].f[0][2][0] = v[p].f[1][0][0] = v[p].f[2][0][2] = 1;
      v[p].f[0][1][0] = v[p].f[0][1][1] = v[p].f[1][0][1] = 2;
    } else {
      int g = a[v[p].l] ^ a[v[p].r] ^ -1;
      int o = (g == mid) + (g > mid) * 2;
      v[p].f[0][0][0] = v[p].f[1][0][0] = 0;
      v[p].f[0][0][1] = v[p].f[1][0][1] = v[p].f[2][0][1] = 0;
      v[p].f[0][1][0] = v[p].f[min(o, 1)][0][0] = v[p].f[o][0][1] = 1;
    }
    return;
  }
  Dp(v[p].e[0], mid), Dp(v[p].e[1], mid), Dp(v[p].e[2], mid);
  static LL f[kMaxM][kMaxM];
  int s0 = v[v[p].e[0]].s, s1 = v[v[p].e[1]].s, s2 = v[v[p].e[2]].s;
  Clear(v[p].s, v[p].f[0]), Clear(v[p].s, v[p].f[1]), Clear(v[p].s, v[p].f[2]);
  for (int s = 0; s < 27; s++) {
    int o0 = s % 3, o1 = s / 3 % 3, o2 = s / 9;
    int o = o0 + o1 + o2 - min(min(o0, o1), o2) - max(max(o0, o1), o2);
    Clear(s0 + s1, f);
    Merge(s0, s1, f, v[v[p].e[0]].f[o0], v[v[p].e[1]].f[o1]);
    Merge(s0 + s1, s2, v[p].f[o], f, v[v[p].e[2]].f[o2]);
  }
}

LL Ask(int mid, int x, int y) {
  LL ask = 0;
  Dp(1, mid);
  for (int i = 0; i <= x; i++) {
    for (int j = 0; j <= y; j++) {
      LL c = Pow(mid, i) * Pow(w - mid - 1, j) % kMod;
      ask = (ask + v[1].f[1][i][j] * c) % kMod;
    }
  }
  return ask;
}

void Interpolation(LL f[kMaxM + 1], LL d[kMaxM + 2]) {
  static LL g[kMaxM + 2], h[kMaxM + 2];
  g[0] = 1, d[0] = 0;
  for (int i = 1; i <= k + 2; i++) {
    g[i] = 0, d[i] = 0;
  }
  for (int i = 0; i <= k + 1; i++) {
    for (int j = k + 2; j >= 1; j--) {
      g[j] = (g[j] * (kMod - i) + g[j - 1]) % kMod;
    }
    g[0] = g[0] * (kMod - i) % kMod;
  }
  for (int i = 0; i <= k + 1; i++) {
    for (int j = k + 2; j >= 1; j--) {
      h[j - 1] = (g[j] + i * h[j]) % kMod;
    }
    LL _f = f[i];
    for (int j = 0; j <= k + 1; j++) {
      if (i != j) {
        _f = _f * Pow(i - j + kMod) % kMod;
      }
    }
    for (int j = 0; j <= k + 1; j++) {
      d[j] = (d[j] + h[j] * _f) % kMod;
    }
  }
}

void Calc(int l, int r) {
  static LL f[kMaxM + 1], d[kMaxM + 2];
  int s1 = 0, s2 = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] != -1) {
      s1 += a[i] >= l && a[i] <= r;
      s2 += (a[i] > r) - (a[i] < l);
    }
  }
  if (min(s1 + s2 + k - 1, s1 - s2 + k) < 0) {
    return;
  }
  int x = s1 + s2 + k - 1 >> 1, y = s1 - s2 + k >> 1;
  if (r - l + 1 <= k + 2) {
    for (int i = l; i <= r; i++) {
      ans = (ans + Ask(i, x, y)) % kMod;
    }
    return;
  }
  f[0] = Ask(l, x, y);
  for (int i = 1; i <= k + 1; i++) {
    f[i] = (f[i - 1] + Ask(i + l, x, y)) % kMod;
  }
  Interpolation(f, d);
  for (int j = 0; j <= k + 1; j++) {
    ans = (ans + Pow(r - l, j) * d[j]) % kMod;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> w;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ~a[i] && (b[++m] = a[i]);
  }
  k = n - m, b[++m] = 0, b[++m] = w - 1;
  sort(b + 1, b + m + 1);
  int s = 0;
  Init(s, 1, n);
  int l = max(m - k + 1 >> 1, 1);
  int r = min(m + k + 1 >> 1, m);
  for (int i = l; i <= r; i++) {
    if (i == l || b[i] != b[i - 1]) {
      Calc(b[i], b[i]);
    }
  }
  for (int i = l; i < r; i++) {
    if (b[i] + 1 <= b[i + 1] - 1) {
      Calc(b[i] + 1, b[i + 1] - 1);
    }
  }
  cout << ans << '\n';
  return 0;
}
