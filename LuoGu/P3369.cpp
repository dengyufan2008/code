#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1000000000;
struct V {
  int d, c, s, l, r;
} v[100001];
int n, m, s = 1;

void Insert(int &p, int x) {
  if (!p) {
    v[p = ++m] = {x, 1, 1};
  } else if (v[p].d == x) {
    v[p].c++, v[p].s++;
  } else if (v[p].d < x) {
    v[p].s++;
    Insert(v[p].r, x);
  } else {
    v[p].s++;
    Insert(v[p].l, x);
  }
}

void Delete(int &p, int x) {
  if (v[p].d == x) {
    v[p].c--, v[p].s--;
    if (!v[p].c) {
      int i = v[p].l;
      for (; v[v[i].r].r; i = v[i].r) {
        v[i].s--;
      }
      v[p].d = v[v[i].r].d, v[p].c = v[v[i].r].c, v[i].r = v[v[i].r].r;
    }
  } else if (v[p].d < x) {
    v[p].s--;
    Delete(v[p].r, x);
  } else {
    v[p].s--;
    Delete(v[p].l, x);
  }
}

int FindRank(int &p, int x) {
  if (v[p].d == x) {
    return 1;
  } else if (v[p].d < x) {
    return v[v[p].l].s + FindRank(v[p].r, x);
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
