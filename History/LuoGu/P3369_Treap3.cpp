#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

template <class T, int kMaxN>  // You SHOULD call the function Init() before using the treap.
class Treap {
 private:
  struct V {
    int s, k, l, r;
    T d;
  } v[kMaxN];
  int n, m, s;
  T mx, mn;
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
  void Insert(int &p, T x) {
    if (!p) {
      v[p = ++m].d = x, v[p].k = rand();
    } else {
      Insert(x < v[p].d ? v[p].l : v[p].r, x);
    }
    Update(p), Rebalance(p);
  }
  T Replace(int &p) {
    T c = v[p].d;
    if (!v[p].r) {
      p = v[p].l;
    } else {
      c = Replace(v[p].r);
      Update(p);
    }
    return c;
  }
  void Delete(int &p, T x) {
    if (v[p].d == x) {
      if (!v[p].l || !v[p].r) {
        p = v[p].l + v[p].r;
      } else {
        v[p].d = Replace(v[p].l);
      }
    } else {
      Delete(x < v[p].d ? v[p].l : v[p].r, x);
    }
    Update(p);
  }
  int FindRank(int &p, T x) {
    if (!p) {
      return 0;
    }
    return v[p].d < x ? FindRank(v[p].r, x) + v[v[p].l].s + 1 : FindRank(v[p].l, x);
  }
  T FindVal(int &p, int x) {
    if (v[v[p].l].s + 1 == x) {
      return v[p].d;
    }
    return v[v[p].l].s < x ? FindVal(v[p].r, x - v[v[p].l].s - 1) : FindVal(v[p].l, x);
  }
  T FindLast(int &p, T x) {
    if (!p) {
      return mn;
    }
    return v[p].d < x ? max(v[p].d, FindLast(v[p].r, x)) : FindLast(v[p].l, x);
  }
  T FindNext(int &p, T x) {
    if (!p) {
      return mx;
    }
    return x < v[p].d ? min(v[p].d, FindNext(v[p].l, x)) : FindNext(v[p].r, x);
  }

 public:
  const T operator[](int x) { return FindVal(s, x); }
  void Init(T minv, T maxv) { srand(time(0)), mn = minv, mx = maxv; }
  void Insert(T x) { Insert(s, x); }
  void Delete(T x) { Delete(s, x); }
  int FindRank(T x) { return FindRank(s, x) + 1; }
  T FindLast(T x) { return FindLast(s, x); }
  T FindNext(T x) { return FindNext(s, x); }
  bool Empty() { return !n; }
  int Size() { return n; }
};
int n;
Treap<int, 100001> t;

int main() {
  t.Init(-1e9, 1e9);
  cin >> n;
  for (int i = 1, o, x; i <= n; i++) {
    cin >> o >> x;
    if (o == 1) {
      t.Insert(x);
    } else if (o == 2) {
      t.Delete(x);
    } else if (o == 3) {
      cout << t.FindRank(x) << '\n';
    } else if (o == 4) {
      cout << t[x] << '\n';
    } else if (o == 5) {
      cout << t.FindLast(x) << '\n';
    } else {
      cout << t.FindNext(x) << '\n';
    }
  }
  return 0;
}
