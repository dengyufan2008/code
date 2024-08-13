#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
struct A {
  LL x, y;
  A operator+(A a) {
    return {x + a.x, y + a.y};
  }
  LL operator*(A a) {
    return x * a.y;
  }
  const bool operator<(const A &a) const {
    return y * a.x < x * a.y;
  }
} a[kMaxN];
struct V {
  A a;
  LL ans;
} v[kMaxN << 3];
int o, n;
LL ans, w[kMaxN];
vector<pair<A, int>> l;
vector<pair<A, pair<int, int>>> t;
vector<pair<int, bool>> q[kMaxN];

void Init(int p, int l, int r) {
  v[p] = {{0, 0}, 0};
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
}

void Change(int p, int l, int r, int x, bool o) {
  if (l == r) {
    v[p].a = o ? t[x].first : (A){0, 0};
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, o);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, o);
  }
  v[p].a = v[p << 1].a + v[p << 1 | 1].a;
  v[p].ans = v[p << 1].ans + v[p << 1 | 1].ans;
  v[p].ans += v[p << 1].a * v[p << 1 | 1].a;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y;
      if (!a[i].x && !a[i].y) {
        i--, n--;
      } else {
        w[0] += a[i].x * a[i].y;
      }
    }
    for (int i = 1; i <= n; i++) {
      A o = a[i];
      for (; !l.empty() && !(l.back().first < o); l.pop_back()) {
        w[i] += l.back().first * o;
        o = l.back().first + o;
        t.push_back({l.back().first, {l.back().second, i - 1}});
      }
      l.push_back({o, i});
    }
    for (; !l.empty(); l.pop_back()) {
      t.push_back({l.back().first, {l.back().second, n}});
    }
    for (int i = n; i >= 1; i--) {
      A o = a[i];
      for (; !l.empty() && !(l.back().first < o); l.pop_back()) {
        w[0] += l.back().first * o;
        w[i] -= l.back().first * o;
        o = l.back().first + o;
        t.push_back({l.back().first, {i, l.back().second}});
      }
      l.push_back({o, i - 1});
    }
    for (; !l.empty(); l.pop_back()) {
      t.push_back({l.back().first, {0, l.back().second}});
    }
    sort(t.begin(), t.end());
    for (int i = 0; i < t.size(); i++) {
      q[t[i].second.first].push_back({i, 1});
      if (t[i].second.second < n) {
        q[t[i].second.second + 1].push_back({i, 0});
      }
    }
    Init(1, 0, t.size() - 1);
    for (int i = 0; i <= n; i++) {
      i && (w[i] += w[i - 1], w[i - 1] = 0);
      for (auto j : q[i]) {
        Change(1, 0, t.size() - 1, j.first, j.second);
      }
      ans = max(ans, w[i] + v[1].ans), q[i].clear();
    }
    cout << ans << '\n', ans = w[n] = 0, t.clear();
  }
  return 0;
}
