#include <queue>

#include "tree.h"

using namespace std;

const int kMaxN = 1e5 + 1;
struct V {
  int s, l;
  vector<int> e;
} v[kMaxN];
struct G {
  int l, r, s;
} g[kMaxN << 1];
int n, m, k;
vector<int> l[kMaxN];

void Init(int x) {
  v[x].s = 1;
  if (v[x].e.empty()) {
    v[x].l = g[x].s = 1;
    return;
  }
  for (int &i : v[x].e) {
    Init(i), v[x].s += v[i].s;
    if (v[v[x].e[0]].s < v[i].s) {
      swap(v[x].e[0], i);
    }
  }
  v[x].l = v[v[x].e[0]].l + 1;
  g[x].s = v[x].s;
}

void PushTree(int x) {
  push(x);
  for (int i : v[x].e) {
    PushTree(i);
  }
}

void PushChain(int x) {
  for (int i = x;; i = v[i].e[0]) {
    push(i);
    if (v[i].e.empty()) {
      break;
    }
  }
}

void Pop(int x) {
  for (int i = 1; i <= x; i++) {
    pop();
  }
}

void SolveChain(int x, bool o) {
  check(x);
  if (v[x].e.empty()) {
    return;
  }
  push(x);
  for (int i : v[x].e) {
    if (i != v[x].e[0]) {
      PushTree(i);
    }
  }
  SolveChain(v[x].e[0], 1);
  for (int i : v[x].e) {
    if (i != v[x].e[0]) {
      Pop(v[i].s);
    }
  }
  if (o) {
    pop();
  }
}

void Do(int x);

void Push(int x) {
  if (x <= n) {
    PushTree(x);
  } else {
    Push(g[x].l), Push(g[x].r);
  }
}

void Divide(int x) {
  if (x <= n) {
    Do(x);
  } else {
    Push(g[x].r), Divide(g[x].l), Pop(g[g[x].r].s);
    Push(g[x].l), Divide(g[x].r), Pop(g[g[x].l].s);
  }
}

void DoDivide(vector<int> &l) {
  static priority_queue<pair<int, int>> q;
  if (l.size() == 1) {
    return Do(l[0]);
  }
  for (int i : l) {
    q.push({-g[i].s, i});
  }
  for (int i = 1; i < l.size(); i++) {
    int x = q.top().second;
    q.pop();
    int y = q.top().second;
    q.pop();
    g[++k] = {x, y, g[x].s + g[y].s};
    q.push({-g[k].s, k});
  }
  q.pop(), Divide(k), k -= l.size() - 1;
}

void Do(int x) {
  if (v[x].e.empty()) {
    return check(x);
  }
  SolveChain(x, 0), l[++m].clear();
  for (int i = x; !v[i].e.empty(); i = v[i].e[0]) {
    for (int j : v[i].e) {
      if (j != v[i].e[0]) {
        l[m].push_back(j);
      }
    }
  }
  if (!l[m].empty()) {
    PushChain(v[x].e[0]);
    DoDivide(l[m]);
    Pop(v[x].l);
  } else {
    pop();
  }
}

void solve(int N, vector<int> P) {
  n = k = N, m = 0, fill(&v[1], &v[n] + 1, v[0]);
  for (int i = 2; i <= n; i++) {
    v[P[i - 2]].e.push_back(i);
  }
  Init(1), Do(1);
}
