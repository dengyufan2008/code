#include <bitset>
#include <fstream>

using namespace std;

ifstream cin("maze.in");
ofstream cout("maze.out");

const int kMaxN = 503, kMaxM = 1e5 + 1;
int n, m, q;

class Flow {
  int ans, p[kMaxN], e[kMaxN][kMaxN];
  bitset<kMaxN> in[kMaxN], out[kMaxN];

  void AddE(int x, int y) {
    if (!e[x][y]) {
      in[y].set(x);
      out[x].set(y);
    }
    e[x][y]++;
  }

  void DelE(int x, int y) {
    e[x][y]--;
    if (!e[x][y]) {
      in[y].reset(x);
      out[x].reset(y);
    }
  }

  bool FindPath(int s, bool o) {  // reverse or not
    static int q[kMaxN];
    static bitset<kMaxN> _p;
    fill(&p[1], &p[n + 1] + 1, 0), _p.set();
    p[s] = s, _p.reset(s), q[1] = s;
    int target = 1;
    for (int i = 2; i <= n; i++) {
      if ((e[target][n + 1] > e[i][n + 1]) == o) {
        target = i;
      }
    }
    if (o && !e[n + 1][target] || !o && !e[target][n + 1]) {
      return 0;
    }
    for (int h = 1, t = 1, x; h <= t && !p[target]; h++) {
      static bitset<kMaxN> tmp;
      x = q[h], tmp = _p & (o ? in[x] : out[x]);
      for (int i = tmp._Find_first(); i < kMaxN; i = tmp._Find_next(i)) {
        p[i] = x, _p.reset(i), q[++t] = i;
      }
    }
    return p[n + 1] || p[target];
  }

  void CheckAns() {
    for (int i = 1; i <= n; i++) {
      if (!e[i][n + 1]) {
        return;
      }
    }
    ans--;
    for (int i = 1; i <= n; i++) {
      DelE(i, n + 1);
    }
  }

 public:
  void Add1(int x) {
    if (FindPath(x, 0)) {
      int z = 0;
      for (int i = 1; i <= n; i++) {
        if (p[i] && (!z || e[z][n + 1] <= e[i][n + 1])) {
          z = i;
        }
      }
      DelE(z, n + 1), AddE(n + 1, z);
      for (int i = z; i != x; i = p[i]) {
        DelE(p[i], i), AddE(i, p[i]);
      }
    } else {
      ans++;
      for (int i = 1; i <= n; i++) {
        AddE(i, n + 1);
      }
      DelE(x, n + 1), AddE(n + 1, x);
    }
  }

  void Del1(int x) {
    int z = 0;
    FindPath(x, 1);
    for (int i = 1; i <= n; i++) {
      if (p[i] && (!z || e[z][n + 1] > e[i][n + 1])) {
        z = i;
      }
    }
    AddE(z, n + 1), DelE(n + 1, z);
    for (int i = z; i != x; i = p[i]) {
      AddE(p[i], i), DelE(i, p[i]);
    }
    CheckAns();
  }

  void Add2(int x, int y) {
    x > y ? swap(x, y) : void();
    AddE(x, y), Add1(x);
  }

  void Del2(int x, int y) {
    x > y ? swap(x, y) : void();
    if (e[x][y]) {
      DelE(x, y), Del1(x);
    } else {
      int z = 0;
      FindPath(y, 1);
      for (int i = 1; i <= n; i++) {
        if (p[i] && (!z || e[z][n + 1] > e[i][n + 1])) {
          z = i;
        }
      }
      AddE(z, n + 1), DelE(n + 1, z);
      for (int i = z; i != y; i = p[i]) {
        AddE(p[i], i), DelE(i, p[i]);
      }
      DelE(y, x), CheckAns();
    }
  }

  int Ask() { return ans; }
} flow;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1, x; i <= n; i++) {
    for (cin >> x; x; x--) {
      flow.Add1(i);
    }
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, flow.Add2(x, y);
  }
  cout << flow.Ask() << '\n';
  for (int i = 1, o, x, y; i <= q; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> y, flow.Add2(x, y);
    } else if (o == 2) {
      cin >> y, flow.Del2(x, y);
    } else if (o == 3) {
      flow.Add1(x);
    } else {
      flow.Del1(x);
    }
    cout << flow.Ask() << '\n';
  }
  return 0;
}
