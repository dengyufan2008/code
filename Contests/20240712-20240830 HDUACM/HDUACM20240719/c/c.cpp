#include <fstream>
#include <map>
#include <vector>
#define ULL unsigned long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 5e5 + 1;
struct V {
  int w, p;
  ULL s;
  vector<int> e;
} v[kMaxN];
struct D {
  int l, r, c;
  ULL s, ans;
} d[kMaxN * 21];
int n, k;
ULL ans, a[kMaxN];
map<pair<int, int>, int> s;

void Pushup(int p) {
  d[p].c = d[d[p].l].c + d[d[p].r].c;
  d[p].s = d[d[p].l].s + d[d[p].r].s;
  d[p].ans = d[d[p].l].ans + d[d[p].r].ans + d[d[p].l].c * d[d[p].r].s * 2;
}

void Set(int &p, int l, int r, int x) {
  p = ++k;
  if (l == r) {
    d[p].c = 1, d[p].s = d[p].ans = a[x] * a[x];
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Set(d[p].l, l, mid, x);
  } else {
    Set(d[p].r, mid + 1, r, x);
  }
  Pushup(p);
}

void Merge(int &p, int q, int l, int r) {
  if (!p || !q) {
    p |= q;
    return;
  }
  int mid = l + r >> 1;
  Merge(d[p].l, d[q].l, l, mid);
  Merge(d[p].r, d[q].r, mid + 1, r);
  Pushup(p);
}

void T(int f, int x) {
  v[x].s = v[x].w, Set(v[x].p, 1, n, s[{v[x].w, x}]);
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].s += v[i].s;
      Merge(v[x].p, v[i].p, 1, n);
    }
  }
  ans ^= d[v[x].p].ans - v[x].s * v[x].s;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w, s[{v[i].w, i}] = 0;
  }
  for (auto &i : s) {
    static int j = 0;
    i.second = ++j, a[j] = i.first.first;
  }
  T(0, 1), cout << ans << '\n';
  return 0;
}
