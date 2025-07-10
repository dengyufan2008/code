#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2.4e6 + 3;
int t, u, n;
pair<int, int> a[kMaxN + 1 >> 1];

class Uni {
  int w, f[kMaxN], s[kMaxN], c[kMaxN];
  vector<pair<int, int>> l;

  int GetRoot(int x) {
    return f[x] == x ? x : GetRoot(f[x]);
  }

 public:
  void Init() {
    w = 0, l.clear();
    for (int i = 1; i <= n << 1; i++) {
      f[i] = i, s[i] = 1, c[i] = 0;
    }
  }

  void AddEdge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    s[x] < s[y] ? swap(x, y) : void();

    l.push_back({x, y});
    c[x]++, c[x] & 1 ? w++ : w--;
    if (x != y) {
      (c[x] & c[y] & 1) && (w -= 2);
      f[y] = x, s[x] += s[y], c[x] += c[y];
    }
  }

  void Undo() {
    int x = l.back().first, y = l.back().second;

    if (x != y) {
      f[y] = y, s[x] -= s[y], c[x] -= c[y];
      (c[x] & c[y] & 1) && (w += 2);
    }
    c[x]--, c[x] & 1 ? w++ : w--;
    l.pop_back();
  }

  bool Check() { return !w; }
} uni;

namespace Sub1 {
struct V {
  int r, p;
  bool b;
  vector<pair<int, int>> e;
} v[kMaxN];
int k;
vector<pair<int, int>> ans;

void S(int f, int x) {
  v[x].r = ++k;
  for (auto i : v[x].e) {
    if (i.second != f && v[i.first].r && v[i.first].r < v[x].r) {
      if (v[x].p) {
        ans.push_back({v[x].p, i.second});
        v[x].p = 0;
      } else {
        v[x].p = i.second;
      }
    }
  }
  for (auto i : v[x].e) {
    if (!v[i.first].r) {
      S(i.second, i.first);
      if (!v[i.first].b) {
        if (v[x].p) {
          ans.push_back({v[x].p, i.second});
          v[x].p = 0;
        } else {
          v[x].p = i.second;
        }
      }
    }
  }
  if (v[x].p) {
    ans.push_back({v[x].p, f});
    v[x].b = 1;
  }
}

void Solve() {
  uni.Init();
  for (int i = 1; i <= n; i++) {
    uni.AddEdge(a[i].first, a[i].second);
  }
  if (!uni.Check()) {
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
  ans.clear();
  for (int i = 1; i <= n << 1; i++) {
    v[i].r = v[i].p = v[i].b = 0, v[i].e.clear();
  }
  for (int i = 1; i <= n; i++) {
    v[a[i].first].e.push_back({a[i].second, i});
    v[a[i].second].e.push_back({a[i].first, i});
  }
  k = 0;
  for (int i = 1; i <= n << 1; i++) {
    !v[i].r ? S(0, i) : void();
  }
  for (auto i : ans) {
    cout << i.first << ' ' << i.second << '\n';
  }
}
}  // namespace Sub1

namespace Sub2 {
void Divide(int l, int r) {
  if (l == r) {
    cout << (uni.Check() ? "Yes\n" : "No\n");
    return;
  }
  int mid = l + r >> 1;

  for (int i = mid + 1; i <= r; i++) {
    uni.AddEdge(a[i].first, a[i].second);
  }
  Divide(l, mid);
  for (int i = mid + 1; i <= r; i++) {
    uni.Undo();
  }

  for (int i = l; i <= mid; i++) {
    uni.AddEdge(a[i].first, a[i].second);
  }
  Divide(mid + 1, r);
  for (int i = l; i <= mid; i++) {
    uni.Undo();
  }
}

void Solve() {
  uni.Init(), Divide(1, n);
}
}  // namespace Sub2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> u;
  while (t--) {
    cin >> n, n = n << 1 | u - 1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
      a[i].second += n;
    }
    if (u == 1) {
      Sub1::Solve();
    } else {
      Sub2::Solve();
    }
  }
  return 0;
}
