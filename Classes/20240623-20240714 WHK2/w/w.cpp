#include <fstream>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("w.in");
ofstream cout("w.out");

const int kMaxN = 2e5, kMaxL = 18;
struct V {
  int l, r, w;
} v[kMaxN * 30];
int n, m, k, b[kMaxN], p[kMaxL][kMaxN];
LL d[kMaxN], f[kMaxL][kMaxN];
unordered_map<int, int> h, s;

void Init() {
  b[0] = -1;
  for (int i = 1, j; i < k; i++) {
    for (j = i; !b[j]; j = j * 2 % k) {
      b[j] = i;
    }
    if (b[j] == i) {
      LL _d = 0;
      for (; b[j] == i; j = j * 2 % k) {
        _d += j, b[j] = -1, p[0][j] = j * 2 % k, f[0][j] = j;
      }
      d[i] = _d;
      for (; b[j] == -1; j = j * 2 % k) {
        d[j] = _d, b[j] = -2;
      }
    }
  }
  for (int i = 0; i < k; i++) {
    b[i] = b[i] != -2;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 0; j < k; j++) {
      p[i][j] = p[i - 1][p[i - 1][j]];
      f[i][j] = f[i - 1][j] + f[i - 1][p[i - 1][j]];
    }
  }
}

void Xor(int &p, int l, int r, int x, int y) {
  static int t = 0;
  !p && (p = ++t);
  if (l == r) {
    v[p].w ^= y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Xor(v[p].l, l, mid, x, y);
  } else {
    Xor(v[p].r, mid + 1, r, x, y);
  }
  v[p].w = v[v[p].l].w ^ v[v[p].r].w;
}

int Calc(int p, int l, int r, int x) {
  if (!p) {
    return 0;
  } else if (r <= x) {
    return v[p].w;
  }
  int mid = l + r >> 1, ans = Calc(v[p].l, l, mid, x);
  if (mid < x) {
    ans ^= Calc(v[p].r, mid + 1, r, x);
  }
  return ans;
}

int Find(int x, int w, int c) {
  x += (n - x) / d[c] / w * d[c] * w;
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (x + f[i][c] * w <= n) {
      x += f[i][c] * w, c = p[i][c];
    }
  }
  return x;
}

void Add(int x, int y) {
  int w = 1, c = x % k;
  for (; !c; w *= k, c = x / w % k) {
  }
  for (; b[c] && x <= n;) {
    h[x] ^= y, x += c * w, c = c * 2 % k;
    for (; !c; w *= k, c = x / w % k) {
    }
  }
  if (x <= n) {
    Xor(s[Find(x, w, c)], 1, n, x, y);
  }
}

int Ask(int x) {
  int w = 1, c = x % k, ans = 0;
  for (; x; x -= c * w, c = x / w % k) {
    for (; !c; w *= k, c = x / w % k) {
    }
    if (b[c]) {
      ans ^= h.count(x) ? h[x] : 0;
    } else {
      int _x = Find(x, w, c);
      ans ^= s.count(_x) ? Calc(s[_x], 1, n, x) : 0;
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  Init();
  for (int i = 1, x, y; i <= m; i++) {
    cin >> y;
    if (y == 1) {
      cin >> x >> y;
      Add(x, y);
    } else {
      cin >> x;
      cout << Ask(x) << '\n';
    }
  }
  return 0;
}
