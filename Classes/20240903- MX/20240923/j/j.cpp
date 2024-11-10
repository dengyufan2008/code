#include <fstream>
#include <vector>

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 1001;
int n, m, k;
pair<int, int> p[kMaxN], a[kMaxN * kMaxN];
class G {
  int s, w, c[kMaxN];
  bool d[kMaxN], b[kMaxN], t[kMaxN], ans[kMaxN];
  vector<int> l, e[kMaxN];
  vector<vector<int>> r;

  int T(int x, bool u) {
    if (b[x]) {
      return 0;
    }
    int o = b[x] = 1;
    t[x] = u;
    for (int i : e[x]) {
      if (c[i]) {
        o += T(i, !u);
      }
    }
    return o;
  }

 public:
  void Clear() {
    w = kMaxN, l.clear();
    for (int i = 1; i <= n; i++) {
      c[i] = d[i] = ans[i] = 0, e[i].clear();
    }
  }

  void AddEdge() {
    for (int i = 1; i <= m; i++) {
      int x = a[i].first, y = a[i].second;
      e[x].push_back(y), e[y].push_back(x);
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
        o += T(i, 0) >> 1;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (!b[i] && c[i] == 2) {
        o += T(i, 0) + 1 >> 1;
      }
    }
    if (o < w) {
      w = o;
      for (int i = 1; i <= n; i++) {
        ans[i] = t[i] || d[i];
      }
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

  void Delete(int x) {
    s++, d[x] = 1, l.push_back(x);
    for (int i : e[x]) {
      if (!d[i]) {
        c[x]--, c[i]--;
      }
    }
  }

  void Undo() {
    int x = l.back();
    s--, d[x] = 0, l.pop_back();
    for (int i : e[x]) {
      if (!d[i]) {
        c[x]++, c[i]++;
      }
    }
  }

  void Delete2(int x) {
    static vector<int> v;
    v.clear(), v.swap(l);
    for (int i : e[x]) {
      if (!d[i]) {
        Delete(i);
      }
    }
    v.swap(l), r.push_back(v);
  }

  void Undo2() {
    static vector<int> v;
    v.swap(r.back()), r.pop_back();
    for (v.swap(l); !l.empty(); Undo()) {
    }
    v.swap(l);
  }

  bool Valid() { return w <= k; }

  bool Print() {
    int o = 0;
    for (int i = 1; i <= n; i++) {
      o += ans[i];
    }
    for (int i = 1; i <= n && o < k; i++) {
      if (!ans[i]) {
        ans[i] = 1, o++;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (ans[i]) {
        cout << i << ' ';
      }
    }
    cout << '\n';
    return 0;
  }
} g;

void S() {
  if (g.Check()) {
    g.Update();
    return;
  } else if (g.Size() >= k) {
    return;
  }
  int x = g.FindMax();
  g.Delete(x), S(), g.Undo();
  g.Delete2(x), S(), g.Undo2();
}

long long Dis(pair<int, int> x, pair<int, int> y) {
  return 1LL * (x.first - y.first) * (x.first - y.first) +
         1LL * (x.second - y.second) * (x.second - y.second);
}

bool C(int x, bool o) {
  m = 0, g.Clear();
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (Dis(p[i], p[j]) > x) {
        a[++m] = {i, j};
      }
    }
  }
  g.AddEdge(), S();
  return o ? g.Print() : g.Valid();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].first >> p[i].second;
  }
  int l = 0, r = INT_MAX;
  while (l <= r) {
    int mid = l + r >> 1;
    if (C(mid, 0)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  C(l, 1);
  return 0;
}
