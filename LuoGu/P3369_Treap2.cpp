#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1000000000;
struct V {
  int d, s, k, l, r;
} v[100001];
int n, m, s;

void Update(int &p) {
  v[p].s = v[v[p].l].s + v[v[p].r].s + (p != 0);
}

void Left(int &p) {
  int q = v[p].r;
  v[p].r = v[q].l, v[q].l = p;
  Update(p), Update(q);
  p = q;
}

void Right(int &p) {
  int q = v[p].l;
  v[p].l = v[q].r, v[q].r = p;
  Update(p), Update(q);
  p = q;
}

void Rebalance(int &p) {
  if (v[p].l && v[v[p].l].k < v[p].k) {
    Right(p);
  } else if (v[p].r && v[v[p].r].k < v[p].k) {
    Left(p);
  }
}

void Insert(int &p, int x) {
  if (!p) {
    v[p = ++m].d = x, v[p].k = rand();
  } else {
    Insert(v[p].d > x ? v[p].l : v[p].r, x);
  }
  Update(p), Rebalance(p);
}

int Replace(int &p) {
  int c = v[p].d;
  if (!v[p].r) {
    p = v[p].l;
  } else {
    c = Replace(v[p].r);
    Update(p);
  }
  return c;
}

void Delete(int &p, int x) {
  if (v[p].d == x) {
    if (!v[p].l || !v[p].r) {
      p = v[p].l + v[p].r;
    } else {
      v[p].d = Replace(v[p].l);
    }
  } else {
    Delete(v[p].d > x ? v[p].l : v[p].r, x);
  }
  Update(p);
}

int FindRank(int &p, int x) {
  if (!p) {
    return 0;
  }
  return v[p].d >= x ? FindRank(v[p].l, x) : FindRank(v[p].r, x) + v[v[p].l].s + 1;
}

int FindVal(int &p, int x) {
  if (v[v[p].l].s + 1 == x) {
    return v[p].d;
  }
  return v[v[p].l].s >= x ? FindVal(v[p].l, x) : FindVal(v[p].r, x - v[v[p].l].s - 1);
}

int FindLast(int &p, int x) {
  if (!p) {
    return -kInf;
  }
  return v[p].d < x ? max(v[p].d, FindLast(v[p].r, x)) : FindLast(v[p].l, x);
}

int FindNext(int &p, int x) {
  if (!p) {
    return kInf;
  }
  return v[p].d > x ? min(v[p].d, FindNext(v[p].l, x)) : FindNext(v[p].r, x);
}

int main() {
  srand((unsigned)time(0));
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
      cout << FindLast(s, x) << '\n';
    } else {
      cout << FindNext(s, x) << '\n';
    }
  }
  return 0;
}
