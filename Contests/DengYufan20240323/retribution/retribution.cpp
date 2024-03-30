#include <fstream>
#include <random>

using namespace std;

ifstream cin("retribution.in");
ofstream cout("retribution.out");

const int kMaxN = 4e6 + 1, kMove[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
struct E {
  int d, p;
} e[kMaxN * 6];
struct V {
  int xmn, xmx, ymn, ymx;
  int d, l, r, i, ht, et, t;
} v[kMaxN];
int n, m, q, t, o[128], d[kMaxN];
bool b[kMaxN];
char c;
mt19937_64 Rand;

void Init() {
  int seed;
  cin >> seed, Rand = mt19937_64(seed);
}

int Get(int l, int r) {
  uniform_int_distribution<int> distribution(l, r);
  return distribution(Rand);
}

int R(int x, int y) { return (x - 1) * m + y; }

void AddEdge(int x, int y, bool o) {
  static int k = 0;
  e[++k].d = y;
  if (o) {
    e[k].p = v[x].t, v[x].t = k;
  } else {
    e[k].p = v[x].et, v[x].et = k, !v[x].ht && (v[x].ht = k);
  }
}

void T(int x) {
  static int k = 0;
  v[x].d = v[x].l = ++k, d[++t] = x;
  for (int i = v[x].et; i; i = e[i].p) {
    if (!v[e[i].d].d) {
      T(e[i].d);
      v[x].l = min(v[x].l, v[e[i].d].l);
    } else if (!v[e[i].d].r) {
      v[x].l = min(v[x].l, v[e[i].d].d);
    }
  }
  if (v[x].l == v[x].d) {
    for (; d[t] != x; t--) {
      v[d[t]].r = x, e[v[d[t]].ht].p = v[x].et, v[x].et = v[d[t]].et;
      v[x].xmn = min(v[x].xmn, v[d[t]].xmn);
      v[x].xmx = max(v[x].xmx, v[d[t]].xmx);
      v[x].ymn = min(v[x].ymn, v[d[t]].ymn);
      v[x].ymx = max(v[x].ymx, v[d[t]].ymx);
    }
    v[x].r = x, t--;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  o['L'] = 0, o['R'] = 1, o['U'] = 2, o['D'] = 3;
  cin >> n >> m >> q, Init();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> c;
      v[R(i, j)] = {i, i, j, j};
      for (int k = 0; k < 4; k++) {
        int _i = i + kMove[k][0], _j = j + kMove[k][1];
        if (k != o[c] && _i >= 1 && _i <= n && _j >= 1 && _j <= m) {
          AddEdge(R(i, j), R(_i, _j), 0);
        }
      }
    }
  }
  for (int i = 1; i <= n * m; i++) {
    !v[i].d ? T(i) : void();
  }
  for (int i = 1; i <= n * m; i++) {
    if (v[i].r == i) {
      for (int j = v[i].et; j; j = e[j].p) {
        b[v[e[j].d].r] = 1;
      }
      b[i] = 0;
      for (int j = v[i].et; j; j = e[j].p) {
        if (b[v[e[j].d].r]) {
          b[v[e[j].d].r] = 0, v[v[e[j].d].r].i++;
          AddEdge(i, v[e[j].d].r, 1);
        }
      }
    }
  }
  for (int i = 1; i <= n * m; i++) {
    if (v[i].r == i && !v[i].i) {
      d[++t] = i;
    }
  }
  for (int h = 1; h <= t; h++) {
    for (int i = v[d[h]].t; i; i = e[i].p) {
      v[e[i].d].xmn = min(v[e[i].d].xmn, v[d[h]].xmn);
      v[e[i].d].xmx = max(v[e[i].d].xmx, v[d[h]].xmx);
      v[e[i].d].ymn = min(v[e[i].d].ymn, v[d[h]].ymn);
      v[e[i].d].ymx = max(v[e[i].d].ymx, v[d[h]].ymx);
      if (!--v[e[i].d].i) {
        d[++t] = e[i].d;
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    int x = Get(1, n), y = Get(1, m), z = Get(1, n);
    z = v[R(z, Get(1, m))].r;
    cout << (x >= v[z].xmn && x <= v[z].xmx && y >= v[z].ymn && y <= v[z].ymx);
  }
  cout << '\n';
  return 0;
}
