#include <fstream>
#define LL long long

using namespace std;

ifstream cin("channel.in");
ofstream cout("channel.out");

const int kMaxN = 4e5 + 1, kInf = 1e9;
int shit, r, c, n, q, e[kMaxN];
LL ans;
char ch;
class LCT {
 private:
  struct V {
    int w, p, f, s[2];
    bool b;
  } v[kMaxN];
  int o;

  void Pushup(int x) {
    v[x].p = x;
    if (v[x].s[0] && v[v[v[x].s[0]].p].w * o > v[v[x].p].w * o) {
      v[x].p = v[v[x].s[0]].p;
    }
    if (v[x].s[1] && v[v[v[x].s[1]].p].w * o > v[v[x].p].w * o) {
      v[x].p = v[v[x].s[1]].p;
    }
  }

  void Pushdown(int x) {
    if (v[x].b) {
      v[v[x].s[0]].b ^= 1, v[v[x].s[1]].b ^= 1;
      swap(v[v[x].s[0]].s[0], v[v[x].s[0]].s[1]);
      swap(v[v[x].s[1]].s[0], v[v[x].s[1]].s[1]);
      v[x].b = 0;
    }
  }

  int Son(int x) {
    return (v[v[x].f].s[0] == x) + (v[v[x].f].s[1] == x) * 2 - 1;
  }

  void RePush(int x) {
    Pushup(x), ~Son(x) ? RePush(v[x].f) : (void)0, Pushdown(x);
  }

  void Rotate(int x, bool b) {
    int y = v[x].s[!b], s = Son(x);
    v[x].s[!b] = v[y].s[b], v[y].s[b] = x;
    v[y].f = v[x].f, v[x].f = y, v[v[x].s[!b]].f = x;
    ~s && (v[v[y].f].s[s] = y);
    Pushup(x), Pushup(y);
  }

 public:
  /// @param _o 最小生成树(1) 最大生成树(-1)
  void Init(int _o) {
    o = _o;
    if (o == -1) {
      v[n + 1].w = kInf;
      for (int i = 1; i <= n; i += 2) {
        v[i].w = kInf;
      }
    }
  }

  void Splay(int x) {
    RePush(x);
    for (int s = Son(x), t = Son(v[x].f); ~s; s = Son(x), t = Son(v[x].f)) {
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
    Access(x), Splay(x), v[x].b ^= 1, swap(v[x].s[0], v[x].s[1]);
  }

  int Find(int x) {
    Access(x), Splay(x);
    for (; v[x].s[0]; x = v[x].s[0]) {
      Pushdown(x);
    }
    Splay(x);
    return x;
  }

  void MakePath(int x, int y) {
    MakeRoot(x), Access(y), Splay(x);
  }

  bool Exist(int x, int y) {
    return MakePath(x, y), v[x].s[1] == y && !v[y].s[0];
  }

  void Link(int x, int y) {
    if (Find(x) != Find(y)) {
      MakeRoot(x), v[x].f = y;
    }
  }

  void Cut(int x, int y) {
    if (Exist(x, y)) {
      v[x].s[1] = v[y].f = 0, Pushup(x);
    }
  }

  void Change(int x, int w) {
    Splay(x), v[x].w = w, Pushup(x);
  }

  int AskP(int x) { return v[x].p; }

  int AskW(int x) { return v[x].w; }
} mn, mx;

void Decode(char ch, int &x, int &y, int &w, LL ans) {
  static int v = 0xfffff;
  w = (int)((w ^ ans) & v);
  if (ch == '-') {
    x = (x + ans - 1) % (r + 1 >> 1) + 1, y = (y + ans - 1) % (c - 1 >> 1) + 1;
  }
  if (ch == '|') {
    x = (x + ans - 1) % (r - 1 >> 1) + 1, y = (y + ans - 1) % (c + 1 >> 1) + 1;
  }
}

int R(int x, int y) {
  return (x - 1) * c + y;
}

pair<int, int> W(int x) {
  int w = ((x - 1) / c) & 1 ? c : 1;
  return {x - w, x + w};
}

pair<int, int> V(int x) {
  int l, r;
  if (((x - 1) / c) & 1) {
    l = x - 1, !(l % c) && (l = n + 1);
    r = x + 1, !(x % c) && (r = n + 1);
  } else {
    l = x - c, l < 1 && (l = n + 1);
    r = x + c, r > n && (r = n + 1);
  }
  return {l, r};
}

void Change(int mid, int w) {
  int x = W(mid).first, y = W(mid).second;
  int l = V(mid).first, r = V(mid).second;
  mn.Change(mid, w), mx.Change(mid, w);
  if (e[mid] > w) {
    if (mn.Exist(x, mid) && mn.Exist(y, mid)) {
      ans -= e[mid] - w;
    } else {
      mn.MakePath(x, y);
      int p = mn.AskP(x);
      if (mn.AskW(p) > w) {
        pair<int, int> q;
        ans -= mn.AskW(p) - w;
        q = W(p), mn.Cut(p, q.first), mn.Cut(p, q.second);
        mn.Link(x, mid), mn.Link(y, mid);
        mx.Cut(l, mid), mx.Cut(r, mid);
        q = V(p), mx.Link(p, q.first), mx.Link(p, q.second);
      }
    }
  } else if (e[mid] < w && (!mx.Exist(l, mid) || !mx.Exist(r, mid))) {
    mx.MakePath(l, r);
    int p = mx.AskP(l);
    ans += min(mx.AskW(p), w) - e[mid];
    if (mx.AskW(p) < w) {
      pair<int, int> q;
      q = V(p), mx.Cut(p, q.first), mx.Cut(p, q.second);
      mx.Link(l, mid), mx.Link(r, mid);
      mn.Cut(x, mid), mn.Cut(y, mid);
      q = W(p), mn.Link(p, q.first), mn.Link(p, q.second);
    }
  }
  e[mid] = w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> shit >> r >> c >> q;
  r = r * 2 - 1, c = c * 2 - 1, n = r * c;
  mn.Init(1), mx.Init(-1);
  for (int i = 1; i <= r; i += 2) {
    if (i < r) {
      mn.Link(R(i, 1), R(i + 1, 1));
      mn.Link(R(i + 1, 1), R(i + 2, 1));
    }
    for (int j = 1; j < c; j++) {
      mn.Link(R(i, j), R(i, j + 1));
      if (j > 1) {
        mx.Link(R(i + 1, j), R(i + 1, j + 1));
      }
    }
    mx.Link(R(i + 1, c), n + 1);
  }
  for (int i = 1, x, y, w; i <= q; i++) {
    cin >> ch >> x >> y >> w;
    shit ? Decode(ch, x, y, w, ans) : (void)0;
    x = x * 2 - 1, y = y * 2 - 1;
    ch == '-' ? Change(R(x, y + 1), w) : Change(R(x + 1, y), w);
    cout << ans << '\n';
  }
  return 0;
}
