#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL p, d, x;
} e[2001];
struct B {
  LL et, d = 2e9 + 1;
} v[2001];
LL n, m;
bool b[2001];

LL S(LL x, LL y, LL s) {
  if (b[x]) {
    return 2e9 + 1;
  }
  if (x == y) {
    return s;
  }
  b[x] = true;
  LL ans = 2e9 + 1;
  for (LL i = v[x].et; i; i = e[i].p) {
    ans = min(ans, S(e[i].d, y, s + e[i].x));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (LL i = 1, a, b, c; i <= m; i++) {
    cin >> a >> b >> c;
    e[i] = {v[a].et, b, c}, v[a].et = i;
    if (a == b) {
      v[a].d = c;
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = v[i].et; j; j = e[j].p) {
      fill(&b[0], &b[2000] + 1, false);
      v[i].d = min(v[i].d, e[j].x + S(e[j].d, i, 0));
    }
    cout << (v[i].d >= 2e9 + 1 ? -1 : v[i].d) << endl;
  }
  return 0;
}
