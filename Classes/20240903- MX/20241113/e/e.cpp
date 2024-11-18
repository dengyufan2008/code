#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 2e5 + 1, kMod = 1e9 + 7;
struct V {
  int c;
  LL w, t = 1;
} v[kMaxN << 2];
int n, a[kMaxN], d[kMaxN], w[kMaxN];
LL s, ans;

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

void Tag(int p, LL w) {
  v[p].w = v[p].w * w % kMod, v[p].t = v[p].t * w % kMod;
}

void Pushdown(int p) {
  Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t), v[p].t = 1;
}

void Pushup(int p) {
  v[p].c = v[p << 1].c + v[p << 1 | 1].c;
  v[p].w = (v[p << 1].w + v[p << 1 | 1].w) % kMod;
}

void Change(int p, int l, int r, int x, LL w) {
  if (l == r) {
    v[p].c = 1, v[p].w = w;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, w);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, w);
  }
  Pushup(p);
}

int Count(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p].c;
  }
  Pushdown(p);
  int mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    ans += Count(p << 1, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Count(p << 1 | 1, mid + 1, r, _l, _r);
  }
  return ans;
}

LL Sum(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p].w;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  LL ans = 0;
  if (mid >= _l) {
    ans += Sum(p << 1, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Sum(p << 1 | 1, mid + 1, r, _l, _r);
  }
  return ans % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], d[i] = i;
  }
  sort(d + 1, d + n + 1, [](int i, int j) {
    return a[i] < a[j];
  });
  s = 1;
  for (int i = 1; i <= n; i++) {
    w[i] = a[d[i]], s = s * (w[i] - i + 1) % kMod;
  }
  if (!s) {
    cout << 0 << '\n';
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    LL t = s * Pow(w[i] - i + 1 << 1) % kMod;
    ans = (ans + Sum(1, 1, n, 1, d[i]) * t) % kMod;
    ans = (ans - Sum(1, 1, n, d[i], n) * t) % kMod;
    ans = (ans + Count(1, 1, n, d[i], n) * s) % kMod;
    Tag(1, (w[i] - i) * Pow(w[i] - i + 1) % kMod);
    Change(1, 1, n, d[i], (w[i] - i));
  }
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
