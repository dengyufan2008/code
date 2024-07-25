#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxs = 200000, mod = 1e9 + 7, maxc = 33, maxk = 1e5 + 5;
const int TMP = 300000;  // n=10^10时，上限239496
inline void inc(int &x, int y) {
  x += y;
  (mod <= x) && (x -= mod);
}
inline void dec(int &x, int y) {
  x -= y;
  (x < 0) && (x += mod);
}
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int sub(int x, int y) { return x < y ? x - y + mod : x - y; }
inline int div2(int x) { return ((x & 1) ? x + mod : x) >> 1; }
inline ll sqrll(int x) { return 1ll * x * x; }
inline int pw(int x, int y) {
  int z = 1;
  for (; y; y >>= 1, x = 1ll * x * x % mod)
    if (y & 1) z = 1ll * z * x % mod;
  return z;
}

int pri[maxs / 7], lpf[maxs + 1], pcnt, lim, mul, num[maxc + 1], cnt, K, T;
int fun[TMP][maxc + 3];  // fun[i][j]，id为i的表达式和为j的方案数，如2x+2y+3z=10
int sum[TMP];            // sum为表达式左边有几个数，必须小于K
int Sum[TMP];            // Sum为当前所有数的和，必须<=maxc
int las[TMP];
int mem[TMP][maxc + 1];
int f[maxc + 3];  // F[c]表示f(p^c)的答案
ll global_n, lis[maxs + 1];
int le[maxs + 1],  // x<=\sqrt{n}
    ge[maxs + 1];  // x>\sqrt{n}
#define idx(v) (v <= lim ? le[v] : ge[global_n / v])
int G[maxs + 1], Fprime[maxs + 1], fac[maxk], ifac[maxk];

void sieve(int n) {
  pcnt = 0;
  for (int i = 2; i <= n; ++i) {
    if (lpf[i] == 0) {
      lpf[i] = ++pcnt;
      pri[lpf[i]] = i;
    }
    for (int j = 1, v; j <= lpf[i] && (v = i * pri[j]) <= n; ++j) lpf[v] = j;
  }
}
void init(ll n) {
  cnt = 0;
  for (ll i = 1, j, v; i <= n; i = n / j + 1) {
    j = n / i;
    v = j % mod;
    lis[++cnt] = j;
    (j <= lim ? le[j] : ge[global_n / j]) = cnt;
    G[cnt] = sub(v, 1ll);
  }
}

void calcFprime() {
  for (int k = 1; k <= pcnt; ++k) {
    int p = pri[k];
    ll sqrp = sqrll(p);
    for (int i = 1; lis[i] >= sqrp; ++i) {
      ll v = lis[i] / p;
      int id = idx(v);
      dec(G[i], sub(G[id], (k - 1)));
    }
  }
  for (int i = 1; i <= cnt; ++i) Fprime[i] = 1ll * G[i] * num[1] % mod;
}
void bfs() {
  int u[maxc + 1] = {0};
  int l = 0, r = 1;
  for (int j = 0; j <= maxc; j++) mem[1][j] = u[j];
  fun[1][0] = 1;
  las[1] = 1;
  while (l < r) {
    l++;
    for (int j = 0; j <= maxc; j++) u[j] = mem[l][j];
    if (sum[l] + 1 == K) break;
    for (int i = las[l]; i <= maxc && Sum[l] + i <= maxc; i++)
      if (u[i] < num[i]) {
        u[i]++;
        r++;
        for (int j = 0; j <= maxc; j++) mem[r][j] = u[j];
        sum[r] = sum[l] + 1;
        Sum[r] = Sum[l] + i;
        las[r] = i;
        for (int j = i; j <= maxc; j++)
          fun[r][j] = add(fun[l][j - i], fun[r][j - i]);
        int tmp = mul;
        for (int j = 1; j <= maxc; j++) tmp = 1ll * tmp * ifac[u[j]] % mod * ifac[num[j] - u[j]] % mod;
        for (int j = 0; j <= maxc; j++) inc(f[j], 1ll * fun[r][j] * tmp % mod);
        u[i]--;
      }
  }
}
int F(int k, ll n) {
  if (n < pri[k] || n <= 1) return 0;
  int id = idx(n);
  ll ans = Fprime[id] - (k - 1) * num[1];
  for (int i = k; i <= pcnt && sqrll(pri[i]) <= n; ++i) {
    ll pw = pri[i], pw2 = sqrll(pw);
    for (int c = 1; pw2 <= n; ++c, pw = pw2, pw2 *= pri[i])
      ans += (1ll * f[c] * F(i + 1, n / pw) + f[c + 1]) % mod;
  }
  return ans % mod;
}
int main() {
  //	freopen("data.in","r",stdin);
  scanf("%d", &T);
  for (; T--;) {
    memset(lpf, 0, sizeof(lpf));
    scanf("%lld%d", &global_n, &K);
    fac[0] = 1;
    for (int i = 1; i <= K; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[K] = pw(fac[K], mod - 2);
    for (int i = K; i; i--) ifac[i - 1] = 1ll * ifac[i] * i % mod;
    int tmpK = 0, x;
    memset(num, 0, sizeof(num));
    for (int i = 1; i <= K; i++) {
      scanf("%d", &x);
      if (x <= maxc) num[x]++, tmpK++;
    }
    mul = 1;
    for (int i = 1; i <= maxc; i++) mul = 1ll * mul * fac[num[i]] % mod;
    K = tmpK;
    memset(fun, 0, sizeof(fun));
    memset(f, 0, sizeof(f));
    bfs();
    lim = sqrt(global_n);
    sieve(lim + 1000);
    init(global_n);
    calcFprime();
    printf("%lld\n", (F(1, global_n) + 1ll + mod) % mod);
  }
}
/*
100 3
1 1 1

100 3
1 2 3
*/
