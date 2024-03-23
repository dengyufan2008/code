#include <chrono>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 1e6 + 1, kMod = 1e9 + 7;
struct E {
  LL p, d;
} e[kMaxN << 1];
struct V {
  LL d, w, et;
  bool b;
} v[kMaxN];
LL n, m, c, w, k, ans, d[kMaxN], p[kMaxN] = {1};
unordered_multiset<LL> s;
mt19937_64 Rand(chrono::steady_clock::now().time_since_epoch().count());

void S(LL f, LL x) {
  if (v[x].d) {
    return;
  }
  v[x].d = ++k;
  for (LL i = v[x].et; i; i = e[i].p) {
    if ((i >> 1) != f) {
      if (v[e[i].d].d) {
        if (v[e[i].d].d <= v[x].d) {
          LL c = Rand() / 2;
          v[x].w ^= c, v[e[i].d].w ^= c, d[i >> 1] ^= c;
        }
      } else {
        S(i >> 1, e[i].d);
      }
    }
  }
}

void T(LL f, LL x) {
  if (v[x].b) {
    return;
  }
  v[x].b = 1;
  for (LL i = v[x].et; i; i = e[i].p) {
    if ((i >> 1) != f && !v[e[i].d].b) {
      T(i >> 1, e[i].d);
      v[x].w ^= v[e[i].d].w, d[i >> 1] = v[e[i].d].w;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  srand(time(0));
  cin >> n >> m;
  if (m <= 1) {
    cout << 0;
    return 0;
  }
  for (LL i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    e[i * 2] = {v[x].et, y}, v[x].et = i * 2;
    e[i * 2 + 1] = {v[y].et, x}, v[y].et = i * 2 + 1;
  }
  for (LL i = 1; i <= n; i++) {
    if (!v[i].b) {
      c++, S(0, i), T(0, i);
    }
  }
  for (LL i = 1; i <= m; i++) {
    w += d[i] > 0, s.insert(d[i]);
    p[i] = p[i - 1] * 2 % kMod;
  }
  for (LL i = 1; i <= m; i++) {
    if (d[i]) {
      LL t = s.count(d[i]);
      if (m - n + c - 1 >= 0) {
        ans = (ans + p[m - n + c - 1] * t % kMod) % kMod;
        if (m - n + c - 2 >= 0) {
          ans = (ans + p[m - n + c - 2] * (w - t) % kMod) % kMod;
        }
      }
    }
  }
  cout << ans;
  return 0;
}
