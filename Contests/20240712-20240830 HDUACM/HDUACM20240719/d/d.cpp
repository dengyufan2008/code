#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 6e5 + 1;
struct V {
  int f, s;
  LL t, ans;
} v[kMaxN];
int n, m;
LL ans;
vector<pair<int, int>> e[kMaxN << 2];
vector<pair<int, int>> l;

int GetRoot(int x) { return v[x].f == x ? x : GetRoot(v[x].f); }
LL GetTag(int x) { return v[x].f == x ? v[x].t : v[x].t + GetTag(v[x].f); }
void Tag(int x, LL y) { v[x].t += y, v[x].ans += y; }

void Merge(int x, int y) {
  x = GetRoot(x), y = GetRoot(y);
  if (x != y) {
    v[x].s > v[y].s ? swap(x, y) : void();
    v[x].f = y, v[y].s += v[x].s, Tag(x, -GetTag(y));
    l.push_back({x, y});
  } else {
    l.push_back({0, 0});
  }
}

void Undo() {
  auto x = l.back().first, y = l.back().second;
  l.pop_back();
  if (x || y) {
    v[x].f = x, v[y].s -= v[x].s, Tag(x, GetTag(y));
  }
}

void Add(int p, int l, int r, int _l, int _r, pair<int, int> x) {
  if (l >= _l && r <= _r) {
    return e[p].push_back(x);
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, x);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, x);
  }
}

void Calc(int p, int l, int r) {
  for (auto i : e[p]) {
    Merge(i.first, i.second);
  }
  if (l == r) {
    Tag(GetRoot(1), l);
  } else {
    int mid = l + r >> 1;
    Calc(p << 1, l, mid), Calc(p << 1 | 1, mid + 1, r);
  }
  for (auto i : e[p]) {
    Undo();
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, l, r; i <= m; i++) {
    cin >> x >> y >> l >> r;
    Add(1, 1, n, l, r, {x, y});
  }
  for (int i = 1; i <= n; i++) {
    v[i].f = i, v[i].s = 1;
  }
  Calc(1, 1, n);
  for (int i = 1; i <= n; i++) {
    ans ^= v[i].ans;
  }
  cout << ans << '\n';
  return 0;
}
