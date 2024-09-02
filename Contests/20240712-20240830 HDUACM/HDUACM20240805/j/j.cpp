#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 2e5 + 1, kMaxM = 1 << 18;
const int kMod = 998244353, kG = 3, kMem = 512 << 20;

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

void Ntt(vector<LL> &f, int m, bool o) {
  static int u = 0, _u = 0, r[kMaxM] = {};
  if (u != m) {
    u = m, _u = Pow(m);
    for (int i = 0; i < m; i++) {
      r[i] = (r[i >> 1] >> 1) | (i & 1 ? m >> 1 : 0);
    }
  }
  for (int i = 0; i < m; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < m; i <<= 1) {
    LL g = Pow(kG, (kMod - 1) / (i + i) * (o ? i + i - 1 : 1));
    for (int j = 0; j < m; j += i + i) {
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
    for (int i = 0; i < m; i++) {
      f[i] = f[i] * _u % kMod;
    }
  }
}

struct Poly {
  bool o;
  vector<LL> f;

  void Clear() { o = 0, f.clear(); }
  void Set() { f.resize(max(1, (int)f.size())), f[0] = 1; }
  void Fill(int x) {
    int _x = 1;
    for (; _x < x; _x <<= 1) {
    }
    for (; f.size() < _x; f.push_back(1)) {
    }
  }
  void Left() {
    f.push_back(0);
    for (int i = f.size() - 1; i >= 1; i--) {
      f[i] = f[i - 1];
    }
    f[0] = 0;
  }

  void operator+=(Poly x) {
    f.resize(max(f.size(), x.f.size()));
    for (int i = 0; i < x.f.size(); i++) {
      f[i] = (f[i] + x.f[i]) % kMod;
    }
  }
  void operator*=(Poly x) {
    f.resize(max(f.size(), x.f.size()));
    for (int i = 0; i < x.f.size(); i++) {
      f[i] = f[i] * x.f[i] % kMod;
    }
  }
  void operator^=(int x) {
    int _x = 1;
    for (; _x < x; _x <<= 1) {
    }
    f.resize(_x), Ntt(f, _x, o), o ^= 1;
  }
};
struct V {
  int f, s, t, l;
  Poly w[2][2];
  vector<int> e;
} v[kMaxN];
int t, n, m, a[kMaxN];

Poly Mul(Poly x, Poly y) {
  int t = x.f.size() + y.f.size() - 1;
  x ^= t, y ^= t, x *= y, x ^= t;
  for (; !x.f.empty() && !x.f.back(); x.f.pop_back()) {
  }
  return x;
}

void R(int x) {
  v[x].s = 1;
  for (int &i : v[x].e) {
    R(i), v[x].s += v[i].s;
    if (v[v[x].e[0]].s < v[i].s) {
      swap(v[x].e[0], i);
    }
  }
  v[x].t = v[x].s;
  if (!v[x].e.empty()) {
    swap(v[x].e[0], v[x].e.back());
    v[x].t -= v[v[x].e.back()].s;
  }
}

void S(int x, int l) {
  v[x].l = l;
  if (!v[x].e.empty()) {
    S(v[x].e.back(), l);
  }
  for (int i = 0; i + 1 < v[x].e.size(); i++) {
    S(v[x].e[i], v[x].e[i]);
  }
}

void Calc10(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Calc10(l, mid), Calc10(mid + 1, r);
  v[a[l]].w[1][0] = Mul(v[a[l]].w[1][0], v[a[mid + 1]].w[1][0]);
  v[a[mid + 1]].w[1][0].Clear();
}

void Calc(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Calc(l, mid), Calc(mid + 1, r);
  v[a[l]].w[1][1] += v[a[mid + 1]].w[1][1];
  v[a[l]].w[1][1] += Mul(v[a[l]].w[0][1], v[a[mid + 1]].w[1][0]);
  v[a[l]].w[1][0] += Mul(v[a[l]].w[0][0], v[a[mid + 1]].w[1][0]);
  v[a[l]].w[0][0] = Mul(v[a[l]].w[0][0], v[a[mid + 1]].w[0][0]);
  v[a[l]].w[0][1] = Mul(v[a[l]].w[0][1], v[a[mid + 1]].w[0][0]);
  v[a[l]].w[0][1] += v[a[mid + 1]].w[0][1];
  v[a[mid + 1]].w[0][0].Clear(), v[a[mid + 1]].w[0][1].Clear();
  v[a[mid + 1]].w[1][0].Clear(), v[a[mid + 1]].w[1][1].Clear();
}

void T(int x) {
  if (v[x].e.empty()) {
    int y = v[x].l, z = v[y].f;
    v[x].w[0][1].Set();
    v[x].w[0][0].Set(), v[x].w[1][0].Set();
    v[x].w[0][0].Left(), v[x].w[1][0].Left();
    for (int i = y; i != x; i = v[i].e.back()) {
      v[i].w[0][1].Set();
      if (v[i].e.size() == 1) {
        v[i].w[0][0].Set(), v[i].w[1][0].Set();
        v[i].w[0][0].Left(), v[i].w[1][0].Left();
      } else {
        m = 0;
        for (int j = 0; j + 1 < v[i].e.size(); j++) {
          a[++m] = v[i].e[j], v[a[m]].w[1][0].Set();
        }
        Calc10(1, m), v[a[1]].w[1][0].Left();
        v[i].w[0][0] = v[i].w[1][0] = v[a[1]].w[1][0];
        v[a[1]].w[1][0].Clear();
      }
    }
    m = 0;
    for (int i = y; i != x; i = v[i].e.back()) {
      a[++m] = i;
    }
    a[++m] = x, Calc(1, m);
    if (z) {
      v[z].w[1][1] += v[y].w[1][0], v[z].w[1][1] += v[y].w[1][1];
      v[y].w[0][0].Clear(), v[y].w[0][1].Clear(), v[y].w[1][1].Clear();
    }
  } else {
    for (int i : v[x].e) {
      T(i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  __asm__("movq %0, %%rsp\n" ::"r"((char *)malloc(kMem) + kMem));
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    cin >> n;
    for (int i = 2; i <= n; i++) {
      cin >> v[i].f, v[v[i].f].e.push_back(i);
    }
    R(1), S(1, 1), T(1), v[1].w[1][0] += v[1].w[1][1];
    for (int i = 1; i <= n; i++) {
      cout << v[1].w[1][0].f[i] << " \n"[i == n];
    }
    v[1].w[0][0].Clear(), v[1].w[0][1].Clear();
    v[1].w[1][0].Clear(), v[1].w[1][1].Clear();
  }
  exit(0);
}
