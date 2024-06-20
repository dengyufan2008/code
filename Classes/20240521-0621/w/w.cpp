#include <fstream>

using namespace std;

ifstream cin("w.in");
ofstream cout("w.out");

const int kMaxN = 5e5 + 1;
struct V {
  int c, mx, f, s[2];
  bool b;
} v[kMaxN];
int u, n, m;

void Tag(int x) {
  v[x].b ^= 1, swap(v[x].s[0], v[x].s[1]);
}

void Pushdown(int x) {
  if (v[x].b) {
    Tag(v[x].s[0]), Tag(v[x].s[1]), v[x].b = 0;
  }
}

void Pushup(int x) {
  v[x].mx = max(x, v[v[x].s[1]].mx);
}

void RePush(int x) {
  ~Son(x) ? RePush(v[x].f) : void(), Pushdown(x);
}

int Son(int x) {
  return (v[v[x].f].s[0] == x) + (v[v[x].f].s[1] == x) * 2 - 1;
}

void Rotate(int x, bool o) {
  int y = v[x].s[!o], s = Son(x);
  v[x].s[!o] = v[y].s[o], v[y].s[o] = x;
  v[y].f = v[x].f, v[x].f = y;
  v[v[x].s[!o]].f = x, ~s && (v[v[y].f].s[s] = y);
  Pushup(x), Pushup(y);
}

void Splay(int x) {
  RePush(x);
  while (Son(x)) {
    int s = Son(x), t = Son(v[x].f);
    if (~t) {
      Rotate(s == t ? v[v[x].f].f : v[x].f, !s);
      Rotate(v[x].f, !t);
    } else {
      Rotate(v[x].f, !s);
    }
  }
}

void Access(int x) {
  for (int y = 0; x; y = x, x = v[x].f) {
    Splay(x), v[x].s[1] = y, Pushup(x);
  }
}

void MakeRoot(int x) {
  Access(x), Splay(x), Tag(x);
}

int FindTop(int x) {
  Splay(x);
  for (; v[x].s[0];) {
    x = v[x].s[0], Pushdown(x);
  }
  return Splay(x), x;
}

int FindRoot(int x) {
  return Access(x), FindTop(x);
}

void Link(int x, int y) {
  if (FindRoot(x) != FindRoot(y)) {
    MakeRoot(x), v[x].f = y;
  }
}

bool Exist(int x, int y) {
  MakeRoot(x), Access(y), Splay(x);
  return v[x].s[1] == y && !v[y].s[0];
}

void Cut(int x, int y) {
  if (Exist(x, y)) {
    v[x].s[1] = v[y].f = 0, Pushup(x);
  }
}

void Merge(int x, int y) {
  Access(x), Access(y);
  int _x = FindTop(x);
  Access(v[_x].f);
  int _y = FindTop(y);
  ;
}

int Ask(int x, int y) {
  ;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u >> n >> m;
  for (int i = 1, o, x, y, p = 0; i <= m; i++) {
    cin >> o >> x >> y;
    if (u) {
      x = (x + p - 1) % n + 1;
      y = (y + p - 1) % n + 1;
    }
    if (o == 1) {
      Merge(x, y);
    } else {
      cout << Ask(x, y) << '\n';
    }
  }
  return 0;
}
