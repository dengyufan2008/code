#include <algorithm>
#include <cstdio>
using namespace std;
typedef unsigned long long ull;
const int N = 63, inf = ~0U >> 1;
int Case, n, m, i, j, x, y, a[N], b[N], T[N], a_deg[N], b_deg[N];
ull a_all[N], a_ban[N], a_must[N], b_ban[N], nei[N], imp;
bool a_imp[N], can[N][N][2][2];
struct P {
  int val;
  ull way;
  P() {}
  P(int _val, ull _way) {
    val = _val;
    way = _way;
  }
  void clr() {
    val = -inf;
    way = 0;
  }
  void up(const P& b, int k = 0) {
    if (val > b.val + k) return;
    if (val < b.val + k) {
      val = b.val + k;
      way = b.way;
      return;
    }
    way += b.way;
  }
  void print() { printf("%d %llu\n", val, way); }
};
P dfs(ull S) {
  if (!S) return P(0, 1);
  int who = -1, best = inf;
  int cnt = __builtin_popcountll(S);
  if (imp & S)
    who = __builtin_ctzll(imp & S);
  else
    for (ull Q = S; Q; Q -= Q & -Q) {
      int x = __builtin_ctzll(Q);
      if (__builtin_popcountll(nei[x] & S) <= 2) continue;
      int a_deg = __builtin_popcountll(a_all[x] & S);
      int b_deg = __builtin_popcountll(b_ban[x] & S);
      int now = T[cnt - a_deg - 1] + T[cnt - b_deg - 1];
      if (now < best) who = x, best = now;
    }
  if (who < 0) {
    P ans(0, 1);
    for (ull Q = S; Q;) {
      int head = __builtin_ctzll(Q);
      Q -= Q & -Q;
      ull mask = S & nei[head];
      if (!mask) {
        S ^= 1ULL << head;
        ans.val += max(a[head], b[head]);
        if (a[head] == b[head]) ans.way *= 2;
        continue;
      }
      if ((mask & -mask) != mask) continue;
      S ^= 1ULL << head;
      static P dp[2][2];
      int x = head, o = 0;
      for (int i = 0; i < 2; i++) dp[0][i].clr();
      dp[0][0] = P(a[x], 1);
      dp[0][1] = P(b[x], 1);
      while (S & nei[x]) {
        int y = __builtin_ctzll(S & nei[x]);
        S ^= 1ULL << y;
        for (int j = 0; j < 2; j++) dp[o ^ 1][j].clr();
        for (int j = 0; j < 2; j++)
          if (dp[o][j].way) {
            if (can[x][y][j][0]) dp[o ^ 1][0].up(dp[o][j], a[y]);
            if (can[x][y][j][1]) dp[o ^ 1][1].up(dp[o][j], b[y]);
          }
        o ^= 1;
        x = y;
      }
      P cur(-inf, 0);
      for (int j = 0; j < 2; j++)
        if (dp[o][j].way) cur.up(dp[o][j]);
      if (!cur.way) return P(-inf, 0);
      ans.val += cur.val;
      ans.way *= cur.way;
      Q &= S;
    }
    while (S) {
      int head = __builtin_ctzll(S);
      S ^= 1ULL << head;
      static P dp[2][2][2];
      int x = head, o = 0;
      for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) dp[0][i][j].clr();
      dp[0][0][0] = P(a[x], 1);
      dp[0][1][1] = P(b[x], 1);
      while (S & nei[x]) {
        int y = __builtin_ctzll(S & nei[x]);
        S ^= 1ULL << y;
        for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 2; j++) dp[o ^ 1][i][j].clr();
          for (int j = 0; j < 2; j++)
            if (dp[o][i][j].way) {
              if (can[x][y][j][0]) dp[o ^ 1][i][0].up(dp[o][i][j], a[y]);
              if (can[x][y][j][1]) dp[o ^ 1][i][1].up(dp[o][i][j], b[y]);
            }
        }
        o ^= 1;
        x = y;
      }
      P cur(-inf, 0);
      for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
          if (dp[o][i][j].way && can[head][x][i][j]) cur.up(dp[o][i][j]);
      if (!cur.way) return P(-inf, 0);
      ans.val += cur.val;
      ans.way *= cur.way;
    }
    return ans;
  }
  S ^= 1ULL << who;
  P ans(-inf, 0);
  for (int o = 0; o < 2; o++) {
    ull nS = S, SA = 0, SB = 0, Q = 0;
    int val = 0;
    if (!o) {
      if (a_imp[who]) continue;
      val = a[who];
      SA ^= a_must[who] & nS;
      SB ^= a_ban[who] & nS;
      Q = a_all[who] & S;
    } else {
      val = b[who];
      SB ^= b_ban[who] & nS;
      Q = b_ban[who] & nS;
    }
    nS ^= Q;
    while (Q) {
      int x = __builtin_ctzll(Q);
      if (SA >> x & 1) {
        val += a[x];
        if (a_ban[x] & SA) break;
        if (a_must[x] & SB) break;
        if (a_imp[x]) break;
        SA ^= a_must[x] & nS;
        SB ^= a_ban[x] & nS;
        Q ^= a_all[x] & nS;
        nS ^= a_all[x] & nS;
      } else {
        val += b[x];
        if (b_ban[x] & SA) break;
        SB ^= b_ban[x] & nS;
        Q ^= b_ban[x] & nS;
        nS ^= b_ban[x] & nS;
      }
      Q ^= 1ULL << x;
    }
    if (Q) continue;
    P res = dfs(nS);
    ans.up(res, val);
  }
  return ans;
}
int main() {
  freopen("h.in", "r", stdin);
  freopen("h.ans", "w", stdout);
  for (i = 0; i < N; i++) {
    if (i <= 3)
      T[i] = 1;
    else
      T[i] = max(T[i - 1] + T[max(i - 5, 0)], max(T[i - 2] + T[i - 4], T[i - 3] + T[i - 3]));
    // printf("T[%d]=%d\n",i,T[i]);
  }
  scanf("%d", &Case);
  while (Case--) {
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) {
      scanf("%d%d", &a[i], &b[i]);
      a_ban[i] = a_must[i] = b_ban[i] = 0;
    }
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        for (x = 0; x < 2; x++)
          for (y = 0; y < 2; y++) can[i][j][x][y] = 1;
    while (m--) {
      char op[9];
      scanf("%s%d%d", op, &x, &y);
      x--;
      y--;
      if (op[0] == 'A') {
        // x -> !y
        // y -> !x
        a_ban[x] |= 1ULL << y;
        a_ban[y] |= 1ULL << x;
        can[x][y][0][0] = 0;
        can[y][x][0][0] = 0;
      } else {
        // x -> y
        //! y -> !x
        a_must[x] |= 1ULL << y;
        b_ban[y] |= 1ULL << x;
        can[x][y][0][1] = 0;
        can[y][x][1][0] = 0;
      }
    }
    imp = 0;
    for (i = 0; i < n; i++) {
      a_imp[i] = !!(a_ban[i] & a_must[i]);
      if (a_imp[i]) imp |= 1ULL << i;
      a_all[i] = a_ban[i] | a_must[i];
      nei[i] = a_all[i] | b_ban[i];
    }
    P ans = dfs((1ULL << n) - 1);
    ans.print();
  }
}
