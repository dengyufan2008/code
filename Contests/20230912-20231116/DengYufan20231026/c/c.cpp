#include "C.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solve {
 private:
  int n, p = -1, q;
  vector<int> a, gap, ans, d[2][8];

  vector<int> Ask(int x, bool o, int y, bool b) {
    vector<int> w;
    for (int i = 0; i <= y; i++) {
      if (i == p && b || i != p && (i >> x & 1) == o) {
        w.push_back(i);
      }
    }
    vector<int> v = qry2(w);
    sort(v.begin(), v.end());
    return v;
  }

  void FindVal() {
    a = Ask(114, 0, n - 1, 0);
    int l = 1, r = n - 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Ask(114, 0, mid, 0).back() < a.back()) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    p = l, q = qry1(p);
  }

  void FindGap() {
    vector<int> w = Ask(114, 0, n - 1, 0), _w, v;
    for (int i : w) {
      auto t = lower_bound(a.begin(), a.end(), i);
      a.erase(t);
    }
    for (int i = 0; i <= 7; i++) {
      d[0][i] = a, d[1][i] = Ask(i, 1, n - 1, 1);
      w = Ask(i, 1, n - 1, 0);
      for (int j : w) {
        auto t = lower_bound(d[1][i].begin(), d[1][i].end(), j);
        d[1][i].erase(t);
      }
      for (int j : d[1][i]) {
        auto t = lower_bound(d[0][i].begin(), d[0][i].end(), j);
        d[0][i].erase(t);
      }
    }
    for (int i = 0; i < n; i++) {
      if (i != p) {
        w = a;
        for (int j = 0; j <= 7; j++) {
          v = d[i >> j & 1][j];
          for (int k : w) {
            auto t = lower_bound(v.begin(), v.end(), k);
            if (t != v.end() && *t == k) {
              _w.push_back(k), v.erase(t);
            }
          }
          w = _w, _w.clear();
        }
        gap.push_back(w[0]);
      } else {
        gap.push_back(0);
      }
    }
  }

  void FindAns() {
    int mx = 0;
    for (int i = 1; i < n; i++) {
      if (gap[i] > gap[mx]) {
        mx = i;
      }
    }
    int q2 = qry1(mx);
    for (int i = 0; i < n; i++) {
      ans.push_back(q2 < q ? q - gap[i] : q + gap[i]);
    }
    answer(ans);
  }

 public:
  void Find(int _n) {
    n = _n, FindVal(), FindGap(), FindAns();
  }
} solve;

void find(int n, int M1, int M2) {
  solve.Find(n);
}
// g++ c.cpp grader.cpp -o c
