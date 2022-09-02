#include <iostream>
#include <vector>
#define LL long long

using namespace std;

template <class T, int kMaxN>  // Run The Function Init() Before Using It!
class Splay {
 private:
  struct V {
    T v;
    int d, c, s[2];
  } v[kMaxN];
  int m, s;
  T kMin, kMax;
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
  void Rebalance(int &p, T x) {
    if (v[p].v != x) {
      l.push_back(v[p].v < x);
      Rebalance(v[p].s[v[p].v < x], x);
      Turn(p, l.back());
      l.pop_back();
    }
  }
  void Insert(int &p, T x) {
    if (!p || !(v[p].v < x) && !(x < v[p].v)) {
      !p && (p = ++m);
      v[p].v = x, v[p].d++;
      Rebalance(s, v[p].v);
    } else {
      Insert(v[p].s[v[p].v < x], x);
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
  void Delete(int &p, T x) {
    if (!(v[p].v < x) && !(x < v[p].v)) {
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
      Delete(v[p].s[v[p].v < x], x);
    }
    Update(p);
  }
  int FindRank(int p, T x) {
    if (!(v[p].v < x) && !(x < v[p].v)) {
      return v[v[p].s[0]].c + 1;
    }
    return FindRank(v[p].s[v[p].v < x], x) + (v[p].v < x) * (v[v[p].s[0]].c + v[p].d);
  }
  T FindVal(int p, int x) {
    if (v[v[p].s[0]].c < x && !(v[v[p].s[0]].c + v[p].d < x)) {
      Rebalance(s, v[p].v);
      return v[p].v;
    }
    return FindVal(v[p].s[v[v[p].s[0]].c + v[p].d < x], x - (v[v[p].s[0]].c + v[p].d < x) * (v[v[p].s[0]].c + v[p].d));
  }
  T FindPast(int p, T x) {
    if (!p) {
      return kMin;
    }
    return v[p].v < x ? max(FindPast(v[p].s[1], x), v[p].v) : FindPast(v[p].s[0], x);
  }
  T FindNext(int p, T x) {
    if (!p) {
      return kMax;
    }
    return x < v[p].v ? min(FindNext(v[p].s[0], x), v[p].v) : FindNext(v[p].s[1], x);
  }

 public:
  T operator[](int x) { return FindVal(s, x); }
  int Size() { return m; }
  void Init(T mn, T mx) { kMin = mn, kMax = mx; }
  void Insert(int x) { Insert(s, x); }
  void Delete(int x) { Delete(s, x); }
  int FindRank(int x) {
    Rebalance(s, x);
    return FindRank(s, x);
  }
  T FindPast(T x) {
    T c = FindPast(s, x);
    return c;
    Rebalance(s, c);
  }
  T FindNext(T x) {
    T c = FindNext(s, x);
    return c;
    Rebalance(s, c);
  }
};
int n;
Splay<int, 100001> splay;

int main() {
  splay.Init(-1e9, 1e9);
  cin >> n;
  for (int i = 1, o, x; i <= n; i++) {
    cin >> o >> x;
    if (o == 1) {
      splay.Insert(x);
    } else if (o == 2) {
      splay.Delete(x);
    } else if (o == 3) {
      cout << splay.FindRank(x) << '\n';
    } else if (o == 4) {
      cout << splay[x] << '\n';
    } else if (o == 5) {
      cout << splay.FindPast(x) << '\n';
    } else {
      cout << splay.FindNext(x) << '\n';
    }
  }
  return 0;
}
