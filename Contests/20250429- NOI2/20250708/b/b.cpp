#include <iostream>

#include "perm.h"

using namespace std;

const int kMaxN = 1e5 + 1;
int n;
vector<int> e[kMaxN];

void Solve1() {
  static vector<int> q;
  static vector<bool> a;
  for (int i = 1; i <= n; i++) {
    q.push_back(i);
    for (int j = 1; j <= n; j++) {
      if (j != i) {
        q.push_back(j), q.push_back(j);
      }
    }
    q.push_back(i);
  }
  a = query(q);
  for (int i = 1, c = 0; i <= n; i++) {
    c++;
    for (int j = 1; j <= n; j++) {
      if (j != i) {
        if (a[c]) {
          e[i].push_back(j);
        }
        c += 2;
      }
    }
    c++;
  }
}

int c[kMaxN];

bool Q(int x) {
  c[x]++;
  return query({x}).front();
}

void Q(int l, int r) {
  static vector<int> v;
  v.clear();
  for (int i = l; i <= r; i++) {
    c[i]++;
    v.push_back(i);
  }
  query(v);
}

void Solve2() {
  static vector<pair<int, int>> v;
  for (int i = 1, j = 0; i <= n; i = j) {
    for (j++; j <= n && !Q(j); j++) {
    }
    v.push_back({i, j - 1}), Q(i, j - 1);
  }
  for (int i = 0; i < v.size(); i++) {
    Q(v[i].first, v[i].second);
    for (int j = v[i].second + 1; j <= n; j++) {
      if (Q(j)) {
        static int k;
        for (k = v[i].first; k <= v[i].second && Q(k); k++) {
        }
        e[j].push_back(k), e[k].push_back(j);
        for (int l = k - 1, u = 0; l >= v[i].first; l--) {
          if (Q(l) && !u) {
            u = 1, e[j].push_back(l), e[l].push_back(j);
          }
        }
        Q(k);
      }
      Q(j);
    }
    Q(v[i].first, v[i].second);
  }
}

vector<int> solve(int _n, int subtask) {
  n = _n;
  if (subtask == 1) {
    Solve1();
  } else {
    Solve2();
  }
  static vector<int> ans;
  ans.push_back(1), ans.push_back(e[1].front());
  for (int i = e[1].front(), p = 1;;) {
    swap(i, p), i ^= e[p].front() ^ e[p].back();
    if (i != 1) {
      ans.push_back(i);
    } else {
      break;
    }
  }
  return ans;
}
