#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 1e6 + 2, kInf = 2e9;
struct E {
  int a, b, x, y, z;
} e[kMaxN];
struct D {
  int f, s, c;
} d[kMaxN];
int t, n, m, k, o[kMaxN], v[kMaxN];
vector<int> q[kMaxN][3], ans;

int Find(int w) {
  int l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    if (v[o[mid]] <= w) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

int GetRoot(int x) {
  return d[x].f == x ? x : d[x].f = GetRoot(d[x].f);
}

void Tag(int x, bool c) {
  x = GetRoot(x);
  if (c) {
    d[x].c++, k -= d[x].s == d[x].c;
  } else {
    k += d[x].s == d[x].c, d[x].c--;
  }
}

void AddEdge(int x, int y) {
  x = GetRoot(x), y = GetRoot(y);
  if (x != y) {
    k -= d[x].s > d[x].c;
    k -= d[y].s > d[y].c;
    d[x].f = y, d[y].s += d[x].s;
    d[y].c += d[x].c + 1;
    k += d[y].s > d[y].c;
  } else {
    Tag(x, 1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m, k = n, ans.clear();
    for (int i = 1; i <= n; i++) {
      v[i] = kInf, o[i] = i, d[i] = {i, 1, 0};
      q[i][0].clear(), q[i][1].clear(), q[i][2].clear();
    }
    for (int i = 1, a, b, x, y, z; i <= m; i++) {
      cin >> a >> b >> x >> y >> z;
      x > y ? swap(a, b), swap(x, y) : void();
      v[a] = min(v[a], x + z), v[b] = min(v[b], y + z);
      e[i] = {a, b, x, y, z};
    }
    sort(o + 1, o + n + 1, [](int i, int j) { return v[i] < v[j]; });
    for (int i = 1, x, y; i <= m; i++) {
      x = Find(e[i].x), q[x][0].push_back(i);
      x = Find(e[i].y), q[x][1].push_back(i);
      y = Find(1LL + e[i].x + e[i].y + e[i].z >> 1);
      q[max(x, y)][2].push_back(i);
    }
    for (int u = 1, i = o[1]; u <= n; i = o[++u]) {
      for (int j : q[u][0]) {
        Tag(e[j].a, 1);
      }
      for (int j : q[u][1]) {
        Tag(e[j].a, 0), AddEdge(e[j].a, e[j].b);
      }
      for (int j : q[u][2]) {
        Tag(e[j].a, 1), Tag(e[j].b, 1);
      }
      Tag(i, 1);
      !k ? ans.push_back(i) : void();
      Tag(i, 0);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int i : ans) {
      cout << i << ' ';
    }
    cout << '\n';
  }
  return 0;
}
