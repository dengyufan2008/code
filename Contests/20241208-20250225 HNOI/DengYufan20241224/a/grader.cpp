#include <bits/stdc++.h>

#include "vector.h"
#define vi vector<int>
#define N 2051
using namespace std;
namespace gra {
int n, k, B, ct, in[N];
vi a[N], b[N], c[N], ret[N];
void Ret(int x) {
  printf("Wrong Answer %d\n", x);
  exit(0);
}
vi merge(vi a, vi b) {
  for (int i = 0; i < k; ++i) a[i] = max(a[i], b[i]);
  return a;
}
vi Query(vi s) {
  ++ct;
  if (ct > B) Ret(3);
  if (!s.size()) Ret(4);
  if (s.size() > n) Ret(5);
  vi ans;
  ans.resize(k);
  for (int v : s) {
    if (v < 1 || v > n) Ret(6);
    if (in[v]) Ret(5);
    in[v] = 1;
    ans = merge(ans, a[v]);
  }
  for (int v : s) in[v] = 0;
  return ans;
}
const int maxv = 1e9 + 1;
mt19937 rnd(time(0));
void Solve() {
  scanf("%d%d%d", &n, &k, &B);
  b[0].resize(k), c[n + 1].resize(k);
  for (int i = 1; i <= n; ++i) {
    a[i].resize(k);
    for (int j = 0; j < k; ++j) a[i][j] = rnd() % maxv;
    b[i] = merge(b[i - 1], a[i]);
  }
  for (int i = n; i >= 1; --i) c[i] = merge(c[i + 1], a[i]);
  for (int i = 1; i <= n; ++i) ret[i] = merge(b[i - 1], c[i + 1]);
  vector<vi> Ret1 = solve(n, k, B);
  if (Ret1.size() != n) Ret(1);
  for (auto v : Ret1)
    if (v.size() != k) Ret(1);
  for (int i = 0; i < n; ++i)
    if (ret[i + 1] != Ret1[i]) Ret(2);
  printf("Correct\n");
}
}  // namespace gra
vi query(vi s) { return gra::Query(s); }
int main() {
  gra::Solve();
  return 0;
}
