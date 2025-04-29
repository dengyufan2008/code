#include <algorithm>
#include <vector>

#include "coins.h"
#define LL long long

using namespace std;

const int kMaxN = 1e6 + 1;
int n;
pair<int, int> a[kMaxN];

int Pow(int x, int y) {
  int ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      if (1LL * ans * x >= n) {
        ans = n;
      } else {
        ans *= x;
      }
    }
    if (1LL * x * x >= n) {
      x = n;
    } else {
      x *= x;
    }
  }
  return ans;
}

bool Check(int x) {
  for (int i = 1, j = 1; i <= n; i = j) {
    for (; j <= n && a[i].first == a[j].first; j++) {
    }
    if (j - 1 > Pow(a[i].first + 1, x)) {
      return 0;
    }
  }
  return 1;
}

int Solve() {
  int l = 0, r = 20;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Check(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  // ans=l

  static vector<int> e;
  e.clear();
  for (int i = 1; i <= n; i++) {
    e.push_back(i);
  }
  for (int i = r, c; i >= 0; i--) {
    static vector<int> q, p[kMaxN];
    q.clear(), q.resize(n), c = 0;
    LL w = 0;
    for (int j : e) {
      int y = Pow(a[j].first + 1, i);
      int ll = 0, rr = c - 1;
      while (ll <= rr) {
        int mid = ll + rr >> 1;
        if (p[mid].size() < y) {
          rr = mid - 1;
        } else {
          ll = mid + 1;
        }
      }
      p[ll].push_back(j), q[a[j].second] = ll;
      w -= ll * 5LL, c += ll == c;
    }
    w += weigh(q), e.swap(p[w]);
    for (int j = 0; j < c; j++) {
      p[j].clear();
    }
  }
  return a[e[0]].second;
}

int solve(vector<int> _a) {
  n = _a.size();
  for (int i = 1; i <= n; i++) {
    a[i] = {_a[i - 1], i - 1};
  }
  sort(a + 1, a + n + 1);
  return Solve();
}
