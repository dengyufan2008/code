#include <fstream>

using namespace std;

ifstream cin("w.in");
ofstream cout("w.out");

const int kMaxN = 5e5 + 1;
struct V {
  int mn, c, t;
  int f, s[2];
  bool b;
} v[kMaxN];
int u, n, m;

void TagB(int x) {
  v[x].b ^= 1, swap(v[x].s[0], v[x].s[1]);
}

void TagC(int x, int y) {
  v[x].c += y, v[x].t += y;
}

void Pushdown(int x) {
  if (v[x].b) {
    TagB(v[x].s[0]), TagB(v[x].s[1]), v[x].b = 0;
  }
  if (v[x].t) {
    TagC(v[x].s[0], v[x].t);
    TagC(v[x].s[1], v[x].t);
    v[x].t = 0;
  }
}

void Pushup(int x) {
  v[x].mn = v[x].s[1] ? v[v[x].s[1]].mn : x;
}

int Son(int x) {
  return (v[v[x].f].s[0] == x) + (v[v[x].f].s[1] == x) * 2 - 1;
}

void RePush(int x) {
  ~Son(x) ? RePush(v[x].f) : void(), Pushdown(x);
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
  while (~Son(x)) {
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
  Access(x), Splay(x), TagB(x);
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
  x > y ? swap(x, y) : void();
  int z = FindRoot(y);
  if (FindRoot(x) != z) {
    MakeRoot(x), v[x].f = y, MakeRoot(z);
    Access(y), Splay(y), TagC(y, v[x].c);
  }
}

bool Exist(int x, int y) {
  MakeRoot(x), Access(y), Splay(x);
  return v[x].s[1] == y && !v[y].s[0];
}

void Cut(int x, int y) {
  x > y ? swap(x, y) : void();
  int z = FindRoot(y);
  if (Exist(x, y)) {
    v[x].s[1] = v[y].f = 0, Pushup(x), MakeRoot(z);
    Access(y), Splay(y), TagC(y, -v[x].c);
  }
}

int FindGap(int x, int y) {
  if (v[x].s[0] && v[v[x].s[0]].mn <= y) {
    return FindGap(v[x].s[0], y);
  } else if (x <= y) {
    return x;
  }
  return FindGap(v[x].s[1], y);
}

void Merge(int x, int y) {
  int topx, topy, _x, _y, mid;
  Access(x), topx = FindTop(x);
  if (topx == FindTop(y)) {
    return;
  }
  Access(y), topy = FindTop(y);
  if (FindTop(x) == topy) {
    return;
  }
  _x = FindTop(x), Access(v[_x].f), _y = FindTop(y);
  if (topx == topy) {
    Cut(_y, v[_y].f);
  }
  for (; Splay(_x), v[_x].mn < _y;) {
    _x = FindGap(_x, _y);
    if (~Son(_x)) {
      mid = v[_x].f, Cut(mid, _x);
      Link(_y, mid);
    }
    swap(_x, _y), swap(x, y);
  }
  Link(x, _y);
}

int Ask(int x, int y) { return v[FindGap(FindRoot(x), y)].c; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kMaxN; i++) {
    v[i].mn = i, v[i].c = 1;
  }
  cin >> u >> n >> m;
  for (int i = 1, o, x, y, p = 0; i <= m; i++) {
    cin >> o >> x >> y;
    if (u) {
      x = (x + p - 1) % n + 1, y = (y + p - 1) % n + 1;
    }
    if (o == 1) {
      Merge(x, y);
    } else {
      cout << Ask(x, y) << '\n';
    }
  }
  return 0;
}
