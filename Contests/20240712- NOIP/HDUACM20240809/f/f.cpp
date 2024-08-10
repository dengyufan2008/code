#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 2e5 + 1, kMod = 998244353, kG = 3, kMem = 256 << 20;
int o, n, m, c, k, _k;
LL inv[kMaxN];

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

void Ntt(vector<LL> &f, int t, bool o) {
  static int r[kMaxN << 2] = {};
  f.resize(t);
  for (int i = 0; i < t; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? t >> 1 : 0);
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < t; i <<= 1) {
    LL g = Pow(kG, (kMod - 1) / (i + i) * (o ? i + i - 1 : 1));
    for (int j = 0; j < t; j += i + i) {
      LL w = 1;
      for (int k = j; k < j + i; k++) {
        LL f0 = f[k], f1 = f[k + i] * w % kMod;
        f[k] = (f0 + f1) % kMod;
        f[k + i] = (f0 - f1 + kMod) % kMod;
        w = w * g % kMod;
      }
    }
  }
  if (o) {
    LL w = Pow(t);
    for (int i = 0; i < t; i++) {
      f[i] = f[i] * w % kMod;
    }
  }
}

struct Poly {
  vector<LL> f;

  Poly() {}
  Poly(vector<LL> _f) : f(_f) {}
  void operator*=(Poly x) {
    int t = 1, _t = f.size() + x.f.size() - 1;
    for (; t < _t; t <<= 1) {
    }
    Ntt(f, t, 0), Ntt(x.f, t, 0);
    for (int i = 0; i < t; i++) {
      f[i] = f[i] * x.f[i] % kMod;
    }
    Ntt(f, t, 1);
    for (; !f.empty() && !f.back(); f.pop_back()) {
    }
  }
} f, g, h;
vector<Poly> v;

void Divide(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Divide(l, mid), Divide(mid + 1, r);
  v[l] *= v[mid + 1];
}

void CalcFG() {
  vector<Poly> a{vector<LL>{1}}, b{vector<LL>{1}};
  vector<LL> u(2);
  cin >> n >> m >> c >> k, _k = Pow(k * 2 + 1);
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    if (x <= c) {
      u.back() = (1LL + k + min(c - x, k)) * _k % kMod;
      u.front() = (1 - u.back() + kMod) % kMod, a.push_back(u);
    } else {
      u.back() = (1LL + k - min(x - c, k + 1)) * _k % kMod;
      u.front() = (1 - u.back() + kMod) % kMod, b.push_back(u);
    }
  }
  v.swap(a), Divide(0, v.size() - 1), v.swap(a);
  v.swap(b), Divide(0, v.size() - 1), v.swap(b);
  f.f.swap(a.front().f), g.f.swap(b.front().f);
}

void CalcAns() {
  LL ans = 0, w[kMaxN] = {}, _w[kMaxN] = {};
  for (int i = 1; i <= n; i++) {
    w[i] = _w[i] = 1;
  }
  for (int i = 1; i <= m && i < f.f.size(); i++) {
    w[i - 1] = _w[i - 1] = f.f[i - 1] = 0;
    for (int j = i; j <= n; j++) {
      w[j] = w[j] * (j - i + 1) % kMod;
      _w[j] = _w[j] * inv[j - i + 1] % kMod;
    }
    h = f;
    for (int j = 0; j < h.f.size(); j++) {
      h.f[j] = h.f[j] * w[j] % kMod;
    }
    h *= g;
    for (int j = 0; j < h.f.size(); j++) {
      ans = (ans + _w[j] * h.f[j]) % kMod;
    }
  }
  cout << ans << '\n';
}

int main() {
  __asm__("movq %0, %%rsp\n" ::"r"((char *)malloc(kMem) + kMem));
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i < kMaxN; i++) {
    inv[i] = Pow(i);
  }
  cin >> o;
  while (o--) {
    CalcFG(), CalcAns();
  }
  exit(0);
}
