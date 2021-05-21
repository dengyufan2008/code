#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL p, d, t, k;
} e[200002];
struct B {
  LL et;
} v[100001];
LL n, m, x, y, ans = 1e18;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m >> x >> y;
  for (LL i = 1, a, b, c, d; i <= m; i++) {
    cin >> a >> b >> c >> d;
    e[i * 2] = {v[a].et, b, c, d}, v[a].et = i * 2;
    e[i * 2 + 1] = {v[b].et, a, c, d}, v[b].et = i * 2 + 1;
  }
  
  return 0;
}
