#include <bits/stdc++.h>
#define p1 998244353
#define p2 1000000007
#define ll long long
using namespace std;
#define N 100005
const int B = 260;
int n, q, i, j, x, l, r, bl, br, num;
int dfn[N], ed[N];
int pre[N], lst[N];
ll l0, r0, ans, s0[N], s[N / B + 2][N];
void dfs(int x) {
  dfn[x] = ++num;
  for (int j = lst[x]; j; j = pre[j]) dfs(j);
  ed[x] = num;
}
int tr[N], sum1[N], sum2[N];
void ad(int k, int x) {
  while (k <= n) tr[k] += x, k += -k & k;
}
int he(int k) {
  int ret = 0;
  while (k) ret += tr[k], k -= -k & k;
  return ret;
}
int main() {
  freopen("c.in","r",stdin);
  freopen("c.ans","w",stdout);
  scanf("%d", &n);
  for (i = 2; i <= n; i++) {
    scanf("%d", &x);
    pre[i] = lst[x], lst[x] = i;
  }
  dfs(1);
  for (i = 1; i <= n; i++) {
    ad(dfn[i], 1);
    s0[i] = he(ed[i]) - he(dfn[i] - 1);
  }
  memset(tr, 0, sizeof(tr));
  for (i = 1; i <= n; i++) {
    s0[i] = s0[i] + s0[i - 1] + he(dfn[i]);
    ad(dfn[i], 1), ad(ed[i] + 1, -1);
  }
  memset(tr, 0, sizeof(tr));
  // s1:点是块祖先,s2:块是点祖先
  for (i = 1; i <= n; i += B) {
    memset(sum1, 0, sizeof(sum1));
    memset(sum2, 0, sizeof(sum2));
    for (j = i; j <= n && j < i + B; j++)
      sum1[dfn[j]]++, sum2[dfn[j]]++, sum2[ed[j] + 1]--;
    for (j = 1; j <= n; j++) sum1[j] += sum1[j - 1], sum2[j] += sum2[j - 1];
    for (j = 1; j <= n; j++)
      s[(i - 1) / B][j] = s[(i - 1) / B][j - 1] + sum1[ed[j]] - sum1[dfn[j] - 1] + sum2[dfn[j]];
  }
  for (i = 1; i <= (n - 1) / B; i++)
    for (j = 1; j <= n; j++)
      s[i][j] += s[i - 1][j];
  scanf("%d", &q);
  while (q--) {
    scanf("%lld%lld", &l0, &r0);
    l0 ^= ans, r0 ^= ans;
    l0 = l0 % n + 1, r0 = r0 % n + 1;
    if (l0 > r0) swap(l0, r0);
    l = l0, r = r0, bl = (l - 1) / B, br = (r - 1) / B;
    ans = s0[r] - s0[l - 1];
    if (bl) ans -= s[bl - 1][r] - s[bl - 1][l - 1];
    if (bl + 1 < br) ans -= s[br - 1][l - 1] - s[bl][l - 1] - s[br - 1][bl * B] + s[bl][bl * B];
    for (i = bl * B + 1; i < l; i++) ad(dfn[i], 1);
    if (bl == br) {
      for (i = l; i <= r; i++) ans -= he(ed[i]) - he(dfn[i] - 1);
    } else {
      for (i = l; i <= bl * B + B; i++) ans -= he(ed[i]) - he(dfn[i] - 1);
      for (i = br * B + 1; i <= r; i++) ans -= he(ed[i]) - he(dfn[i] - 1);
    }
    for (i = bl * B + 1; i < l; i++) ad(ed[i] + 1, -1);
    if (bl == br) {
      for (i = l; i <= r; i++) ans -= he(dfn[i]);
    } else {
      for (i = l; i <= bl * B + B; i++) ans -= he(dfn[i]);
      for (i = br * B + 1; i <= r; i++) ans -= he(dfn[i]);
    }
    printf("%lld\n", ans);
    for (i = bl * B + 1; i < l; i++) ad(dfn[i], -1), ad(ed[i] + 1, 1);
  }
  return 0;
}