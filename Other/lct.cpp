#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;
struct V {
  int d, w, f, s[2];
  bool b;
} v[kMaxN];
int n, m;

int Son(int x) {
  return (v[v[x].f].s[0] == x) + (v[v[x].f].s[1] == x) * 2 - 1;
}

void Update(int x) {
  v[x].w = v[x].d ^ v[v[x].s[0]].w ^ v[v[x].s[1]].w;
}

void Tag(int x) {
  v[x].b ^= 1, swap(v[x].s[0], v[x].s[1]);
}

void Pushdown(int x) {
  if (v[x].b) {
    Tag(v[x].s[0]), Tag(v[x].s[1]), v[x].b = 0;
  }
}

void Rotate(int x, bool o) {
  int y = v[x].s[!o], p = Son(x);
  v[x].s[!o] = v[y].s[o], v[y].s[o] = x;
  v[y].f = v[x].f, v[x].f = y, v[v[x].s[!o]].f = x;
  ~p && (v[v[y].f].s[p] = y);
  Update(x), Update(y);
}

void RePush(int x) {
  ~Son(x) ? RePush(v[x].f) : void(), Pushdown(x);
}

void Splay(int x) {
  RePush(x);
  for (int p = Son(x), q = Son(v[x].f); ~p; p = Son(x), q = Son(v[x].f)) {
    if (~q) {
      Rotate(p == q ? v[v[x].f].f : v[x].f, !p);
      Rotate(v[x].f, !q);
    } else {
      Rotate(v[x].f, !p);
    }
  }
}

void Access(int x) {
  for (int y = 0; x; y = x, x = v[x].f) {
    Splay(x), v[x].s[1] = y, Update(x);
  }
}

void MakeRoot(int x) {
  Access(x), Splay(x), Tag(x);
}

int Find(int x) {
  Access(x), Splay(x);
  for (; v[x].s[0];) {
    x = v[x].s[0], Pushdown(x);
  }
  return Splay(x), x;
}

void Link(int x, int y) {
  if (Find(x) != Find(y)) {
    MakeRoot(x), v[x].f = y;
  }
}

bool Exist(int x, int y) {
  MakeRoot(x), Access(y), Splay(x);
  return v[x].s[1] == y && !v[y].s[0];
}

void Cut(int x, int y) {
  if (Exist(x, y)) {
    v[x].s[1] = 0, v[y].f = 0, Update(x);
  }
}

void Change(int x, int d) {
  Splay(x), v[x].d = d, Update(x);
}

int Ask(int x, int y) {
  MakeRoot(x), Access(y), Splay(x);
  return v[x].w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].d;
  }
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x >> y;
    if (o == 0) {
      cout << Ask(x, y) << '\n';
    } else if (o == 1) {
      Link(x, y);
    } else if (o == 2) {
      Cut(x, y);
    } else {
      Change(x, y);
    }
  }
  return 0;
}
