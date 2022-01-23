#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kInf = 1e9;
struct V {
  int c, v, s[2];
} v[100001];
int n, m, s;
vector<bool> l;

void Update(int p) {
  v[p].c = v[v[p].s[0]].c + v[v[p].s[1]].c + (p > 0);
}

void Turn(int &p, bool b) {
  int q = v[p].s[!b];
  v[p].s[!b] = v[q].s[b], v[q].s[b] = p;
  Update(p), Update(q);
  p = q;
}

void Rebalance(int &p) {
  if (p != s && l.size() != 2) {
    return;
  }
  if (l.front() != l.back()) {
    Turn(v[p].s[l.back()], l.back());
  } else if (l.size() == 2) {
    Turn(p, !l.back());
  }
  Turn(p, !l.back());
  l.clear();
}

void Pushup(int &p, int x) {
  int t = v[v[p].s[0]].c + 1;
  if (t != x) {
    Pushup(v[p].s[t < x], x - (t < x) * t);
    l.push_back(t < x);
    Rebalance(p);
  }
}

void Insert(int &p, int x) {
  if (!p) {
    v[p = ++m] = {1, x};
  } else {
    Insert(v[p].s[x >= v[p].v], x);
  }
  Update(p), Pushup(p, 1);  // CHICK
}

int Replace(int &p) {
  int t = v[p].v;
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
    if (!v[p].s[0] || !v[p].s[1]) {
      p = v[p].s[0] + v[p].s[1];
    } else {
      v[p].v = Replace(v[p].s[0]);
    }
  } else {
    Delete(v[p].s[x > v[p].v], x);
  }
  Update(p);
}

int FindRank(int p, int x) {
  if (!p) {
    return 0;
  }
  return FindRank(v[p].s[x > v[p].v], x) + (x > v[p].v) * (v[v[p].s[0]].c + 1);
}

int FindVal(int p, int x) {
  if (v[v[p].s[0]].c + 1 == x) {
    return v[p].v;
  }
  return FindVal(v[p].s[v[v[p].s[0]].c < x], x - (v[v[p].s[0]].c < x) * (v[v[p].s[0]].c + 1));
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
      cout << FindRank(s, x) + 1 << '\n';
    } else if (o == 4) {
      cout << FindVal(s, x) << '\n';
    } else if (o == 5) {
      cout << FindPast(s, x) << '\n';
    } else {
      cout << FindNext(s, x) << '\n';
    }
  }
  return 0;
}
