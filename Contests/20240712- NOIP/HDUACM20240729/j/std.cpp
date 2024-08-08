#include <cstdio>
typedef unsigned long long ull;
const int N = 63, M = 1200005;
int Case, n, m, o, i, j, k, at[N], w[N], lim[N], nxt[M];
bool g[N][N], h[N][N], can[N][N];
ull adj[N], sub0[(1 << 20) + 1], sub1[(1 << 20) + 1], sub2[(1 << 20) + 1], f[M];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
inline int lcm(int a, int b) { return a / gcd(a, b) * b; }
inline int getlim(int o, int x) {
  if (!can[o][x]) return 1;
  if (w[o] > 1 || w[x] > 1 || at[o] == at[x]) return n;
  int ret = 1;
  for (int i = 0; i < n; i++)
    if (can[o][i] && can[i][x]) ret = lcm(ret, w[i]);
  return ret;
}
inline int getper(int x) {
  int m = lim[x], i, j;
  for (nxt[1] = j = 0, i = 2; i <= m; nxt[i++] = j) {
    while (j && ((f[j + 1] ^ f[i]) >> x & 1)) j = nxt[j];
    if (!((f[j + 1] ^ f[i]) >> x & 1)) j++;
  }
  return m - nxt[m];
}
int main() {
  freopen("j.in", "r", stdin);
  freopen("j.ans", "w", stdout);
  scanf("%d", &Case);
  while (Case--) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
      char ch[N];
      scanf("%s", ch);
      adj[i] = 0;
      for (j = 0; j < n; j++) {
        g[i][j] = ch[j] == '1';
        if (g[i][j]) adj[i] |= 1ULL << j;
      }
    }
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++) can[i][j] = g[i][j] | (i == j);
    for (k = 0; k < n; k++)
      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) can[i][j] |= can[i][k] & can[k][j];
    for (i = 0; i < n; i++) w[i] = 0;
    for (i = 0; i < n; i++) {
      if (w[i]) continue;
      m = 0;
      for (j = i; j < n; j++)
        if (can[i][j] && can[j][i]) m++;
      for (j = i; j < n; j++)
        if (can[i][j] && can[j][i]) {
          at[j] = i;
          w[j] = m;
        }
    }
    for (o = 0; o < N; o++) {
      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) h[i][j] = 0;
      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
          for (k = 0; k < n; k++) h[i][k] |= g[i][j] & g[j][k];
      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) g[i][j] = h[i][j];
    }
    m = 1 << (n < 20 ? n : 20);
    for (i = 0; i < m; i++) sub0[i] = sub1[i] = sub2[i] = 0;
    for (i = 0; i < n; i++) {
      j = i;
      if (j < 20) {
        sub0[1 << j] |= adj[i];
        continue;
      } else
        j -= 20;
      if (j < 20) {
        sub1[1 << j] |= adj[i];
        continue;
      } else
        j -= 20;
      sub2[1 << j] |= adj[i];
    }
    for (i = 2; i < m; i++) {
      j = i & -i;
      sub0[i] = sub0[i ^ j] | sub0[j];
      sub1[i] = sub1[i ^ j] | sub1[j];
      sub2[i] = sub2[i ^ j] | sub2[j];
    }
    for (o = 0; o < n; o++) {
      m = 1;
      for (i = 0; i < n; i++) {
        lim[i] = getlim(o, i) * 2;
        if (m < lim[i]) m = lim[i];
      }
      ull S = 0;
      for (i = 0; i < n; i++)
        if (g[o][i]) S |= 1ULL << i;
      for (i = 1; i <= m; i++) {
        f[i] = S;
        S = sub0[S & 1048575] | sub1[S >> 20 & 1048575] | sub2[S >> 40];
      }
      for (i = 0; i < n; i++) printf("%d%c", getper(i), i + 1 < n ? ' ' : '\n');
    }
  }
}
