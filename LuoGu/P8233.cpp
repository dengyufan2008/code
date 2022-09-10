#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 1e5 + 1;
struct V {
  int d, s, f[17];
  vector<int> e, p;
} v[kMaxN];
int n, m, ans[kMaxN];
pair<int, int> q[kMaxN];

void S(int f, int x) {
  v[x].s = 1, v[x].d = v[f].d + 1;
  for (int i : v[x].e) {
    if (i != f) {
      v[i].f[0] = x;
      S(x, i);
      v[x].s += v[i].s;
    }
  }
}

void T(int f, int x) {
  for (int i : v[x].p) {
    ans[i] = v[x].s - v[q[i].first].s - v[q[i].second].s;
  }
  for (int i : v[x].e) {
    if (i != f) {
      int c = v[i].s;
      v[x].s -= v[i].s, v[i].s = n;
      T(x, i);
      v[x].s += c, v[i].s = c;
    }
  }
}

int Father(int x, int d) {
  for (int i = 16; i >= 0; i--) {
    if (d >= 1 << i) {
      x = v[x].f[i], d -= 1 << i;
    }
  }
  return x;
}

int Lca(int x, int y) {
  (v[x].d > v[y].d ? x : y) = Father(v[x].d > v[y].d ? x : y, abs(v[x].d - v[y].d));
  for (int i = 16; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int main() {
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  S(0, 1);
  for (int i = 1; i <= 16; i++) {
    for (int j = 1; j <= n; j++) {
      v[j].f[i] = v[v[j].f[i - 1]].f[i - 1];
    }
  }
  cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    int l = Lca(x, y), d = v[x].d + v[y].d - v[l].d * 2, s = Father(v[x].d > v[y].d ? x : y, d / 2 - 1), t = Father(v[x].d <= v[y].d ? x : y, d / 2 - 1);
    if (!d) {
      ans[i] = n;
    } else if (!(d & 1)) {
      q[i] = {s, v[v[s].f[1]].d >= v[l].d ? v[s].f[1] : t};
      v[v[v[s].f[0]].d >= v[l].d ? v[s].f[0] : v[t].f[0]].p.push_back(i);
    }
  }
  T(0, 1);
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
