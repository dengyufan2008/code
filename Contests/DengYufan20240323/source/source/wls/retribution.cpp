#include <bits/stdc++.h>
using namespace std;
const int N = 1.8e3 + 10, Q = 1e6 + 10;
int n, m, q, seed;
char ch[4] = {'U', 'D', 'L', 'R'};
int dx[4] = {-1, 1, 0, 0},
    dy[4] = {0, 0, -1, 1};
namespace Input {
    mt19937_64 R;
    inline void init(int seed) {
        R = mt19937_64(seed);
    }
    inline int get(int l, int r) {
        uniform_int_distribution<int> distribution(l, r);
        return distribution(R);
    }
}  // namespace Input
char s[N][N];
vector<int> G[N * N], H[N * N];

bool inq[N * N];
int dfn[N * N], low[N * N], sta[N * N], top;
int scc[N * N], sccnt;
void tarjan(int u) {
    static int _d = 0;
    dfn[u] = low[u] = ++_d;
    sta[++top] = u, inq[u] = 1;
    for (auto v : H[u]) {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (inq[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        scc[u] = ++sccnt, inq[u] = 0;
        while (sta[top] != u) {
            scc[sta[top]] = sccnt;
            inq[sta[top]] = 0;
            --top;
        }
        --top;
    }
}

int fa[N * N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

pair<int, int> E[4 * N * N];
int et = 0;
void add_edge(int u, int v) {
    H[u].push_back(v), E[++et] = make_pair(u, v);
    fa[find(u)] = find(v);
}

vector<pair<int, int>> qr[N * N];
int ind[N * N];
bool ans[Q];
mt19937 rnd;
void merg(int u, int v) {
    for (auto [ed, id] : qr[u]) {
        if (ed == v) ans[id] = 1;
        else if (!ans[id]) qr[v].emplace_back(ed, id);
    }
    // if (rnd() % 200 == 0) {
    //     sort(qr[v].begin(), qr[v].end()), qr[v].erase(unique(qr[v].begin(), qr[v].end()), qr[v].end()), qr[v].shrink_to_fit();
    // }
}
void topo() {
    queue<int> q;
    for (int i = 1; i <= sccnt; i++)
        if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : G[u]) {
            merg(u, v);
            if (--ind[v] == 0) q.push(v);
        }
        qr[u].clear(), qr[u].shrink_to_fit();
    }
}
#define id(x, y) (((x)-1) * (m) + (y))
#define out(x, y) ((x) < 1 || (x) > n || (y) < 1 || (y) > m)
set<pair<int, int>> st;

int main() {
    freopen("retribution.in", "r", stdin);
    freopen("retribution.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> q >> seed;
    iota(fa + 1, fa + n * m + 1, 1);
    Input::init(seed);
    for (int i = 1; i <= n; i++) cin >> (s[i] + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (out(ni, nj) || ch[k] == s[i][j]) continue;
                add_edge(id(i, j), id(ni, nj));
            }
        }
    }
    for (int i = 1; i <= n * n; i++)
        if (!dfn[i]) tarjan(i);
    // cerr << sccnt << '\n';
    for (int i = 1; i <= et; i++) {
        int u = E[i].first, v = E[i].second;
        if (scc[u] != scc[v] && !st.count(make_pair(scc[u], scc[v]))) G[scc[u]].push_back(scc[v]), ind[scc[v]] += 1, st.insert(make_pair(scc[u], scc[v]));
    }
    st.clear();
    // cerr << clock() * 1.0 / CLOCKS_PER_SEC << '\n';
    for (int i = 1, x1, y1, x2, y2, st, ed; i <= q; i++) {
        // cin >> x1 >> y1 >> x2 >> y2;
        x1 = Input::get(1, n), y1 = Input::get(1, m), x2 = Input::get(1, n), y2 = Input::get(1, m);
        if (find(id(x1, y1)) != find(id(x2, y2))) continue;
        st = scc[id(x1, y1)], ed = scc[id(x2, y2)];
        if (st == ed) {
            ans[i] = 1;
            continue;
        }
        qr[st].emplace_back(ed, i);
    }
    topo();
    for (int i = 1; i <= q; i++) cout << ans[i];
    // cerr << clock() * 1.0 / CLOCKS_PER_SEC << '\n';
    return 0;
}