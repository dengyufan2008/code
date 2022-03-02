#include <iostream>
#define LL long long

using namespace std;

const LL kInf = 1e18;
struct E {
  LL x, v, p;
} e[40002];
struct V {
  LL et, b, p;
} v[20001];
LL n, m, s, t, k, ans;

LL Dfs(LL x, LL y) {
  if (x == t) {
    ans += y;
    return y;
  } else if (v[x].b == k || !y) {
    return 0;
  }
  v[x].b = k;
  for (LL i = v[x].et; i; i = e[i].p) {
    LL t = Dfs(e[i].x, min(y, e[i].v));
    if (t) {
      e[i].v -= min(y, t), e[i ^ 1].v += min(y, t);
      return min(y, t);
    }
  }
  return 0;
}

int main() {
  cin >> n >> m >> s >> t;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    e[i * 2] = {y, z, v[x].et}, v[x].et = i * 2;
    e[i * 2 + 1] = {x, 0, v[y].et}, v[y].et = i * 2 + 1;
  }
  for (k++; Dfs(s, kInf); k++) {
  }
  cout << ans;
  return 0;
}
