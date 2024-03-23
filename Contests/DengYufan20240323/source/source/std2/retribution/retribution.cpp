#include <bits/stdc++.h>
#define PB push_back
#define EB emplace_back
using namespace std;
const int maxn = 1800, maxs = 3240000;
char mp[maxn + 5][maxn + 5];
vector<pair<int, int>> g[maxn + 5][maxn + 5];
int dfn[maxn + 5][maxn + 5], low[maxn + 5][maxn + 5], stamp;
int col[maxn + 5][maxn + 5], cc;
stack<pair<int, int>> st;
void tarjan(int x, int y) {
    st.emplace(x, y);
    dfn[x][y] = low[x][y] = ++stamp;
    for (const auto& [tx, ty] : g[x][y]) {
        if (!dfn[tx][ty]) {
            tarjan(tx, ty);
            low[x][y] = min(low[x][y], low[tx][ty]);
        } else if (!col[tx][ty]) low[x][y] = min(low[x][y], dfn[tx][ty]);
    }
    if (low[x][y] == dfn[x][y]) {
        cc++;
        int i, j;
        do {
            tie(i, j) = st.top(), st.pop();
            col[i][j] = cc;
        } while (i != x || j != y); 
    }
}
vector<pair<int, int>> cL[maxs + 5];
vector<int> ng[maxs + 5], rg[maxs + 5];
int oud[maxs + 5];
inline void addE(int u, int v) { rg[v].PB(u), oud[u]++; }
int U[maxs + 5], D[maxs + 5], L[maxs + 5], R[maxs + 5];
const int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
mt19937_64 rng;
inline int get(int l, int r) {
    uniform_int_distribution<int> d(l, r);
    return d(rng);
}
int main() {
  freopen("retribution.in", "r", stdin);
  freopen("retribution.out", "w", stdout); 
    int n, m, Q, sd;
    scanf("%d%d%d%d", &n, &m, &Q, &sd);
    rng = mt19937_64(sd);
    for (int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int dir = 0; dir < 4; dir++) {
                int x = i + d[dir][0], y = j + d[dir][1];
                if (1 <= x && x <= n && 1 <= y && y <= m && mp[x][y] != "UDLR"[dir]) g[i][j].EB(x, y);
            }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!dfn[i][j]) tarjan(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cL[col[i][j]].EB(i, j);
            for (const auto& [x, y] : g[i][j])
                if (col[i][j] != col[x][y]) addE(col[i][j], col[x][y]);
        }
    queue<int> q;
    for (int i = 1; i <= cc; i++)
        if (!oud[i]) q.push(i);
    fill(U + 1, U + cc + 1, 1E9), fill(L + 1, L + cc + 1, 1E9);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& [x, y] : cL[u]) U[u] = min(U[u], x), D[u] = max(D[u], x), L[u] = min(L[u], y), R[u] = max(R[u], y);
        for (int v : rg[u]) {
            U[v] = min(U[v], U[u]), D[v] = max(D[v], D[u]), L[v] = min(L[v], L[u]), R[v] = max(R[v], R[u]);
            if (!(--oud[v])) q.push(v);
        }
    }
    for (int i = 1; i <= Q; i++) {
        int sx = get(1, n), sy = get(1, m), tx = get(1, n), ty = get(1, m);
        int c = col[tx][ty];
        putchar('0' + (U[c] <= sx && sx <= D[c] && L[c] <= sy && sy <= R[c]));
    }
}
