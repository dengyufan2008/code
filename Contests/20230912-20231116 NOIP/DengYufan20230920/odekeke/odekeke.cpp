#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("odekeke.in");
ofstream cout("odekeke.out");

const LL kMaxN = 1501, kMaxM = 1e5 + 1, kMod = 998244353;
struct V {
  LL w, d, o;
} v[kMaxN];
LL n, m, k, p1, p2, q1, q2, r1, r2, r3, r4, c, sf, sg, ans, d[kMaxN], f[kMaxM], g[kMaxM];

void InsertF(LL x) {
  sf += x;
  for (LL j = k; j >= x; j--) {
    f[j] = (f[j] + f[j - x]) % kMod;
  }
}

void InsertG(LL x) {
  sg += x;
  for (LL j = k; j >= x; j--) {
    g[j] = (g[j] + g[j - x]) % kMod;
  }
}

void DeleteF(LL x) {
  sf -= x;
  for (LL j = x; j <= k; j++) {
    f[j] = (f[j] - f[j - x] + kMod) % kMod;
  }
}

void DeleteG(LL x) {
  sg -= x;
  for (LL j = x; j <= k; j++) {
    g[j] = (g[j] - g[j - x] + kMod) % kMod;
  }
}

LL CalcF(LL p1, LL p2) {
  LL ans = 0;
  for (LL i = max(sf - p2, 0LL); i <= min(p1, sf); i++) {
    ans = (ans + f[i]) % kMod;
  }
  return ans;
}

LL CalcG(LL q1, LL q2) {
  LL ans = 0;
  for (LL i = max(sg - q2, 0LL); i <= min(q1, sg); i++) {
    ans = (ans + g[i]) % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> c;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].d;
  }
  cin >> p1 >> p2 >> q1 >> q2 >> r1 >> r2 >> r3 >> r4 >> c;
  k = max({p1, p2, q1, q2, r1, r2, r3, r4});
  sort(v + 1, v + n + 1, [](V i, V j) { return i.d < j.d; });
  for (LL i = 1, j; i <= n; i = j) {
    for (m++, j = i; j <= n && v[i].d == v[j].d; j++) {
      d[m] += v[j].w, v[j].o = m;
    }
  }
  f[0] = g[0] = 1;
  for (LL i = 1; i <= m; i++) {
    InsertF(d[i]);
  }
  for (LL i = 1; i <= n; i++) {
    InsertG(v[i].w);
  }
  ans = CalcF(min(p1, r1), min(p2, r2)) * CalcG(min(q1, r3), min(q2, r4)) % kMod;
  if (c) {
    for (LL i = 1; i <= n; i++) {
      DeleteF(d[v[i].o]), DeleteG(v[i].w);
      if (d[v[i].o] > v[i].w) {
        InsertF(d[v[i].o] - v[i].w);
      }
      ans = (ans + CalcF(min(p1, r1 - v[i].w), min(p2, r2 - v[i].w)) * CalcG(min(q1, r3 - v[i].w), min(q2, r4 - v[i].w)) % kMod) % kMod;
      InsertF(d[v[i].o]), InsertG(v[i].w);
      if (d[v[i].o] > v[i].w) {
        DeleteF(d[v[i].o] - v[i].w);
      }
    }
  }
  cout << ans;
  return 0;
}
