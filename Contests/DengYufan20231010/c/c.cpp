#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 6e5 + 1, kMaxM = 9e5 + 1, kInf = 1e9;
struct A {
  int x, w;
};
struct E {
  int x, y;
  bool b;
} e[kMaxM];
struct V {
  int r, d, f, w, p;
  vector<A> e, g;
} v[kMaxN];
int n, m;

int GetRoot(int x) { return v[x].r == x ? x : v[x].r = GetRoot(v[x].r); }

void S(int f, int x) {
  v[x].f = f, e[v[x].w].b ^= v[x].d & 1;
  for (v[x].p = f; v[v[x].p].w > v[x].w; v[x].p = v[v[x].p].p) {
  }
  v[v[x].p].g.push_back({x, v[x].w});
  for (A i : v[x].e) {
    if (i.x != f) {
      v[i.x].w = i.w;
      S(x, i.x);
      e[v[x].w].b ^= !e[v[i.x].w].b;
    }
  }
}

int T(int x) {
  int mn = 0;
  for (A i : v[x].g) {
    if (!e[i.w].b && (!mn || v[mn].w > v[i.x].w)) {
      mn = i.x;
    }
  }
  return mn ? T(mn) : x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].x >> e[i].y;
    e[i].x++, e[i].y++, v[e[i].x].d++, v[e[i].y].d++;
  }
  for (int i = 1; i <= n; i++) {
    v[i].r = i;
  }
  for (int i = m; i >= 1; i--) {
    if (GetRoot(e[i].x) != GetRoot(e[i].y)) {
      v[e[i].x].e.push_back({e[i].y, i});
      v[e[i].y].e.push_back({e[i].x, i});
      v[GetRoot(e[i].x)].r = GetRoot(e[i].y);
    } else {
      e[i].b = 1;
    }
  }
  S(0, 1);
  if (!e[v[1].w].b) {
    for (int i = T(1); i; i = v[i].f) {
      e[v[i].w].b ^= 1;
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << e[i].b;
  }
  return 0;
}
