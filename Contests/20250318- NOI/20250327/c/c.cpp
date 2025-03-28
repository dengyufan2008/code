#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include <vector>

#include "memory.h"

using namespace std;

const int kMaxN = 1e5 + 1, kMaxM = 5e4 + 1;
int u[kMaxM];
struct S {
  int x, c, d;
  bool operator<(const S &s) const {
    if (c != s.c) {
      return c > s.c;
    } else if (d != s.d) {
      return d < s.d;
    }
    return u[x] < u[s.x];
  }
};
struct V {
  pair<int, int> a, p;
} v[kMaxM], _v[kMaxM];
int n, m, d[kMaxM], ans[kMaxN];
vector<int> e[kMaxM];
set<S> s;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

pair<int, int> Look(int x, int y) { return look(x, y); }

void SolveXYXY(int a, int b, int c, int d, int x, int y) {  // 期望 2 次
  auto t = Look(a, c);
  for (; t.first != t.second; t = Look(a, c)) {
    swap(b, c);
    if (Rand() & 1) {
      swap(a, b);
    }
    if (Rand() & 1) {
      swap(c, d);
    }
  }
  ans[a] = ans[c] = t.first, ans[b] = ans[d] = x ^ y ^ t.first;
}

int SolveXYXZ(int &a, int &b, int &c, int &d, int x, int y, int z) {  // 1 次
  auto t = Look(a, c);
  if (t.first == x && t.second == x) {
    ans[a] = ans[c] = x, ans[b] = y, ans[d] = z;
    return 0;
  } else if (t.first != x && t.second != x) {
    swap(a, b), swap(c, d), ans[a] = ans[c] = x;
    return 1;
  }
  int w = x ^ t.first ^ t.second;
  if (w == y) {  // 以前是 y x x z, 现在是 [x, y] x z
    swap(b, c);
    ans[c] = x, ans[d] = z;
    return 2;
  } else {  // 以前是 x y z x, 现在是 [x, z] x y
    swap(b, c), swap(c, d);
    ans[c] = x, ans[d] = y;
    return 3;
  }
}

void SolveXXY(int &a, int &b, int &c, int x, int y) {  // 期望 2 次
  auto t = Look(a, c);
  for (; t.first != t.second; t = Look(a, c)) {
    swap(a, b);
    if (Rand() & 1) {
      swap(b, c);
    }
  }
  ans[a] = ans[c] = x, ans[b] = y;
}

void SolveXYZW(int a, int b, int c, int d, int &x, int &y, int &z, int &w) {  // 1 次
  auto t = Look(a, c);
  if (t.first == y || t.second == y) {
    swap(x, y);
  }
  if (t.first == w || t.second == w) {
    swap(z, w);
  }
  ans[b] = y, ans[d] = w;
}

void CalcD(int x, int t) {
  if (!t) {
    return;
  }
  s.erase({x, (int)e[x].size(), d[x]});
  d[x] = 0;
  for (int i : e[x]) {
    int y = x ^ v[i].a.first ^ v[i].a.second;
    d[x] += e[y].size(), CalcD(y, t - 1);
  }
  s.insert({x, (int)e[x].size(), d[x]});
}

void Insert(int x) {
  int w1 = v[x].a.first, w2 = v[x].a.second;
  s.erase({w1, (int)e[w1].size(), d[w1]});
  s.erase({w2, (int)e[w2].size(), d[w2]});
  e[w1].push_back(x), e[w2].push_back(x);
  s.insert({w1, (int)e[w1].size(), d[w1]});
  s.insert({w2, (int)e[w2].size(), d[w2]});
  CalcD(w1, 2), CalcD(w2, 2);
}

void Delete(int x) {
  int w1 = v[x].a.first, w2 = v[x].a.second;
  s.erase({w1, (int)e[w1].size(), d[w1]});
  s.erase({w2, (int)e[w2].size(), d[w2]});
  for (int i : {w1, w2}) {
    for (int j = 0; j < e[i].size(); j++) {
      if (e[i][j] == x) {
        e[i].erase(e[i].begin() + j);
        break;
      }
    }
  }
  s.insert({w1, (int)e[w1].size(), d[w1]});
  s.insert({w2, (int)e[w2].size(), d[w2]});
  CalcD(w1, 2), CalcD(w2, 2);
}

void Calc1() {
  for (int i = 1; i <= n >> 1; i++) {
    s.insert({i, 0, 0});
  }
  for (int i = 1; i <= n >> 1; i++) {
    if (v[i].a.first == v[i].a.second) {
      ans[v[i].p.first] = ans[v[i].p.second] = v[i].a.first;
    } else {
      Insert(i);
    }
  }
  while (!s.empty() && s.begin()->c == 2) {
    int i = s.begin()->x, x = e[i][0], y = e[i][1];
    v[x].a.first == i ? swap(v[x].a.first, v[x].a.second) : void();
    v[y].a.first == i ? swap(v[y].a.first, v[y].a.second) : void();
    Delete(x), Delete(y);
    if (v[x].a.first == v[y].a.first) {
      SolveXYXY(v[x].p.first, v[x].p.second, v[y].p.first, v[y].p.second, i, v[x].a.first);
      continue;
    }
    int t = SolveXYXZ(v[x].p.first, v[x].p.second, v[y].p.first, v[y].p.second, i, v[x].a.first, v[y].a.first);
    if (t == 1) {
      v[x].p.first = v[y].p.second, v[x].a.second = v[y].a.first;
    } else if (t == 3) {
      v[x].a.first = v[y].a.first;
    }
    if (t) {
      if (e[v[x].a.first].empty() && e[v[x].a.second].empty()) {
        _v[++m] = v[x];
      } else {
        Insert(x);
      }
    }
  }
}

void Calc2() {
  for (int i = 1; i <= n >> 1; i++) {
    if (!e[i].empty()) {
      int x = e[i][0];
      _v[++m] = v[x], Delete(x);
    }
  }
  if (!m) {
    return;
  }
  swap(v, _v);
  while (m > 1) {
    SolveXYZW(v[1].p.first, v[1].p.second, v[m].p.first, v[m].p.second, v[1].a.first, v[1].a.second, v[m].a.first, v[m].a.second);
    v[1].p.second = v[m].p.first, v[1].a.second = v[m].a.first, m--;
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i] == v[1].a.first) {
      SolveXXY(i, v[1].p.first, v[1].p.second, v[1].a.first, v[1].a.second);
      break;
    }
  }
}

vector<int> memory(int _n) {
  static int o[kMaxN], d[kMaxM];
  static vector<int> tmp;
  n = _n;
  for (int i = 1; i <= n; i++) {
    o[i] = i;
  }
  shuffle(o + 1, o + n + 1, Rand);
  for (int i = 1; i <= n >> 1; i++) {
    u[i] = i;
    v[i].a = Look(o[i * 2 - 1], o[i * 2]);
    v[i].p = {o[i * 2 - 1], o[i * 2]};
  }
  shuffle(u + 1, u + (n >> 1) + 1, Rand);
  Calc1(), Calc2(), tmp.clear();
  for (int i = 1; i <= n; i++) {
    tmp.push_back(ans[i]);
  }
  return tmp;
}
// g++ -std=c++14 -O2 c.cpp grader.cpp -o c && c
