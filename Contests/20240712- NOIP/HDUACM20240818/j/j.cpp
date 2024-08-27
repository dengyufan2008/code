// by lsl
#include <bits/stdc++.h>
#define ll unsigned int
using namespace std;
const int N = 3e5 + 10;
ll a[N], b[N];
ll ans;
int q, TE;
ll check(ll x, int p) {
  for (int i = 1; i <= q; i++) x = ((a[i] ^ x) + (b[i] ^ x)) % (1ll << (p + 1));
  return x;
}
void work() {
  ans = 0;
  cin >> q;
  for (int i = 1; i <= q; i++) cin >> a[i] >> b[i];
  for (int i = 0; i < 32; i++) {
    if (check(ans, i) == ans) continue;
    ans += (1ll << i);
  }
  for (int i = 1; i <= q; i++) {
    ans = ((a[i] ^ ans) + (b[i] ^ ans));
    cout << ans << '\n';
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> TE;
  while (TE--) work();
  return 0;
}
