#include <fstream>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1, kMaxL = 20, kMaxV = 1e9;
struct V {
  int w;   // 从代表元加过来要进多少次位
  int p;   // 加一圈要进多少次位
  int t;   // 进位偏移
  bool b;  // 是否在非 0 环上
} v[kMaxN];
int n, m, k;
unordered_map<int, int> s;

class Seg {
  struct V {
    int l, r, s;
  } v[kMaxN * 40];
  int k, s[kMaxL][kMaxN];

  void Xor(int &p, int l, int r, int x, int y) {
    !p && (p = ++k);
    if (l == r) {
      v[p].s ^= y;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Xor(v[p].l, l, mid, x, y);
    } else {
      Xor(v[p].r, mid + 1, r, x, y);
    }
    v[p].s = v[v[p].l].s ^ v[v[p].r].s;
  }

  int Ask(int p, int l, int r, int x) {
    if (!p) {
      return 0;
    } else if (r <= x) {
      return v[p].s;
    }
    int mid = l + r >> 1;
    int ans = Ask(v[p].l, l, mid, x);
    if (mid < x) {
      ans ^= Ask(v[p].r, mid + 1, r, x);
    }
    return ans;
  }

 public:
  void Xor(int c, int t, int x, int y) {
    Xor(s[c][t], 1, kMaxV, x, y);
  }

  int Ask(int c, int t, int x) {
    return Ask(s[c][t], 1, kMaxV, x);
  }
} seg;

void Init() {
  static int o[kMaxN];
  for (int i = 0; i < k; i++) {
    o[i] = -1;
  }
  for (int i = 0, j, cc = 1; i < k; i++) {
    for (j = i; o[j] == -1; j = j * 2 % k) {
      o[j] = i;
    }
    if (j && o[j] == i) {
      int c = j * 2 >= k;
      v[j].w = 0, v[j].b = 1;
      for (int l = j * 2 % k; l != j;) {
        v[l].w = c, v[l].b = 1, l <<= 1;
        if (l >= k) {
          l -= k, c++;
        }
      }
      v[j].p = c, v[j].t = cc;
      for (int l = j * 2 % k; l != j; l = l * 2 % k) {
        v[l].p = c, v[l].t = cc;
      }
      cc += c;
    }
  }
}

void Xor(int x, int y) {
  int u = 1, c = 0;
  LL _u = 1LL * k * u;
  for (; !(x % _u); u = _u, _u = 1LL * k * u) {
    c++;
  }
  while (x <= n && !v[x / u % k].b) {
    s[x] ^= y, x += x % _u;
    for (; !(x % _u); u = _u, _u = 1LL * k * u) {
      c++;
    }
  }
  if (x <= n) {
    V &_v = v[x / u % k];
    seg.Xor(c, (x / _u - _v.w + _v.p) % _v.p + _v.t, x / u, y);
  }
}

int Ask(int x) {
  int u = 1, c = 0;
  LL _u = 1LL * k * u;
  int ans = 0;
  for (; !(x % _u); u = _u, _u = 1LL * k * u) {
    c++;
  }
  while (1) {
    V &_v = v[x / u % k];
    if (_v.b) {
      ans ^= seg.Ask(c, (x / _u - _v.w + _v.p) % _v.p + _v.t, x / u);
    } else {
      ans ^= s[x];
    }
    x -= x % _u;
    if (x) {
      for (; !(x % _u); u = _u, _u = 1LL * k * u) {
        c++;
      }
    } else {
      break;
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k, Init();
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> y, Xor(x, y);
    } else {
      cout << Ask(x) << '\n';
    }
  }
  return 0;
}
