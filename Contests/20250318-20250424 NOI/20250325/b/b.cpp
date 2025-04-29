#include <vector>

#include "evolution2.h"

using namespace std;

const int kMaxN = 1e4;
struct V {
  vector<int> e, g;
} v[kMaxN];
int n;

bool Less(int x, int y) { return compare(x, y); }

void Merge(vector<int> &x, vector<int> &y) {
  static vector<int> d, ans;
  x.size() < y.size() ? swap(x, y) : void();
  int p = x.size(), q = y.size();
  if (p <= q << 1) {
    for (int i = 0, j = 0; i < p || j < q;) {
      if (i < p && (j == q || Less(x[i], y[j]))) {
        ans.push_back(x[i++]);
      } else {
        ans.push_back(y[j++]);
      }
    }
  } else {
    d.resize(q);
    for (int i = 0, j = 0; j < q;) {
      int t = min((1 << 32 - __builtin_clz((p - i - 1) / (q - j))) - 1, p - i);
      if (i + t == p || Less(y[j], x[i + t])) {
        int l = i, r = i + t - 1;
        while (l <= r) {
          int mid = l + r >> 1;
          if (Less(y[j], x[mid])) {
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        }
        i = d[j++] = l;
      } else {
        i += t + 1;
      }
    }
    for (int i = 0, j = 0; i < p || j < q;) {
      if (i < p && (j == q || d[j] > i)) {
        ans.push_back(x[i++]);
      } else {
        ans.push_back(y[j++]);
      }
    }
  }
  swap(x, ans), ans.clear(), y.clear(), y.shrink_to_fit();
}

void Divide(int x, int l, int r) {
  if (l < r) {
    int mid = l + r >> 1;
    Divide(x, l, mid), Divide(x, mid + 1, r);
    Merge(v[v[x].e[l]].g, v[v[x].e[mid + 1]].g);
  }
}

void Solve(int x) {
  if (v[x].e.empty()) {
    v[x].g.push_back(x);
    return;
  }
  for (int i : v[x].e) {
    Solve(i);
  }
  Divide(x, 0, v[x].e.size() - 1);
  v[x].g.push_back(x);
  v[x].g.insert(v[x].g.end(), v[v[x].e[0]].g.begin(), v[v[x].e[0]].g.end());
  v[v[x].e[0]].g.clear(), v[v[x].e[0]].g.shrink_to_fit();
}

vector<int> recover(int N, vector<int> U, vector<int> V) {
  static vector<int> ans;
  n = N, ans.resize(n);
  for (int i = 0; i < n; i++) {
    v[i].e.clear();
  }
  for (int i = 0; i + 1 < n; i++) {
    v[U[i]].e.push_back(V[i]);
  }
  Solve(0);
  for (int i = 0; i < n; i++) {
    ans[v[0].g[i]] = i;
  }
  return v[0].g.clear(), ans;
}
// g++ -std=c++14 -O2 b.cpp grader.cpp -o b && b
