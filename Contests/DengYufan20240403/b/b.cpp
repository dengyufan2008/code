#include <algorithm>
#include <ctime>
#include <fstream>
#include <queue>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5e5 + 1, kInf = 1e9;
int n, s, t, b[kMaxN], c[kMaxN];
vector<int> a[kMaxN], d[kMaxN];
struct F {
  struct E {
    int p, d, w;
  } e[kMaxN * 4];
  struct V {
    int d, et, nt;
  } v[kMaxN];
  int k = 1;
  bool b[kMaxN];
  vector<int> l;
  queue<int> q;

  void Clear() {
    for (int i : l) {
      v[i].et = 0, b[i] = 0;
    }
    k = 1, l.clear();
  }

  void AddEdge(int x, int y, int w) {
    e[++k] = {v[x].et, y, w}, v[x].et = k;
    e[++k] = {v[y].et, x, 0}, v[y].et = k;
    if (!b[x]) {
      b[x] = 1, l.push_back(x);
    }
    if (!b[y]) {
      b[y] = 1, l.push_back(y);
    }
  }

  bool Bfs() {
    for (int i : l) {
      v[i].d = i == n + t + 1, v[i].nt = v[i].et;
    }
    for (q.push(n + t + 1); !q.empty(); q.pop()) {
      for (int i = v[q.front()].et; i; i = e[i].p) {
        if (e[i].w && !v[e[i].d].d) {
          v[e[i].d].d = v[q.front()].d + 1;
          q.push(e[i].d);
        }
      }
    }
    return v[n + t + 2].d;
  }

  int Dfs(int x, int in) {
    if (x == n + t + 2) {
      return in;
    }
    int out = 0;
    for (int &i = v[x].nt; i && in; in && (i = e[i].p)) {
      if (e[i].w && v[e[i].d].d == v[x].d + 1) {
        int t = Dfs(e[i].d, min(in, e[i].w));
        e[i].w -= t, e[i ^ 1].w += t;
        in -= t, out += t;
      }
    }
    return out;
  }

  int Flow() {
    int ans = 0;
    for (; Bfs(); ans += Dfs(n + t + 1, kInf)) {
      ans++, ans--;
    }
    return ans;
  }
} f;

void Solve(int l, int r) {
  if (l == r) {
    return;
  }
  static int o = 0;
  int w = 0;
  o++, f.Clear();
  for (int i = 1; i <= n; i++) {
    f.AddEdge(n + t + 1, i, r - l + 1 >> 1);
    for (int j = l, k = l; j <= r; j = k) {
      for (; k <= r && a[i][j] == a[i][k]; k++) {
      }
      f.AddEdge(i, n + a[i][j], k - j);
      if (b[a[i][j]] != o) {
        b[a[i][j]] = o, c[a[i][j]] = k - j;
      } else {
        c[a[i][j]] += k - j;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = l; j <= r; j++) {
      if (b[a[i][j]] == o) {
        b[a[i][j]] = -o, w += c[a[i][j]] & 1;
        f.AddEdge(n + a[i][j], n + t + 2, c[a[i][j]] >> 1);
      }
    }
  }
  w >>= 1, f.AddEdge(n + t + 3, n + t + 2, w);
  for (int i = 1; i <= n; i++) {
    for (int j = l; j <= r; j++) {
      if (b[a[i][j]] == -o) {
        b[a[i][j]] = o;
        if (c[a[i][j]] & 1) {
          f.AddEdge(n + a[i][j], n + t + 3, 1);
        }
      }
    }
  }
  f.Flow();
  for (int i = 1; i <= n; i++) {
    int u = l;
    for (int j = f.v[i].et; j; j = f.e[j].p) {
      if (f.e[j].d <= n + t) {
        for (int k = 1; k <= f.e[j ^ 1].w; k++) {
          d[i][u++] = f.e[j].d - n;
        }
      }
    }
    reverse(&d[i][l], &d[i][l + r >> 1] + 1);
    for (int j = l, k = l; j <= r; j++) {
      if (k > (l + r >> 1) || a[i][j] != d[i][k]) {
        d[i][u++] = a[i][j];
      } else {
        k++;
      }
    }
    a[i] = d[i];
  }
  Solve(l, l + r >> 1), Solve((l + r >> 1) + 1, r);
}

void Input() {
  cin >> n >> s >> t;
  for (int i = 1; i <= n; i++) {
    a[i].resize(s + 1), d[i].resize(s + 1);
    for (int j = 1; j <= s; j++) {
      cin >> a[i][j];
    }
    sort(&a[i][1], &a[i][s] + 1);
  }
}

void Print() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= s; j++) {
      cout << a[i][j] << " \n"[j == s];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Solve(1, s), Print();
  cout << clock() << '\n';
  return 0;
}
