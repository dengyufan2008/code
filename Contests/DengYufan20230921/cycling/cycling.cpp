#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("cycling.in");
ofstream cout("cycling.out");

const int kMaxN = 1e5 + 1;
struct V {
  int l;
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m, l, r, mid, ans;
vector<int> t;

int M(int x) {
  int c = 0;
  for (int i = 0, j = t.size() - 1; i < j; j--) {
    for (; i < j && (t[i] + t[j] < mid || i == x); i++) {
    }
    if (j != x) {
      c += i < j, i++;
    }
  }
  return c;
}

void T(int f, int x) {
  for (auto i : v[x].e) {
    if (i.first != f) {
      T(x, i.first);
    }
  }
  t.clear();
  for (auto i : v[x].e) {
    if (i.first != f) {
      t.push_back(v[i.first].l + i.second);
    }
  }
  sort(t.begin(), t.end());
  for (; !t.empty() && t.back() >= mid; t.pop_back()) {
    ans++;
  }
  int c = M(-1), l = 0, r = t.size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (M(mid) == c) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  ans += c, v[x].l = r < 0 ? 0 : t[r];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  l = 1, r = 5e7;
  while (l <= r) {
    mid = l + r >> 1, ans = 0, T(0, 1);
    if (ans >= m) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << r;
  return 0;
}
