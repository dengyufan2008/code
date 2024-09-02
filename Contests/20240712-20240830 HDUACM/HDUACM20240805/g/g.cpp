#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 1e5 + 1, kMod = 998244353;
struct V {
  int p, r, s;
  bool b;
  LL f, g, _f;
  vector<int> e;
} v[kMaxN];
int o, n, m, h, a[kMaxN];
LL w, ans, s[kMaxN], t[kMaxN];

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

void S(int f, int x) {
  v[x].p = f, v[x].r = ++m, v[x].s = v[x].f = 1;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i), v[x].s += v[i].s;
      v[x].f = v[x].f * v[i].f % kMod;
    }
  }
  v[x].f = (v[x].f + 1) % kMod;
}

void CalcInv() {
  s[0] = 1;
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] * v[i].f % kMod;
  }
  t[n] = Pow(s[n]);
  for (int i = n; i >= 1; i--) {
    t[i - 1] = t[i] * v[i].f % kMod;
    v[i]._f = s[i - 1] * t[i] % kMod;
  }
}

void T(int f, int x) {
  LL w = 1;
  for (int i : v[x].e) {
    if (i != f) {
      w = w * v[i].f % kMod;
    }
  }
  for (int i : v[x].e) {
    if (i != f) {
      v[i].g = (v[x].g * w % kMod * v[i]._f + 1) % kMod;
      T(x, i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  v[1].g = 1, cin >> o;
  while (o--) {
    m = ans = 0;
    for (int i = 1; i <= n; i++) {
      v[i].b = 0, v[i].e.clear();
    }
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
      cin >> x, a[x + 1] = i;
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    S(0, 1), CalcInv(), T(0, 1);
    h = a[1], v[a[1]].b = 1, w = (v[a[1]].f - 1) * v[a[1]]._f % kMod;
    for (int i = 1; i <= n; i++) {
      int x = a[i];
      for (; v[h].r > v[x].r || v[h].r + v[h].s <= v[x].r;) {
        h = v[h].p, v[h].b = 1;
        w = w * (v[h].f - 1) % kMod * v[h]._f % kMod;
      }
      for (; !v[x].b;) {
        w = w * (v[x].f - 1) % kMod * v[x]._f % kMod;
        v[x].b = 1, x = v[x].p;
      }
      ans = (ans + w * v[h].f % kMod * v[h].g) % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}
