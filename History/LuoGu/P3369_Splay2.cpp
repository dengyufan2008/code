#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kInf = 1e9;
struct V {
  int v, d, c, s[2];
} v[100001];
int n, m, s;
vector<bool> l;

void Update(int p) {
  v[p].c = v[v[p].s[0]].c + v[v[p].s[1]].c + (p != 0) * v[p].d;
}

void Turn(int &p, bool b) {
  int q = v[p].s[b];
  v[p].s[b] = v[q].s[!b], v[q].s[!b] = p;
  Update(p), Update(q);
  p = q;
}

void Rebalance(int &p, int x) {
  if (v[p].v != x) {
    l.push_back(v[p].v < x);
    Rebalance(v[p].s[v[p].v < x], x);
    Turn(p, l.back());
    l.pop_back();
  }
}

void Insert(int &p, int x) {
  if (!p || v[p].v == x) {
    !p && (p = ++m);
    v[p].v = x, v[p].d++;
    Rebalance(s, v[p].v);
  } else {
    Insert(v[p].s[x > v[p].v], x);
  }
  Update(p);
}

int Replace(int &p) {
  int t = p;
  if (!v[p].s[1]) {
    p = v[p].s[0];
  } else {
    t = Replace(v[p].s[1]);
    Update(p);
  }
  return t;
}

void Delete(int &p, int x) {
  if (v[p].v == x) {
    if (!--v[p].d) {
      if (!v[p].s[0] || !v[p].s[1]) {
        p = v[p].s[0] + v[p].s[1];
      } else {
        int t = Replace(v[p].s[0]);
        v[p].v = v[t].v, v[p].d = v[t].d;
      }
    } else {
      Rebalance(s, v[p].v);
    }
  } else {
    Delete(v[p].s[x > v[p].v], x);
  }
  Update(p);
}

int FindRank(int p, int x) {
  if (v[p].v == x) {
    return v[v[p].s[0]].c + 1;
  }
  return FindRank(v[p].s[x > v[p].v], x) + (x > v[p].v) * (v[v[p].s[0]].c + v[p].d);
}

int FindVal(int p, int x) {
  if (v[v[p].s[0]].c < x && v[v[p].s[0]].c + v[p].d >= x) {
    Rebalance(s, v[p].v);
    return v[p].v;
  }
  return FindVal(v[p].s[v[v[p].s[0]].c + v[p].d < x], x - (v[v[p].s[0]].c + v[p].d < x) * (v[v[p].s[0]].c + v[p].d));
}

int FindPast(int p, int x) {
  if (!p) {
    return -kInf;
  }
  return v[p].v < x ? max(FindPast(v[p].s[1], x), v[p].v) : FindPast(v[p].s[0], x);
}

int FindNext(int p, int x) {
  if (!p) {
    return kInf;
  }
  return v[p].v > x ? min(FindNext(v[p].s[0], x), v[p].v) : FindNext(v[p].s[1], x);
}

int main() {
  cin >> n;
  for (int i = 1, o, x; i <= n; i++) {
    cin >> o >> x;
    if (o == 1) {
      Insert(s, x);
    } else if (o == 2) {
      Delete(s, x);
    } else if (o == 3) {
      Rebalance(s, x);
      cout << FindRank(s, x) << '\n';
    } else if (o == 4) {
      cout << FindVal(s, x) << '\n';
    } else if (o == 5) {
      int c = FindPast(s, x);
      cout << c << '\n';
      Rebalance(s, c);
    } else {
      int c = FindNext(s, x);
      cout << c << '\n';
      Rebalance(s, c);
    }
  }
  return 0;
}
