#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1000000000;
struct V {
  int d, s, l, r;
} v[100001];
int n, m, s = 1;

void Update(int &p) {
  v[p].s = v[v[p].l].s + v[v[p].r].s + (p != 0);
}

void Insert(int &p, int x) {
  if (!p || !m) {
    v[p = ++m].d = x;
  } else {
    Insert(v[p].d <= x ? v[p].r : v[p].l, x);
  }
  Update(p);
}

int Replace(int &p) {
  int c = p;
  if (!v[p].r) {
    p = v[p].l;
  } else {
    c = Replace(v[p].r);
  }
  Update(p);
  return c;
}

void Delete(int &p, int x) {
  if (v[p].d == x) {
    if (!v[p].l || !v[p].r) {
      p = v[p].l ? v[p].l : v[p].r;
    } else {
      int i = Replace(v[p].l);
      v[p].d = v[i].d;
    }
  } else {
    Delete(v[p].d < x ? v[p].r : v[p].l, x);
  }
  Update(p);
}

int FindRank(int &p, int x) {
  if (v[p].d == x) {
    return v[v[p].l].s + 1;
  } else if (v[p].d < x) {
    return FindRank(v[p].r, x) + v[v[p].l].s + 1;
  } else {
    return FindRank(v[p].l, x);
  }
}

int FindVal(int &p, int x) {
  if (v[v[p].l].s + 1 == x) {
    return v[p].d;
  } else if (v[v[p].l].s + 1 < x) {
    return FindVal(v[p].r, x - v[v[p].l].s - 1);
  } else {
    return FindVal(v[p].l, x);
  }
}

int FindLast(int &p, int x) {
  if (!p) {
    return -kInf;
  } else if (v[p].d < x) {
    return max(v[p].d, FindLast(v[p].r, x));
  } else {
    return FindLast(v[p].l, x);
  }
}

int FindNext(int &p, int x) {
  if (!p) {
    return kInf;
  } else if (v[p].d <= x) {
    return FindNext(v[p].r, x);
  } else {
    return min(v[p].d, FindNext(v[p].l, x));
  }
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
      cout << FindRank(s, x) << '\n';
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
