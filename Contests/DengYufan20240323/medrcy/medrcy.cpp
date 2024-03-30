#include <fstream>
#include <vector>

using namespace std;

ifstream cin("medrcy.in");
ofstream cout("medrcy.out");

const int kMaxN = 1001;
int t, n, m, k;
class G {
  int s, w, c[kMaxN], b[kMaxN];
  bool d[kMaxN], t[kMaxN], e[kMaxN][kMaxN], ans[kMaxN];
  static vector<int> l;
  static vector<vector<int>> r;

  int T(int x) {
    if (b[x] == 1) {
      return 0;
    }
    int o = b[x] = 1;
    for (int i = 1; i <= n; i++) {
      if (e[x][i] && c[i]) {
        o += T(i);
      }
    }
    return o;
  }

  void S(int x, int o) {
    if (b[x] == 2) {
      return;
    }
    t[x] |= o;
    for (int i = 1; i <= n; i++) {
      if (e[x][i] && c[i]) {
        S(i, o ^ 1);
      }
    }
  }

 public:
  void Clear() {
    w = kMaxN, l.clear();
    for (int i = 1; i <= n; i++) {
      c[i] = d[i] = ans[i] = 0;
      for (int j = 1; j <= n; j++) {
        e[i][j] = 0;
      }
    }
  }

  void AddEdge(int x, int y) {
    if (!e[x][y]) {
      e[x][y] = e[y][x] = 1;
      c[x]++, c[y]++;
    }
  }

  bool Check() {
    for (int i = 1; i <= n; i++) {
      if (c[i] > 2) {
        return 0;
      }
    }
    return 1;
  }

  void Update() {
    int o = s;
    for (int i = 1; i <= n; i++) {
      b[i] = t[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      if (!b[i] && c[i] == 1) {
        int x = T(i);
        o += x >> 1;
        S(i, (x & 1 ^ 1) << 1);
      }
    }
    for (int i = 1; i <= n; i++) {
      if (!b[i] && c[i] == 2) {
        o += T(i) + 1 >> 1;
        S(i, 2);
      }
    }
    if (o > w) {
      return;
    } else if (o < w) {
      w = o;
      for (int i = 1; i <= n; i++) {
        ans[i] = 0;
      }
    }
    for (int i = 1; i <= n; i++) {
      ans[i] |= t[i];
    }
  }

  int Size() { return s; }

  int FindMax() {
    int x = 0;
    for (int i = 1; i <= n; i++) {
      if (c[i] > c[x]) {
        x = i;
      }
    }
    return x;
  }

  void Delete(int x, vector<int> &v = l) {
    s++, d[x] = 1, v.push_back(x);
    for (int i = 1; i <= n; i++) {
      if (e[x][i] && !d[i]) {
        c[x]--, c[i]--;
      }
    }
  }

  void Undo(vector<int> &v = l) {
    int x = v.back();
    s--, d[x] = 0, v.pop_back();
    for (int i = 1; i <= n; i++) {
      if (e[x][i] && !d[i]) {
        c[x]++, c[i]++;
      }
    }
  }

  void Delete2(int x) {
    static vector<int> v;
    v.clear();
    for (int i = 1; i <= n; i++) {
      if (e[x][i] && !d[i]) {
        Delete(i, v);
      }
    }
    r.push_back(v);
  }

  void Undo2() {
    static vector<int> v;
    v.swap(r.back()), r.pop_back();
    for (; !v.empty(); Undo(v)) {
    }
  }

  void Print() {
    if (w > k) {
      cout << -1 << '\n';
    } else {
      int o = 0;
      for (int i = 1; i <= n; i++) {
        o += ans[i];
      }
      cout << w << ' ' << o << '\n';
      for (int i = 1; i <= n; i++) {
        if (ans[i]) {
          cout << i << ' ';
        }
      }
      cout << '\n';
    }
  }
} g;

void S() {
  if (g.Check()) {
    g.Update();
    return;
  } else if (g.Size() == k) {
    return;
  }
  int x = g.FindMax();
  g.Delete(x), S(), g.Undo();
  g.Delete2(x), S(), g.Undo2();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    g.Clear();
    cin >> n >> m >> k;
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      g.AddEdge(x, y);
    }
    S(), g.Print();
  }
  return 0;
}
