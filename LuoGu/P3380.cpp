#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V1 {
  int v, c, k, s[2];
};
struct B {  // Balance Tree
  int s;
  vector<V1> v = {{}};

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
    if (v[p].k < v[v[p].s[0]].k) {
      Turn(p, 1);
    } else if (v[p].k < v[v[p].s[1]].k) {
      Turn(p, 0);
    }
  }

  void Insert(int &p, int x) {
    if (!p) {
      p = v.size(), v.push_back({x, 1, rand()});
    } else {
      Insert(v[p].s[v[p].v < x], x);
    }
    Update(p);
  }

  int Replace(int &p) {
    int t = v[p].v;
    if (!v[p].s[1]) {
      p = v[p].s[0];
    } else {
      t = Replace(v[p].s[1]);
    }
    Update(p);
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
      Delete(v[p].s[v[p].v < x], x);
    }
    Update(p);
  }

  int FindRank(int p, int x) {
    if (!p) {
      return 0;
    } else if (v[p].v < x) {
      return FindRank(v[p].s[0], x);
    } else {
      return FindRank(v[p].s[1], x) + v[v[p].s[0]].c + 1;
    }
  }

  int FindVal(int p, int x) {
    int t = v[v[p].s[0]].c + 1;
    if (t == x) {
      return v[p].v;
    } else if (t > x) {
      return FindVal(v[p].s[0], x);
    } else {
      return FindVal(v[p].s[1], x - t);
    }
  }

  int FindPast(int p, int x) {
    if (!p) {
      return -2147483647;
    } else if (v[p].v < x) {
      return max(v[p].v, FindPast(v[p].s[1], x));
    } else {
      return FindPast(v[p].s[0], x);
    }
  }

  int FindNext(int p, int x) {
    if (!p) {
      return 2147483647;
    } else if (v[p].v > x) {
      return min(v[p].v, FindNext(v[p].s[0], x));
    } else {
      return FindNext(v[p].s[1], x);
    }
  }
};
struct S {  // Seg Tree
  vector<B> v = {{}};

  int Modify(int p, int l, int r, int x, int k) {
    if (l == r) {
      // CHICK
      return;
    }
    int mid = (l + r) / 2;
    if (mid >= x) {
      Modify(p * 2, l, mid, x, k);
    } else {
      Modify(p * 2, mid + 1, r, x, k);
    }
    // CHICK
  }
};
int n, m;

int main() {
  srand(unsigned(time(0)));

  return 0;
}
