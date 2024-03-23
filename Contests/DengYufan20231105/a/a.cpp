#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e5 + 1;
int n, m, k, a[kMaxN], l[kMaxN];
vector<int> v[kMaxN];
map<pair<int, int>, LL> ans;

int Find(int x) {
  int l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    if (a[mid] <= x) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return a[r] == x ? r : 0;
}

int Find(int x, int y) {
  int l = 0, r = v[x].size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (v[x][mid] <= y) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return v[x].size() - l;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  k = sqrt(n);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) { return a[i] < a[j] || a[i] == a[j] && i < j; });
  for (int i = 1, j, k = 0; i <= n; i = j) {
    v[++k].push_back(0);
    for (j = i; j <= n && a[l[i]] == a[l[j]]; j++) {
      v[k].push_back(l[j]);
    }
  }
  sort(a + 1, a + n + 1), n = unique(a + 1, a + n + 1) - a - 1;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    int p = Find(x), q = Find(y);
    if (!p || !q) {
      cout << 0 << '\n';
      continue;
    } else if (v[p].size() > k && v[q].size() > k) {
      auto t = ans.find({p, q});
      if (t != ans.end()) {
        cout << t->second << '\n';
      } else {
        LL w = 0;
        for (int j = 0, k = 0; j < v[p].size(); j++) {
          for (; k < v[q].size() && v[q][k] <= v[p][j]; k++) {
          }
          w = max(w, (LL)(v[q].size() - k) * j);
        }
        cout << (ans[{p, q}] = w) << '\n';
      }
      continue;
    } else if (v[p].size() <= v[q].size()) {
      LL w = 0;
      for (int j = 0; j < v[p].size(); j++) {
        w = max(w, 1LL * j * Find(q, v[p][j]));
      }
      cout << w << '\n';
    } else {
      LL w = 0;
      for (int j = 1; j < v[q].size(); j++) {
        w = max(w, (LL)(v[p].size() - Find(p, v[q][v[q].size() - j] - 1) - 1) * j);
      }
      cout << w << '\n';
    }
  }
  return 0;
}
